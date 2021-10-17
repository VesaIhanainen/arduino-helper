#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd.h"
#include "arduinohelper.h"

#define MS_DELAY 3000

void pulseEnable(struct Pins *pins){
    digitalWrite(pins->enable, 0);
    _delay_ms(1);
    digitalWrite(pins->enable, 1);
    _delay_ms(1);
    digitalWrite(pins->enable, 0);
    _delay_ms(100);
}

void writeBits(struct Pins *pins, uint8_t value){
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(pins->data_pins[i],(value >> i ) & 0x01);
        //digitalWrite(pins->data_pins[i],(value & 1 << i ));
    }
    pulseEnable(pins);
    
}

void send(struct Pins *pins, uint8_t value, uint8_t mode){
    digitalWrite(pins->reset,mode);
    // digitalWrite(pins->read_write,0);
  
    writeBits(pins,value >> 4);
    writeBits(pins,value);

    // writeBits(pins,value);
    // writeBits(pins,value >> 4);
}

void command(struct Pins *pins, uint8_t value){
    send(pins,value,0);
}

uint8_t write(struct Pins *pins, uint8_t value){
    send(pins,value,1);
    return 1;
}

void display(struct Pins *pins, struct Lcd *lcd){
    lcd->_displaycontrol |= LCD_DISPLAYON;
    command(pins,LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void clear(struct Pins *pins){
    command(pins,LCD_CLEARDISPLAY);
    _delay_ms(2000);
}

void LCDInit(struct Pins *pins, struct Lcd *lcd){
    lcd->_displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
    lcd->_row_offsets[0] = 0x00;
    lcd->_row_offsets[1] = 0x40;
    lcd->_row_offsets[2] = 0x00+16;
    lcd->_row_offsets[3] = 0x40+16;
    pinMode(pins->reset, 1);
    // pinMode(pins->read_write, 0);
    pinMode(pins->enable, 1);
    for (int i = 0; i < 4; i++)
    {
        pinMode(pins->data_pins[i],1);
    }

    // Initialize
    _delay_us(50000);
    digitalWrite(pins->reset, 0);
    digitalWrite(pins->enable, 0);
    // digitalWrite(pins->read_write, 0);
    // Set to 4-bit interface 
    //writeBits(pins,0x02);

    // Send function set command sequence
    command(pins,LCD_FUNCTIONSET | lcd->_displayfunction);
    _delay_ms(4500);  // wait more than 4.1 ms

    // second try
    command(pins,LCD_FUNCTIONSET | lcd->_displayfunction);
    _delay_ms(150);

    // third go
    command(pins,LCD_FUNCTIONSET | lcd->_displayfunction);

    command(pins, LCD_FUNCTIONSET | lcd->_displayfunction);

    lcd->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display(pins,lcd);
    
    clear(pins);

    lcd->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    command(pins, LCD_ENTRYMODESET | lcd->_displaymode); 
}

