// Car2.0.ino
// Author: Juraj Marcin

#define DEBUG

#include "SpektrumRC.h"
#include "TiltAlarm.h"
#include "Lights.h"

CarData cardata;

void setup() {
	SpektrumRC.init();
	Lights.init();
	TiltAlarm.init();
	
	#ifdef DEBUG
	Serial.begin(9600);
	#endif
}

void loop() {
	SpektrumRC.loop();
	Lights.loop();
	TiltAlarm.loop();
	#ifdef DEBUG
	sendDebugSerial();
	#endif

	delay(5);
}

void sendDebugSerial() {
	Serial.print("battery_percentage=");Serial.println(cardata.battery_percentage);
	Serial.print("tilt.tilted=");Serial.println(cardata.tilt.tilted);
	Serial.print("tilt.degrees=");Serial.println(cardata.tilt.degrees);
	Serial.print("lights.is_below_threshold=");Serial.println(cardata.lights.is_below_threshold);
	Serial.print("rc.throttle=");Serial.println(cardata.rc.throttle);
	Serial.print("rc.steer=");Serial.println(cardata.rc.steer);
}

void updateCarData() {
	SpektrumRC.updateCarData(cardata);
	TiltAlarm.updateCarData(cardata);
	Lights.updateCarData(cardata);
}