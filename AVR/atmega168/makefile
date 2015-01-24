#An avrdude command that can program my board
# Uses an arduino as an ISP (for example I have a Leonardo with slightly modified ArduinoISP software, using 5/6 of its ISP pins, and pin 10 -> reset)
AVRDUDE=avrdude -c arduino -b 19200 -P /dev/tty.usbmodem1411 -p atmega168p -u

# default target when "make" is run w/o arguments
all: blink.hex

# compile blink.c into blink.o
blink.o: blink.c 
	avr-gcc -c -g -Os -Wall -mmcu=atmega168 blink.c -o blink.o

# link up blink.o into blink.elf
blink.elf: blink.o
	avr-gcc blink.o -mmcu=atmega168 -o blink.elf

# copy hex (FLASH) object out of blink.elf into blink.hex
blink.hex: blink.elf
	avr-objcopy -O ihex blink.elf blink.hex

# command to program chip (optional) (invoked by running "make install")
install: blink.hex
	$(AVRDUDE) -U flash:w:blink.hex -F -v

readfuse:
	$(AVRDUDE) -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h -F

defaultfuse:
	$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m -F

fuse:
	$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m -F

# command to clean up junk (no source files) (invoked by "make clean")
clean:
	rm -f *.o *.hex *.elf *.map *~