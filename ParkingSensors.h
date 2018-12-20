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

#define PS_SENSOR_COUNT 1

class _ParkingSensors {

	uint8_t currentState = 0;
	uint8_t currentSensor = 0;
	int16_t lowStates[PS_SENSOR_COUNT];
	int16_t sensorData[PS_SENSOR_COUNT];

	public:
	void init();

	void interr();

	void update_cardata(CarData& cardata);
};

extern _ParkingSensors ParkingSensors;

#endif

