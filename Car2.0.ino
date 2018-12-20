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

void setup() {
	#ifdef DEBUG
	Serial.begin(9600);
	#endif // DEBUG
	#ifdef DEBUG
	Serial.println("Booting...");
	#endif // DEBUG
	pinMode(SPKR_PIN, OUTPUT);
	digitalWrite(SPKR_PIN, HIGH);
	delay(400);
	digitalWrite(SPKR_PIN, LOW);
	setDefValues();
	ESP8266.init();
	Lights.init();
	TiltAlarm.init();
	SpektrumRC.init();
	Chassis.init();
	//ParkingSensors.init();
	
	digitalWrite(SPKR_PIN, HIGH);
	delay(200);
	digitalWrite(SPKR_PIN, LOW);
	delay(200);
	digitalWrite(SPKR_PIN, HIGH);
	delay(200);
	digitalWrite(SPKR_PIN, LOW);
	#ifdef DEBUG
	Serial.println("Booted!");
	#endif // DEBUG
}

void loop() {
	Lights.loop();
	TiltAlarm.loop();
	SpektrumRC.loop(ctrldata.astr_mode);
	Chassis.setHeight(ctrldata.height);
	ctrldata.height = 0;
	ParkingSensors.loop();

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

void setDefValues() {
	ctrldata.astr_mode = 1;
}