#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "arduinohelper.h"
#define HIGH 1
#define INPUT 1
#define LOW 0
#define OUTPUT 0

void pinMode(uint8_t port, uint8_t mode){
    if(2 <= port && port <= 7){
        if(mode == INPUT){
            DDRD |= _BV(port);
        }
        else{
            DDRD &= ~_BV(port);
        }
    }
    if (8 <= port && port <= 13){
        if(mode == INPUT){
            DDRB |= _BV(port-8);
        }
        else{
            DDRB &= ~_BV(port-8);
        }
    }
}

void disablePWM(uint8_t port){
    if( port == 3)
    {
        TCCR2A &= ~_BV(COM2B1);
    }
    if( port == 5){
        TCCR0A &= ~_BV(COM0B1);
    }
    if ( port == 6){
        TCCR0A &= ~_BV(COM0A1);
    }
    if ( port == 9){
        TCCR1A &= ~_BV(COM1A1);
    }
    if ( port == 10){
        TCCR1A &= ~_BV(COM1B1);
    }
    if ( port == 11){
        TCCR2A &= ~_BV(COM2A1);
    }
}

int digitalRead(uint8_t port){
    disablePWM(port);
    uint8_t bit = _BV(port % 9);
    if(2 <= port && port <= 7){
        if (PORTD & bit) return HIGH;
    }
    else if (8 <= port && port <= 13)
    {
        
        if (PORTB & bit) return HIGH;
    }
    return LOW;    
}

void digitalWrite(uint8_t port, uint8_t value){
    disablePWM(port);

    uint8_t oldSREG = SREG;
    cli();
    if(2 <= port && port <= 7){
        if(value == 1){
            PORTD |= _BV(port);
        }
        else{
            PORTD &= ~_BV(port);
        }
    }
    if (8 <= port && port <= 13){
        if(value == 1){
            PORTB |= _BV(port-8);
        }
        else{
            PORTB &= ~_BV(port-8);
        }
    }
    SREG = oldSREG;
}