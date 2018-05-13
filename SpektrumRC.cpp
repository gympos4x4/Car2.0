// SpektrumRC.cpp
// Author: Juraj Marcin

#include "SpektrumRC.h"

_SpektrumRC SpektrumRC;

void _SpektrumRC::init() {
	pinMode(SR_THR_PIN, INPUT);
	pinMode(SR_STR_PIN, INPUT);
}

int8_t _SpektrumRC::getThrottle() {
	uint64_t val = pulseIn(SR_THR_PIN, HIGH, 20000);
	if (val < SR_THR_DMIN) {
		return map(val, SR_THR_MIN, SR_THR_DMIN, INT8_MIN, 0);
	} else if (val < SR_THR_DMAX) {
		return 0;
	} else {
		return map(val, SR_THR_DMAX, SR_THR_MAX, 0, INT8_MAX);
	}
}

int8_t _SpektrumRC::getSteer() {
	uint64_t val = pulseIn(SR_STR_PIN, HIGH, 20000);
	if (val < SR_STR_DMIN) {
		return map(val, SR_STR_MIN, SR_STR_DMIN, INT8_MIN, 0);
	} else if (val < SR_STR_DMAX) {
		return 0;
	} else {
		return map(val, SR_STR_DMAX, SR_STR_MAX, 0, INT8_MAX);
	}
}

void _SpektrumRC::loop() {
	lastThrottle = getThrottle();
	lastSteer = getSteer();
}

void _SpektrumRC::updateCarData(class CarData& cardata) {
	cardata.rc.throttle = lastThrottle;
	cardata.rc.steer = lastSteer;
}

_SpektrumRC::_SpektrumRC() {}
_SpektrumRC::~_SpektrumRC() {}