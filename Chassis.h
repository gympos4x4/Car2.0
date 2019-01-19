// Chassis.h
// Author: Juraj Marcin

#ifndef _CHASSIS_h
#define _CHASSIS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "pindef.h"
#include <Servo.h>

class _Chassis {
	
	public:
	volatile int8_t direction;	
	volatile bool maxLow = false;
	volatile bool maxHigh = false;
	volatile int64_t qRots = 0;
	volatile int64_t qRotsChange = 0;
	
	Servo s;
	
	void init();

	void setHeight(int8_t height);
	
	void highInterr();
	
	void lowInterr();
};

extern _Chassis Chassis;

#endif

