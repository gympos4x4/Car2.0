// SpektrumRC.cpp
// Author: Juraj Marcin

#include "SpektrumRC.h"

#define DEBUG

_SpektrumRC SpektrumRC;

void _SpektrumRC::init() {
	pinMode(THRI_PIN, INPUT);
	pinMode(STRI_PIN, INPUT);
	aServo.attach(ASTR_PIN);
}

int8_t _SpektrumRC::getThrottle() {
	uint64_t val = pulseIn(THRI_PIN, HIGH, 20000);
	#ifdef DEBUG
	Serial.print("THR:");
	Serial.println((long)val);
	#endif
	if (val < SR_THR_DMIN) {
		return map(val, SR_THR_MIN, SR_THR_DMIN, -100, 0);
		} else if (val < SR_THR_DMAX) {
		return 0;
		} else {
		return map(val, SR_THR_DMAX, SR_THR_MAX, 0, 100);
	}
}

int8_t _SpektrumRC::getSteer() {
	uint64_t val = pulseIn(STRI_PIN, HIGH, 20000);
	#ifdef DEBUG
	Serial.print("STR:");
	Serial.println((long)val);
	#endif
	if (val < SR_STR_DMIN) {
		return map(val, SR_STR_MIN, SR_STR_DMIN, -100, 0);
		} else if (val < SR_STR_DMAX) {
		return 0;
		} else {
		return map(val, SR_STR_DMAX, SR_STR_MAX, 0, 100);
	}
}

void _SpektrumRC::loop(int8_t astrMode) {
	lastThrottle = getThrottle();
	lastSteer = getSteer();
	aServo.write(map(lastSteer * astrMode, -100, 100, SR_ASR_MIN, SR_ASR_MAX));
	/*if (disableAServo) {
		if (!aServoDisabled) {
			aServo.write(abs(SR_ASR_MIN + SR_ASR_MAX) / 2);
			aServoDisabled = true;
		}
	} else {
		aServo.write(map(lastSteer, -100, 100, SR_ASR_MIN, SR_ASR_MAX));
		aServoDisabled = false;
	}*/
}

void _SpektrumRC::updateCarData(class CarData& cardata) {
	cardata.rc.throttle = lastThrottle;
	cardata.rc.steer = lastSteer;
}

_SpektrumRC::_SpektrumRC() {}
_SpektrumRC::~_SpektrumRC() {}