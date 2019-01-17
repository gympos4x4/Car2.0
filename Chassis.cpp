// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {
	// SET OUTPUTS //
	PIN_OUT(CHS_DIR_DIR, CHS_DIR_PIN);
	PIN_OUT(CHS_PWM_DIR, CHS_PWM_PIN);
	// SET INPUTS, PULL UPS //
	/*PIN_IN(DDRD, PD2);
	PIN_IN(DDRD, PD3);
	PIN_WRITE_H(PORTD, PD2);
	PIN_WRITE_H(PORTD, PD3);
	// SETUP ENDSTOP INTERRUPTS //
	EICRA = (1 << ISC31) | (1 << ISC30) | (1 << ISC21) | (1 << ISC20);
	EIMSK = (1 << INT3) | (1 << INT2);*/
	// SET REV SENSOR TIMER //
	/*TCCR1A = 0;
	TCCR1B = (1 << ICES5) | (1 << CS10);
	TIMSK1 = (1 << ICIE1);*/
}

void _Chassis::setHeight(int8_t height) {
	if (height > 0) {
		//if (maxHigh) return;
		//direction = 1;
		PIN_WRITE_H(CHS_DIR_PORT, CHS_DIR_PIN);
		//uint64_t start = millis();
		//while(qRotsChange < 20);
		delay(100);
		PIN_WRITE_L(CHS_DIR_PORT, CHS_DIR_PIN);
/*#if PMC_REV == 1
		PIN_WRITE_H(CHS_DIR_PORT, CHS_DIR_PIN);
		PIN_WRITE_H(CHS_PWM_PORT, CHS_PWM_PIN);
		uint64_t start = millis();
		while(qRotsChange < 20);
		PIN_WRITE_L(CHS_PWM_PORT, CHS_PWM_PIN);
#endif*/
		//maxLow = false;
	} else if (height < 0) {
		//if (maxLow) return;
		direction = -1;
		PIN_WRITE_H(CHS_PWM_PORT, CHS_PWM_PIN);
		//uint64_t start = millis();
		//while(qRotsChange < 20);
		delay(100);
		PIN_WRITE_L(CHS_PWM_PORT, CHS_PWM_PIN);
/*#if PMC_REV == 1
		PIN_WRITE_L(CHS_DIR_PORT, CHS_DIR_PIN);
		PIN_WRITE_H(CHS_PWM_PORT, CHS_PWM_PIN);
		uint64_t start = millis();
		while(qRotsChange < 20);
		PIN_WRITE_L(CHS_PWM_PORT, CHS_PWM_PIN);
#endif*/
		//maxHigh = false;
	}
	/*direction = 0;
	qRotsChange = 0;*/
}
