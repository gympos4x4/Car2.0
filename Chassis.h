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

class _Chassis {
	
	uint8_t currentHeigth;
	
	public:
	void init();

	void setHeight(int8_t height);
};

extern _Chassis Chassis;

#endif

