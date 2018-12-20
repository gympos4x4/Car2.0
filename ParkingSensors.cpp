// Author: Juraj Marcin

#include "ParkingSensors.h"

_ParkingSensors ParkingSensors;

void _ParkingSensors::init() {
	PIN_OUT(PS_IR_DIR, PS_IR_PIN);
}

void _ParkingSensors::interr(int16_t reading) {
	if (currentState) {
		sensorData[currentSensor] = reading - lowStates[currentSensor];
		currentSensor++;
		if (currentSensor >= PS_SENSOR_COUNT) {
			currentState = 0;
			PIN_WRITE_H(PS_IR_PRT, PS_IR_PIN);
			currentSensor = 0;
		}
		} else {
		lowStates[currentSensor] = reading;
		currentSensor++;
		if (currentSensor >= PS_SENSOR_COUNT) {
			currentState = 1;
			PIN_WRITE_L(PS_IR_PRT, PS_IR_PIN);
			currentSensor = 0;
		}
	}
}

void _ParkingSensors::update_cardata(CarData& cardata) {
	for (uint8_t i = 0; i < PS_SENSOR_COUNT; i++) {
		cardata.parking.sensor_data[i] = sensorData[i];
	}
}
