// SpektrumRC.cpp
// Author: Juraj Marcin

#include "SpektrumRC.h"

_SpektrumRC SpektrumRC;

void _SpektrumRC::init() {
	PIN_OUT(SRC_ASTR_DIR, SRC_ASTR_PIN);
	
	/* RESET TIMER4 REGISTER A */
	TCCR4A = 0;
	/* SET PRESCALER TO 64, RISING EDGE SELECT */
	TCCR4B = (1 << CS41) | (1 << CS40) | (1 << ICES4);
	/* SET INTERRUPT FOR TIMER4 IC */
	TIMSK4 = (1 << ICIE4);

	/* SET NON-INVERTING MODE ON CHANNEL A, FAST PWM 1024, PRESCALER TO 64, RISING EDGE SELECT */
	TCCR5A = (1 << COM5A1) | (1 << WGM51) | (1 << WGM50);
	TCCR5B = (1 << WGM52) | (1 << CS51) | (1 << CS50) | (1 << ICES5);
	/* SET INERRUPT FOR TIMER5 IC AND OCA */
	TIMSK5 = (1 << ICIE5) | (1 << OCIE5A);
}

void _SpektrumRC::loop() {
	if (astrMode < 0) {
		OCR5A = str;
	} else if (astrMode > 0) {
		OCR5A = SRC_STR_INV - str;
	} else {
		OCR5A = SRC_STR_CTR;
	}
}

void _SpektrumRC::strInputInterr() {
	if (strIH) {
		strH = ICR4;
		str = strH - strL;
		strIH = 0;
		TCCR4B = (TCCR4B & ~(1 << ICES4)) | (1 << ICES4);
	} else {
		strL = ICR4;
		strIH = 1;
		TCCR4B = (TCCR4B & ~(1 << ICES4));
	}
}

void _SpektrumRC::thrInputInterr() {
	if (thrIH) {
		thrH = ICR5;
		tthr = thrH - thrL;
		if (tthr < 1024) {
			thr = tthr;
		}
		thrIH = 0;
		TCCR5B = (TCCR5B & ~(1 << ICES5)) | (1 << ICES5);
	} else {
		thrL = ICR5;
		thrIH = 1;
		TCCR5B = (TCCR5B & ~(1 << ICES5));
	}
}

void _SpektrumRC::astrOutputInterr() {
	if (pulseCounter == 0) {
		TCCR5A = (1 << WGM51) | (1 << WGM50);
		pulseCounter++;
	} else if (pulseCounter == 4) {
		TCCR5A = (1 << WGM51) | (1 << WGM50) | (1 << COM5A1);
		pulseCounter = 0;
	} else {
		pulseCounter++;
	}
}

void _SpektrumRC::updateCarData(CarData& cardata) {
	int16_t tmp = str - SRC_STR_CTR;
	if (tmp > 127) {
		tmp = 127;
	} else if (tmp < -128) {
		tmp = -128;
	}
	cardata.rc.steer = tmp;
	tmp = thr - SRC_THR_CTR;
	if (tmp > 127) {
		tmp = 127;
	} else if (tmp < -128) {
		tmp = -128;
	}
	cardata.rc.throttle = tmp;
}