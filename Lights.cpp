// Lights.cpp
// Author: Juraj Marcin

#include "Lights.h"

_Lights Lights;

void _Lights::init() {
	pinMode(LX0_FRONT_PIN, OUTPUT);
	pinMode(LX1_REAR_PIN, OUTPUT);
	pinMode(LX2_REVERSE_PIN, OUTPUT);
	pinMode(LX3_LEFT_PIN, OUTPUT);
	pinMode(LX4_RIGHT_PIN, OUTPUT);
}

void _Lights::loop() {
	bool below = isBelowThreshold();
	setFront(below);
	setRear(below);
}

bool _Lights::isBelowThreshold() {
	lightLevel = analogRead(LXS_PIN);
	return lightLevel < LI_TRESHOLD; // returns true if light level is below treshold value
}

void _Lights::updateCarData(class CarData& cardata)
{
	cardata.lights.is_below_threshold = isBelowThreshold();
	cardata.lights.level = lightLevel;
}

void _Lights::setFront(bool state) {
	digitalWrite(LX0_FRONT_PIN, state);
}

void _Lights::setRear(bool state) {
	digitalWrite(LX1_REAR_PIN, state);
}

void _Lights::setReverse(bool state) {
	digitalWrite(LX2_REVERSE_PIN, state);
}

void _Lights::setLeft(bool state) {
	digitalWrite(LX3_LEFT_PIN, state);
}

void _Lights::setRight(bool state) {
	digitalWrite(LX4_RIGHT_PIN, state);
}
