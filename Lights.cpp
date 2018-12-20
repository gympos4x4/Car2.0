// Lights.cpp
// Author: Juraj Marcin

#include "Lights.h"

_Lights Lights;

void _Lights::init() {
	PIN_OUT(LX_DIR, LX0_FRONT_PIN);
	PIN_OUT(LX_DIR, LX1_REAR_PIN);
	PIN_OUT(LX_DIR, LX2_REV0_PIN);
	PIN_OUT(LX_DIR, LX3_REV1_PIN);
	PIN_OUT(LX_DIR, LX4_LEFT_PIN);
	PIN_OUT(LX_DIR, LX5_RIGHT_PIN);
}

void _Lights::interr(int16_t reading) {
	bool below = LI_BELOW_TRESHOLD(lightLevel);
	lightLevel = reading;
	setFront(below);
	setRear(below);
}

void _Lights::updateCarData(class CarData& cardata)
{
	cardata.lights.is_below_threshold = LI_BELOW_TRESHOLD(lightLevel);
	cardata.lights.level = lightLevel;
}

void _Lights::setFront(bool state) {
	PIN_WRITE(LX_PORT, LX0_FRONT_PIN, state);
}

void _Lights::setRear(bool state) {
	PIN_WRITE(LX_PORT, LX1_REAR_PIN, state);
}

void _Lights::setReverse(bool state) {
	PIN_WRITE(LX_PORT, LX2_REV0_PIN, state);
	PIN_WRITE(LX_PORT, LX3_REV1_PIN, state);
}

void _Lights::setLeft(bool state) {
	PIN_WRITE(LX_PORT, LX4_LEFT_PIN, state);
}

void _Lights::setRight(bool state) {
	PIN_WRITE(LX_PORT, LX5_RIGHT_PIN, state);
}
