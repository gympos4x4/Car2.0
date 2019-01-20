// Lights.cpp
// Author: Juraj Marcin

#include "Lights.h"

_Lights Lights;

void _Lights::init() {
	PIN_OUT(LXS_DIR, LXS_C0_FRONT_PIN);
	PIN_OUT(LXS_DIR, LXS_C1_REAR_PIN);
	PIN_OUT(LXS_DIR, LXS_C2_REV0_PIN);
	PIN_OUT(LXS_DIR, LXS_C3_REV1_PIN);
	PIN_OUT(LXS_DIR, LXS_C4_LEFT_PIN);
	PIN_OUT(LXS_DIR, LXS_C5_RIGHT_PIN);
}

void _Lights::loop(int8_t steer) {
	if (steer > LI_STR_R_TRESHOLD) {
		if (millis() > blinkStart + LI_BLINK_TIME) {
			if (left) left = false;
			else left = true;
			blinkStart = millis();
			setLeft(left);
		}
	} else {
		left = false;
		setLeft(false);
	}
	if (steer < LI_STR_L_TRESHOLD) {
		if (millis() > blinkStart + LI_BLINK_TIME) {
			if (right) right = false;
			else right = true;
			blinkStart = millis();
			setRight(right);
		}
		setRight(right);
	} else {
		right = false;
		setRight(false);
	}
}

void _Lights::interr(int16_t reading) {
	bool below = LI_BELOW_TRESHOLD(lightLevel);
	lightLevel = reading;
	setFront(below);
	setRear(below);
}

void _Lights::updateCarData(CarData& cardata)
{
	cardata.lights.is_below_threshold = LI_BELOW_TRESHOLD(lightLevel);
	cardata.lights.level = lightLevel;
}

void _Lights::setFront(bool state) {
	PIN_WRITE(LXS_PORT, LXS_C0_FRONT_PIN, state);
}

void _Lights::setRear(bool state) {
	PIN_WRITE(LXS_PORT, LXS_C1_REAR_PIN, state);
}

void _Lights::setReverse(bool state) {
	PIN_WRITE(LXS_PORT, LXS_C2_REV0_PIN, state);
	PIN_WRITE(LXS_PORT, LXS_C3_REV1_PIN, state);
}

void _Lights::setLeft(bool state) {
	PIN_WRITE(LXS_PORT, LXS_C4_LEFT_PIN, state);
}

void _Lights::setRight(bool state) {
	PIN_WRITE(LXS_PORT, LXS_C5_RIGHT_PIN, state);
}
