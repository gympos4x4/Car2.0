// ParkingSensors.h
// Author: Juraj Marcin

#ifndef _PARKINGSENSORS_h
#define _PARKINGSENSORS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "comm.h"
#include "pindef.h"

class _ParkingSensors {

	volatile uint8_t currentState = 0;
	volatile uint8_t currentSensor = 0;
	volatile int16_t lowStates[PRS_SENSOR_COUNT];
	volatile int16_t sensorData[PRS_SENSOR_COUNT];

	public:
	void init();

	void interr(int16_t reading);

	void updateCarData(CarData& cardata);
};

extern _ParkingSensors ParkingSensors;

#endif

