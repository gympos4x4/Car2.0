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
#include "pindef.h"

#define LI_TRESHOLD 36 // turn on lights below this value

class _Lights {

	int16_t lightLevel;

public:
	_Lights() {}
	~_Lights() {}

public:
	void init();

	void loop();

	void setFront(bool state);

	void setRear(bool state);

	void setReverse(bool state);

	void setLeft(bool state);

	void setRight(bool state);

	bool isBelowThreshold();

	void updateCarData(class CarData& cardata);
};

extern _Lights Lights;

#endif

