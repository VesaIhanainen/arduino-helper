.PHONY: clean
CC=avr-gcc
OBJCOPY=avr-objcopy

CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p

main.hex: main.elf
	${OBJCOPY} -O ihex -R .eeprom main.elf main.hex
main.elf: main.o lcd.o arduinohelper.o
	${CC} $(CFLAGS) -o main.elf lcd.o arduinohelper.o main.o
main.o: main.c
	${CC} $(CFLAGS) -c main.c -o main.o
lcd.o: lcd.c
	${CC} $(CFLAGS) -c lcd.c -o lcd.o 
arduinohelper.o: arduinohelper.c arduinohelper.h
	${CC} $(CFLAGS) -c arduinohelper.c -o arduinohelper.o
clean:
	rm *.o
	rm *.elf
	rm *.hex