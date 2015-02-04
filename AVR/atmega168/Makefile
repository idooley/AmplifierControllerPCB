# An avrdude command that can program my board

# Use an arduino as an ISP (for example I have a Leonardo with slightly modified ArduinoISP software, using 5/6 of its ISP pins, and pin 10 -> reset)
#AVRDUDE=avrdude -c arduino -b 19200 -P /dev/tty.usbmodem1411 -p atmega168p -u

# Use an USBasp_H6
AVRDUDE=avrdude -c usbasp -p atmega168p -u
AVR=atmega168


all: blink.hex amp_controller.hex

%.o: %.c 
	avr-gcc -c -g -Os -Wall -mmcu=$(AVR) $< -o $@

%.elf: %.o
	avr-gcc $< -mmcu=$(AVR) -o $@

%.hex: %.elf
	avr-objcopy -O ihex $< $@

install_blink: blink.hex
	$(AVRDUDE) -U flash:w:$< -F -v

install_amp_controller: amp_controller.hex
	$(AVRDUDE) -U flash:w:$< -F -v

readfuse:
	$(AVRDUDE) -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h -F

defaultfuse:
	$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m -F

fuse:
	$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m -F

# command to clean up junk (no source files) (invoked by "make clean")
clean:
	rm -f *.o *.hex *.elf *.map *~
