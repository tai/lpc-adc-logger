//
// ADC Data Logger
//

#include "mbed.h"
#include "pt.h"
#include "pff.h"
#include "semihost.h"
#include "PinDetect.h"

#if DEVICE_SEMIHOST
#define log semihost_printf
#else
#define log printf
#endif

AnalogIn ad0(dp4), ad1(dp9), ad2(dp10), ad3(dp11);
DigitalOut led1(dp26);

PinDetect saveButton(dp14);
DigitalIn saveButtonRaw(dp14);

Ticker readTicker;
Ticker blinkTicker;

#define NR_ELEM(a) (sizeof(a) / sizeof(a[0]))

#define ASSERTED 0
#define MAGIC 0xDEADBEEF

// Record to hold sampled data
// Must fit into single FAT sector (512B)
struct logdata_t {
    uint32_t magic;   //   4B
    uint8_t length;   //   1B
    uint8_t skip[27]; //  27B
    struct {          // 480B
        uint16_t ad[4];
    } sample[60];
};

// Global context to pass around
struct ctx_t {
    FATFS fs;
    logdata_t log;

    bool is_key_pressed;
    bool is_ready_to_read;
    bool is_ready_to_save;
} ctx;

void
init_sd() {
    FRESULT rc;

    //
    // Elm-chan's PFF (Petit FAT FS) library is small, but has many
    // limitations like below:
    //
    // - It only supports access to existing file
    // - There is no filehandle - only one file can be opened at once
    //
    // Here, we do basic setup so further logging can be done just by
    // calling series of pf_write API.
    //
    
    rc = pf_mount(&ctx.fs);
    log("pf_mount: %d\r\n", rc);

    rc = pf_open("TEST.TXT");
    log("pf_open: %d\r\n", rc);

    //
    // By default, when 'save' button is NOT asserted during startup,
    // logger will skip existing data and try to append to next free sector.
    //
    if (saveButtonRaw == ! ASSERTED) {
        do {
            WORD nr;
            rc = pf_read(&ctx.log, sizeof(ctx.log), &nr);
            log("pf_read: %d, nr=%d\r\n", rc, nr);
        } while (ctx.log.magic == MAGIC);

        // Rewind back by 1 sector as this is the sector we should write to
        rc = pf_lseek(ctx.fs.fptr - sizeof(ctx.log));
        log("pf_lseek: %d\r\n", rc);
    }
}

void
init() {
    log("init: entered\r\n");

    // init SD card
    init_sd();

    // init context
    ctx.log.magic = MAGIC;

    // start blinking
    blinkTicker.attach_us([]() -> void { led1 = !led1; }, 1000000);

    // start sampling
    readTicker.attach_us([]() -> void { ctx.is_ready_to_read = true; }, 1000000);

    // start input-check
    saveButton.attach_asserted([]() -> void { ctx.is_key_pressed = true; });
}

//
// Task to check user input.
// Currently, there's not much to check as there is only one button
// that triggers a save action.
//
PT_THREAD(check_pin_task(pt *pt)) {
    PT_BEGIN(pt);

    for (;;) {
        PT_WAIT_UNTIL(pt, ctx.is_key_pressed);
        ctx.is_key_pressed = false;
        ctx.is_ready_to_save = true;

        log("key press detected.\r\n");
    }
    PT_END(pt);
}

//
// Task to read ADC data.
// Also streams data out to serial port and triggers a save when
// buffer is full.
//
PT_THREAD(data_read_task(pt *pt)) {
    PT_BEGIN(pt);

    static uint32_t tick;

    for (;;) {
        PT_WAIT_UNTIL(pt, ctx.is_ready_to_read);
        ctx.is_ready_to_read = false;

        auto& sample = ctx.log.sample[ctx.log.length++];
        sample.ad[0] = ad0.read_u16();
        sample.ad[1] = ad1.read_u16();
        sample.ad[2] = ad2.read_u16();
        sample.ad[3] = ad3.read_u16();

        log("%u,%04X,%04X,%04X,%04X\r\n",
            tick++, sample.ad[0], sample.ad[1], sample.ad[2], sample.ad[3]);

        if (ctx.log.length >= NR_ELEM(ctx.log.sample)) {
            ctx.is_ready_to_save = true;
        }
    }
    PT_END(pt);
}

//
// Task to save current data when triggered.
//
PT_THREAD(data_save_task(pt *pt)) {
    PT_BEGIN(pt);

    for (;;) {
        PT_WAIT_UNTIL(pt, ctx.is_ready_to_save);
        ctx.is_ready_to_save = false;

        log("saving data...\r\n");

        FRESULT rc;
        WORD nr;

        rc = pf_write(&ctx.log, sizeof(ctx.log), &nr);
        log("pf_write: %d, nr=%d\r\n", rc, nr);

        rc = pf_write(0, 0, &nr);
        log("pf_write(0): %d, nr=%d\r\n", rc, nr);

        ctx.log.length = 0;
    }
    PT_END(pt);
}

int
main() {
    pt pt1, pt2, pt3, pt4;

    init();

    for (;;) {
        check_pin_task(&pt1);
        data_read_task(&pt3);
        data_save_task(&pt2);
        sleep();
    }
    return 0;
}
