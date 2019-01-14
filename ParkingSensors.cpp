// Author: Juraj Marcin

#include "ParkingSensors.h"

_ParkingSensors ParkingSensors;

void _ParkingSensors::init() {
	PIN_OUT(PRS_IR_DIR, PRS_IR_PIN);
}

void _ParkingSensors::interr(int16_t reading) {
	if (currentState) {
		sensorData[currentSensor] = reading - lowStates[currentSensor];
		currentSensor++;
		if (currentSensor >= PRS_SENSOR_COUNT) {
			currentState = 0;
			PIN_WRITE_L(PRS_IR_PRT, PRS_IR_PIN);
			currentSensor = 0;
		}
	} else {
		lowStates[currentSensor] = reading;
		currentSensor++;
		if (currentSensor >= PRS_SENSOR_COUNT) {
			currentState = 1;
			PIN_WRITE_H(PRS_IR_PRT, PRS_IR_PIN);
			currentSensor = 0;
		}
	}
}

void _ParkingSensors::updateCarData(CarData& cardata) {
	for (uint8_t i = 0; i < PRS_SENSOR_COUNT; i++) {
		cardata.parking.sensor_data[i] = sensorData[i] - 128;
	}
}
