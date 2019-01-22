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

#define LI_TRESHOLD 14 // turn on lights below this value
#define LI_BELOW_TRESHOLD(value) (value < LI_TRESHOLD)
#define LI_BLINK_TIME 600
#define LI_STR_R_TRESHOLD 10
#define LI_STR_L_TRESHOLD -10

class _Lights {

	volatile int16_t lightLevel;
	bool left = false;
	bool right = false;
	uint64_t blinkStart = 0;

public:
	_Lights() {}
	~_Lights() {}

public:
	void init();
	
	void loop(int8_t steer);

	void interr(int16_t reading);

	void setFront(bool state);

	void setRear(bool state);

	void setLeft(bool state);

	void setRight(bool state);

	void updateCarData(CarData& cardata);
};

extern _Lights Lights;

#endif

