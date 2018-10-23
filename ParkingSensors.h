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

#define PS_SENSOR_COUNT 3

class _ParkingSensors {

	const uint8_t sensorPins[PS_SENSOR_COUNT] = {A0, A1, A2};

	public:
	int16_t sensorData[PS_SENSOR_COUNT];

	public:
	_ParkingSensors() {}
	~_ParkingSensors() {}

	public:
	/// <summary>
	/// initiates parking sensors
	/// </summary>
	void init();

	/// <summary>
	/// reads sensor value
	/// </summary>
	/// <param name='sensor'>sensor to read from</param>
	int16_t readsensor(int sensor);

	/// <summary>
	/// executes one check cycle
	/// </summary>
	void loop();

	/// <summary>
	/// updates data that's being sent to the controller
	/// </summary>
	/// <param name='cardata'>CarData instance</param>
	void update_cardata(class CarData& cardata);
};

extern _ParkingSensors ParkingSensors;

#endif

