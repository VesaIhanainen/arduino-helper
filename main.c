#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define HIGH 1
#define INPUT 1
#define LOW 0
#define OUTPUT 0

#include "lcd.h"
#include "arduinohelper.h"

int main(void){
    uint8_t output = 9;
    uint8_t input = 10;
    struct Pins pins;
    pins.reset = 12;
    pins.enable = 11;
    pins.data_pins[0] = 5;
    pins.data_pins[1] = 4;
    pins.data_pins[2] = 3;
    pins.data_pins[3] = 2;
    struct Lcd lcd;
    LCDInit(&pins,&lcd);
    pinMode(output,OUTPUT);
    pinMode(input,INPUT);    
    uint8_t value = 0;
    const char Buffer[5] = "Hello";
    while(1){
        for (size_t i = 0; i < 10; i++)
        {
            digitalWrite(output,LOW);
            _delay_ms(250);
            value = digitalRead(input);
            _delay_ms(250);
            write(&pins,Buffer[value]);
            digitalWrite(output,HIGH);
            _delay_ms(250);
            value = digitalRead(input);
            _delay_ms(250);
            write(&pins,Buffer[value]);
        }
        _delay_ms(500);
    }
}