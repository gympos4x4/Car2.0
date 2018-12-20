// Car2.0.ino
// Author: Juraj Marcin

//#define DEBUG
#define SEND_INTERVAL 500
#define DEBUG_INTERVAL 500

#include "ESP8266.h"
#include "SpektrumRC.h"
#include "TiltAlarm.h"
#include "Lights.h"
#include "ParkingSensors.h"
#include "Chassis.h"

CarData cardata;
ControllerData ctrldata;

uint64_t lastDataSend = 0;
uint64_t lastDebugSend = 0;

uint8_t adcPins[ADC_PIN_COUNT] = {1};
uint8_t adcPin = 0;

void setup() {
	#ifdef DEBUG
	Serial.begin(9600);
	#endif // DEBUG
	#ifdef DEBUG
	Serial.println("Booting...");
	#endif // DEBUG
	PIN_OUT(SPKR_DIR, SPKR_PIN);
	
	/* BOOT START SOUND */
	PIN_WRITE_H(SPKR_PRT, SPKR_PIN);
	delay(400);
	PIN_WRITE_L(SPKR_PRT, SPKR_PIN);
	
	sei();
	
	
	/* SET DEFAULT VALUES */
	ctrldata.astr_mode = 1;
	
	/* INIT DEVICES */
	Lights.init();
	TiltAlarm.init();
	SpektrumRC.init();
	Chassis.init();
	//ParkingSensors.init();
	ESP8266.init();
	
	/* INIT ADC */
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((0 >> 3) & 0x01) << MUX5);
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADSC);
	
	/* BOOT END SOUND */
	PIN_WRITE_H(SPKR_PRT, SPKR_PIN);
	delay(200);
	PIN_WRITE_L(SPKR_PRT, SPKR_PIN);
	delay(200);
	PIN_WRITE_H(SPKR_PRT, SPKR_PIN);
	delay(200);
	PIN_WRITE_L(SPKR_PRT, SPKR_PIN);
	
	/* START ADC CONVERSION */
	startADCConverstion(adcPins[adcPin]);
	
	#ifdef DEBUG
	Serial.println("Booted!");
	#endif // DEBUG
}

void loop() {
	TiltAlarm.loop();
	SpektrumRC.loop(ctrldata.astr_mode);
	Chassis.setHeight(ctrldata.height);
	ctrldata.height = 0;

	updateCarData();

	if (millis() > lastDataSend + SEND_INTERVAL) {
		ESP8266.sendCarData(&cardata);
		lastDataSend = millis();
	}
	
	ESP8266.loop(&ctrldata);
	
	#ifdef DEBUG
	if (millis() > lastDebugSend + DEBUG_INTERVAL) {
		sendDebug();
		lastDebugSend = millis();
	}
	#endif // DEBUG

	delay(10);
}

void sendDebug() {
	Serial.println(millis());
	Serial.print("car.battery_percentage=");Serial.println(cardata.battery_percentage);
	Serial.print("car.tilt.degrees=");Serial.println(cardata.tilt.degrees);
	Serial.print("car.tilt.tilted=");Serial.println(cardata.tilt.tilted);
	Serial.print("car.lights.is_below_threshold=");Serial.println(cardata.lights.is_below_threshold);
	Serial.print("car.lights.level=");Serial.println(cardata.lights.level);
	Serial.print("car.rc.throttle=");Serial.println(cardata.rc.throttle);
	Serial.print("car.rc.steer=");Serial.println(cardata.rc.steer);
	Serial.print("car.parking.sensor_data=");Serial.println(cardata.parking.sensor_data[0]);
	Serial.print("ctrl.height=");Serial.println(ctrldata.height);
	Serial.print("ctrl.astr_mode=");Serial.println(ctrldata.astr_mode);
}

void updateCarData() {
	cardata.battery_percentage = (analogRead(VBAT_SENSE_PIN) - 700) / 2;
	Lights.updateCarData(cardata);
	ParkingSensors.update_cardata(cardata);
	SpektrumRC.updateCarData(cardata);
	TiltAlarm.updateCarData(cardata);
}

void startADCConverstion(uint8_t pin) {
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (pin & (1 << MUX5));
	ADMUX = (1 << REFS0) | (pin & 0x07);
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	uint8_t low = ADCL;
	uint8_t high = ADCH;
	int16_t reading = (high << 8) | low;
	if (adcPins[adcPin] >= 8 && adcPins[adcPin] <= 15) {
		ParkingSensors.interr(reading);
		} else if (adcPins[adcPin] == 1) {
		Lights.interr(reading);
	}
	adcPin++;
	if (adcPin >= ADC_PIN_COUNT) {
		adcPin = 0;
	}
	startADCConverstion(adcPins[adcPin]);
}
