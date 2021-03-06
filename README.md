# 4-ch ADC Data Logger with LPC1114

This is a simple ADC data logger based on LPC1114FN28 microcontroller.
Primary motivation is to test and record battery runtime independently, without using large/external facility like a PC.

# Major Features
- Can measure voltage of 4 channels every minutes at 10-bit resolution
- Can stream data to serial port
- Can log data to FAT-formatted SD card (saves after every 60 samples)
- Can flush data to SD card with a button press
- Can erase data on SD card with a button press
- Can show activity/response to LEDs
- Supports battery-based, low power operation

# How to Build
```
$ git clone lpc-adc-logger
$ cd lpc-adc-logger
$ platformio lib install 234
$ make
```

# How to Use
- Insert a SD card with a file LOG-0000.DAT on its root folder.
- LOG-0000.DAT must be prepared as a zero-filled file large enough to hold all log data.
-- Command `dd if=/dev/zero of=LOG-0000.DAT bs=1024 count=1024` would do
- Pressing "Erase/Flush" button during powerup erases data in datafile.
- Pressing "Erase/Flush" button during operation flushes data to datafile.
- Connect UART to see a stream of currently sampled data.
- You can power off anytime - however, most recent 512B (1 sector) amount of data will be lost unless flushed by a button press.

# LED pattern meanings
- Fast blink - processing button press
- Slow blink - in operation

# Log File Format

File is written as a series of `logdata_t` data, dumped from memory.
Following is an excerpt from the source code:

```
struct logdata_t {
    uint32_t magic;   //   4B
    uint8_t length;   //   1B
    uint8_t skip[27]; //  27B
    struct {          // 480B
        uint16_t ad[4];
    } sample[60];
} __attribute__((packed));
```

After every 60 samples (of 4ch 16-bit ADC data), this 512B block of
data structure gets full and dumped to the disk. So length is usually
0x3c (decimal 60), but could be less if user has forced to save by
pressing a save button.

LPC1114 is a little-endian ARM Cortex-M0 processor, so beware with the
byte order when accessing multi-byte value.

# Pinouts
- dp1  - SD card (MISO)
- dp2  - SD card (MOSI)
- dp3  - SWD (SWDCLK)
- dp4  - ADC ch#0
- dp5  - NC (reserved for I2C-SDA)
- dp6  - SD card (SCLK)
- dp7  - Analog VCC
- dp8  - Analog GND
- dp9  - ADC ch#1
- dp10 - ADC ch#2
- dp11 - ADC ch#3
- dp12 - SWD (SWDIO)
- dp13 - NC (reserved for PWM/WAKEUP)
- dp14 - Button #1 (Flush/Erase Button)

- dp15 - Serial RX
- dp16 - Serial TX
- dp17 - NC (reserved for button)
- dp18 - NC (reserved for PWM)
- dp19 - NC (XTALOUT)
- dp20 - NC (XTALIN)
- dp21 - VCC
- dp22 - GND
- dp23 - RESET
- dp24 - NC (reserved for CLKOUT)
- dp25 - SD card (SSEL)
- dp26 - LED #1
- dp27 - NC (reserved for I2C-SCL)
- dp28 - NC (reserved for LED #2)

# Schematic

# Notes
- Already functional, but currently under development. 
- Sampling rate is currently 1 sample/s, will make it 1 sample/min in final version.

# See Also
- PlatformIO (https://platformio.org/)
- BlackMagic (https://github.com/blacksphere/blackmagic)
- mBed (https://mbed.org/)
- PFF (http://elm-chan.org/fsw/ff/00index_p.html)
- PinDetect (PlatformIO library #ID: 234)
