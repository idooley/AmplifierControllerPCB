AVRDUDE=avrdude -c usbasp -p atmega168p -u
AVR=atmega168
AVRGCC=avr-gcc -DF_CPU=16000000 -std=c11 -Os -Wall -mmcu=$(AVR)

HEADERS = DHT22int.h lcd_lib.h

all: blink.hex amp_controller.hex lcd_driver.hex thermometer.hex

%.o: %.c $(HEADERS)
	$(AVRGCC) -c -g $< -o $@

%.elf: %.o
	$(AVRGCC) $^ -o $@

lcd_driver.o: lcd_driver.c $(HEADERS)
	$(AVRGCC) -c -g $< -o $@

lcd_driver.elf:	lcd_driver.o lcd_lib.o
	$(AVRGCC) $^ -o $@

thermometer.elf: thermometer.o lcd_lib.o DHT22int.o
	$(AVRGCC) $^ -o $@

%.hex: %.elf
	avr-objcopy -O ihex $^ $@

install_blink: blink.hex
	$(AVRDUDE) -U flash:w:$^ -F -v

install_amp_controller: amp_controller.hex
	$(AVRDUDE) -U flash:w:$^ -F -v

install_lcd_driver: lcd_driver.hex
	$(AVRDUDE) -U flash:w:$^ -F -v

lcd_lib.o: lcd_lib.c $(HEADERS)
	$(AVRGCC) -c -g $< -o $@

readfuse:
	$(AVRDUDE) -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h -F

defaultfuse:
	$(AVRDUDE) -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m -F

fuse:
	$(AVRDUDE) -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0x01:m -F

# command to clean up junk (no source files) (invoked by "make clean")
clean:
	rm -f *.o *.hex *.elf *.map *~
