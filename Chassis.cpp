// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {
	Serial.println("CONFIGURUNG CLARA...");
	/*#if BOARD_REV == 2
	PIN_OUT(CHS_DIR, CHS_RST_PIN);
	PIN_OUT(CHS_DIR, CHS_EN_PIN);
	PIN_OUT(CHS_DIR, CHS_SLP_PIN);
	PIN_OUT(CHS_DIR, CHS_DIR_PIN);
	PIN_OUT(CHS_STP_DIR, CHS_STP_PIN);
	
	PIN_WRITE_H(CHS_PORT, CHS_RST_PIN);
	PIN_WRITE_L(CHS_PORT, CHS_EN_PIN);
	PIN_WRITE_L(CHS_STP_PORT, CHS_STP_PIN);
	PIN_WRITE_H(CHS_PORT, CHS_SLP_PIN);
	#else*/
	PIN_OUT(DDRH, PH6);
	TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
	OCR2B = 23;
	/*#endif*/
	// SET GROUND //
	PIN_OUT(DDRC, PC7);
	PIN_WRITE_L(PORTC, PC7);
	// SET ENDSTOP INPUTS, PULL UPS //
	PIN_IN(DDRD, PD2);
	PIN_IN(DDRD, PD3);
	PIN_WRITE_H(PORTD, PD2);
	PIN_WRITE_H(PORTD, PD3);
	// SETUP ENDSTOP INTERRUPTS //
	EICRA |= (1 << ISC30) | (1 << ISC20);
	EIMSK |= (1 << INT3) | (1 << INT2);
	// SET REV SENSOR TIMER //
	/*TCCR1A = 0;
	TCCR1B = (1 << ICES5) | (1 << CS10);
	TIMSK1 = (1 << ICIE1);*/
	Serial.println("CLARA CONFIGURATION DONE");
}

void _Chassis::setHeight(int8_t height) {
	/*#if BOARD_REV == 2
	if (height > 0) {
		if (maxHigh) return;
		direction = 1;
		PIN_WRITE_H(CHS_PORT, CHS_DIR_PIN);
		for (uint8_t r = 0; r < CH_STEP; r++) {
			if (maxHigh) break;
			PIN_WRITE_H(CHS_STP_PORT, CHS_STP_PIN);
			delay(1);
			PIN_WRITE_L(CHS_STP_PORT, CHS_STP_PIN);
			delay(1);
		}
		maxLow = false;
	} else if (height < 0) {
		if (maxLow) return;
		direction = -1;
		PIN_WRITE_L(CHS_PORT, CHS_DIR_PIN);
		for (uint8_t r = 0; r < CH_STEP; r++) {
			if (maxLow) break;
			PIN_WRITE_H(CHS_STP_PORT, CHS_STP_PIN);
			delay(1);
			PIN_WRITE_L(CHS_STP_PORT, CHS_STP_PIN);
			delay(1);
		}
		maxHigh = false;
	}
	#else*/
	if (height > 0) {
		if (maxHigh) return;
		direction = 1;
		OCR2B = 31;
		uint64_t start = millis();
		while(qRotsChange < CH_STEP && millis() < start + height && !maxHigh);
		OCR2B = 23;
		maxLow = false;
	} else if (height < 0) {
		if (maxLow) return;
		direction = -1;
		OCR2B = 16;
		uint64_t start = millis();
		while(qRotsChange < CH_STEP && millis() < start + abs(height) && !maxLow);
		OCR2B = 23;
		maxHigh = false;
	}
	direction = 0;
	qRotsChange = 0;
	/*#endif*/
}
