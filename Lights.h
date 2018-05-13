// Lights.h
// Author: Juraj Marcin

#ifndef _LIGHTS_h
#define _LIGHTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "comm.h"

#define LI_SENSOR_PIN A0
#define LI_FRONT_PIN 0
#define LI_REAR_PIN 6
#define LI_REVERSE_PIN 7
#define LI_TRESHOLD 36 // turn on lights below this value

class _Lights {

	bool lastCheck;

public:
	_Lights() {}
	~_Lights() {}

public:
	void init();

	void loop();

	void setFront(bool state);
	void setRear(bool state);
	void setSide(bool state);

	bool isBelowThreshold();

	void updateCarData(class CarData& cardata);
};

extern _Lights Lights;

#endif

