#
# ref:
# - https://lowreal.net/2016/02/17/3
#

DEV = /dev/tty.usbserial-A50285BI

ELF = .pioenvs/lpc1114fn28/firmware.elf
BIN = $(ELF:.elf=.bin)

all: $(ELF)

$(ELF): $(wildcard src/*.cpp src/*.hpp)
	pio run

flash: $(ELF)
	pio run -t upload

flash-gdb:
	arm-none-eabi-gdb -q -batch -x loadelf.gdb $(ELF)

flash-ocd:
	openocd -f lpc1114.cfg -c ""

flash-isp: $(BIN)
	lpc21isp -control -bin $(BIN) $(DEV) 115200 12000

debug: $(ELF)
	arm-none-eabi-gdb -q $(ELF)

ispmon:
	lpc21isp -termonly -control $(DEV) 115200 12000

clean:
	pio run -t clean
