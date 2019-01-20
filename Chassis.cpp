// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {	
	PIN_OUT(DDRH, PH6);
	TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
	OCR2B = 23;
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
	TCCR1A = 0;
	TCCR1B = (1 << ICES5) | (1 << CS10);
	TIMSK1 = (1 << ICIE1);
}

void _Chassis::setHeight(int8_t height) {
	if (height > 0) {
		//if (maxHigh) return;
		direction = 1;
		Serial.println(qRotsChange);
		OCR2B = 31;
		uint64_t start = millis();
		while(qRotsChange < CH_STEP/* && millis() < start + CH_TIMEOUT/* && !maxHigh*/) {
			if (millis() > start + CH_TIMEOUT) {
				Serial.println("UP TIMEOUT");
				break;
			}
		}
		OCR2B = 23;
		Serial.println(qRotsChange);
		//maxLow = false;
	} else if (height < 0) {
		//if (maxLow) return;
		direction = -1;
		Serial.println(qRotsChange);
		OCR2B = 16;
		uint64_t start = millis();
		while(qRotsChange < CH_STEP/* && millis() < start + CH_TIMEOUT/* && !maxLow*/) {
			if (millis() > start + CH_TIMEOUT) {
				Serial.println("DOWN TIMEOUT");
				break;
			}
		}
		OCR2B = 23;
		Serial.println(qRotsChange);
		//maxHigh = false;
	}
	direction = 0;
	qRotsChange = 0;
}
