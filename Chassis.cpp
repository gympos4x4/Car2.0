// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {	
	PIN_OUT(DDRH, PH6);
	/*TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
	OCR2B = 23;*/
	// SET OUTPUTS //
	/*PIN_OUT(CHS_DIR_DIR, CHS_DIR_PIN);
	PIN_OUT(CHS_PWM_DIR, CHS_PWM_PIN);*/
	// SET ENDSTOP INPUTS, PULL UPS //
	/*PIN_IN(DDRD, PD2);
	PIN_IN(DDRD, PD3);
	PIN_WRITE_H(PORTD, PD2);
	PIN_WRITE_H(PORTD, PD3);
	// SET GROUND //
	PIN_OUT(DDRC, PC6);
	PIN_WRITE_L(PORTC, PC6);
	// SETUP ENDSTOP INTERRUPTS //
	EICRA = (1 << ISC31) | (1 << ISC30) | (1 << ISC21) | (1 << ISC20);
	EIMSK = (1 << INT3) | (1 << INT2);*/
	// SET REV SENSOR TIMER //
	/*TCCR1A = 0;
	TCCR1B = (1 << ICES5) | (1 << CS10);
	TIMSK1 = (1 << ICIE1);*/
	
	/* SET NON-INVERTING MODE ON CHANNEL A, FAST PWM 1024, PRESCALER TO 64, RISING EDGE SELECT */
	TCCR5A = (1 << COM5A1) | (1 << WGM51);
	TCCR5B = (1 << WGM53) | (1 << WGM52) | (1 << CS51);
	ICR5 = 39999;
}

void _Chassis::setHeight(int8_t height) {
	if (height > 0) {
		direction = 1;
		OCR5A = 3999;
		uint64_t start = millis();
		while(qRotsChange < CH_STEP/* && millis() < start + CH_TIMEOUT/* && !maxHigh*/) {
			if (millis() > start + height) {
				break;
			}
		}
		OCR5A = 2999;
	} else if (height < 0) {
		direction = -1;
		OCR5A = 1999;
		uint64_t start = millis();
		while(qRotsChange < CH_STEP/* && millis() < start + CH_TIMEOUT/* && !maxLow*/) {
			if (millis() > start + abs(height)) {
				break;
			}
	}
	OCR5A = 2999;
	}
	direction = 0;
	qRotsChange = 0;
}
