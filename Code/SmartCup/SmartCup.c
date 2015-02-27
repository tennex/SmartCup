/*
 * SmartCup.c
 *
 * Created: 25.02.2015 17:51:56
 *  Author: Orav
 */ 

#define F_CPU 2000000UL
#include <util/delay.h>
#include <avr/io.h>

void init() {
	//RGB LEDs
	DDRB = 0xFF;
	PORTB = 0x00;
	
	//Heating element
	DDRC = 0b11000000;
	PORTC = 0x00;
	
	//ADMUX
	ADMUX = 0b11000000;
	
	//ADC Temperature
	DDRF = 0;
	ADCSRA = (1 << ADEN | 1 << ADSC);		//ADC Enable, Start conversion

}

void getTemperature() {
	ADCSRA |= (1 << ADSC);					//Start conversion
		
	while ((ADCSRA & (1<<ADIF)) == 0) {		//Wait ADC interrupt flag
	}
	
	//PORTB = (uint8_t)ADC;
	
	if ((uint8_t)ADC >= 96) { //3 SINIST
		PORTB = 0b01100000;
	}
	else if ((uint8_t)ADC >= 92) { //3 LILLAT 1 PUNANE
		PORTB = 0b00100000;
		PORTC = 0x11000000;
	}
	else if ((uint8_t)ADC >= 32) { //4 PUNAST
		PORTB = 0b10100000;
	}
	OCR1A = ADC;
	//OCR1AL = ADCL;
	ADCSRA |= 0b00010000;
		
	//if ((uint8_t)ADCL0 <= 876) {
		//PORTB = 0b11000000;
	//}
	//else {
		//PORTB = 0b01100000;
	//}  
}

void testLED() {
	PORTB = 0b10000000; //3 Rohelist, 1 punane
	_delay_ms(1000);
	PORTB = 0b01000000; //Sinakad See on teine olek
	_delay_ms(1000);
	PORTB = 0b00100000; //3 Lillat, 1 punane
	_delay_ms(1000);
	PORTB = 0b11000000; //3 Rohelist
	_delay_ms(1000);
	PORTB = 0b10100000; //4 Punast
	_delay_ms(1000);
	PORTB = 0b01100000; //3 Sinist See on alguses
	_delay_ms(1000);
}

int main(void) {
	init();
	
    while(1)
    {
		//testLED();
		getTemperature();				
       	
    }
}