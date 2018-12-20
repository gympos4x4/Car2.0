// Author: Juraj Marcin

#include "ParkingSensors.h"

_ParkingSensors ParkingSensors;

void _ParkingSensors::init() {
	PIN_OUT(PS_IR_DIR, PS_IR_PIN)
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((0 >> 3) & 0x01) << MUX5);
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADSC);
}

void _ParkingSensors::interr() {
	uint8_t low = ADCL;
	uint8_t high = ADCH;
	int16_t reading = (high << 8) | low;
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
			PIN_WRITE_H(PS_IR_PRT, PS_IR_PIN);
			currentSensor = 0;
		}
	}
	ADMUX = (1 << REFS0) | currentSensor;
	ADCSRA |= (1 << ADSC);
}

void _ParkingSensors::update_cardata(CarData& cardata) {
	for (uint8_t i = 0; i < PS_SENSOR_COUNT; i++) {
		cardata.parking.sensor_data[i] = sensorData[i];
	}
