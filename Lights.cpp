// Lights.cpp
// Author: Juraj Marcin

#include "Lights.h"

_Lights Lights;

void _Lights::init() {
	pinMode(LI_FRONT_PIN, OUTPUT);
	//pinMode(LI_REAR_PIN, OUTPUT);
	//pinMode(LI_REVERSE_PIN, OUTPUT);
}

void _Lights::loop() {
	bool below = isBelowThreshold();
	setFront(below);
	//set_rear(below);
}

bool _Lights::isBelowThreshold() {
	return analogRead(LI_SENSOR_PIN) < LI_TRESHOLD; // returns true if light level is below treshold value
}

void _Lights::updateCarData(class CarData& cardata)
{
	cardata.lights.is_below_threshold = isBelowThreshold();
}

void _Lights::setFront(bool state)
{
	digitalWrite(LI_FRONT_PIN, state);
}
void _Lights::setRear(bool state)
{
	digitalWrite(LI_REAR_PIN, state);
}
void _Lights::setSide(bool state)
{
	//digitalWrite(LI_REVERSE_PIN, state);
}