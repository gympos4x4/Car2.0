// Car2.0.ino
// Author: Juraj Marcin

#define DEBUG
#define SEND_INTERVAL 250
#define DEBUG_INTERVAL 1000
#define BAT_INTERVAL 5000

// BATTERY VALUES //
#define NIMH_H_OFFSET 66.21f //A
#define NIMH_K 0.01854f      //k
#define NIMH_BASE 1.872f     //b
#define NIMH_V_OFFSET 0.002f //c

#include "ESP8266.h"
#include "SpektrumRC.h"
#include "TiltAlarm.h"
#include "Lights.h"
//#include "ParkingSensors.h"
#include "Chassis.h"

CarData cardata;
ControllerData ctrldata;

uint64_t lastDataSend = 0;
uint64_t lastDebugSend = 0;
volatile uint64_t lastBatCheck = 0;

volatile uint8_t adcPins[ADC_PIN_COUNT] = {VBT_SENSE_PIN, LXS_SENSOR_PIN/*, PRS_SENSOR0_PIN, PRS_SENSOR1_PIN, PRS_SENSOR2_PIN, PRS_SENSOR3_PIN, PRS_SENSOR4_PIN, PRS_SENSOR3_PIN*/};
volatile uint8_t adcPin = 0;

volatile int16_t batteryPercentage = 0;

void setup() {
	#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("BOOTING COLOS...");
	Serial.println("3 Devices Run ColOS");
	#endif // DEBUG
	
	PIN_OUT(SPK_DIR, SPK_PIN);
	
	// BOOT START SOUND //
	PIN_WRITE_H(SPK_PRT, SPK_PIN);
	delay(400);
	PIN_WRITE_L(SPK_PRT, SPK_PIN);
	
	sei();
	
	// WATCHDOG CONFIG //
	//WDTCSR = (1 << WDCE);
	//WDTCSR |= (1 << WDP2) | (1 << WDP1) | (1 << WDE);//
	
	// SET DEFAULT VALUES //
	ctrldata.astr_mode = 1;
	
	// INIT DEVICES //
	Lights.init();
	TiltAlarm.init();
	SpektrumRC.init();
	Chassis.init();
	//ParkingSensors.init();
	ESP8266.init();
	
	// INIT ADC //
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((0 >> 3) & 0x01) << MUX5);
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADSC);
	
	// BOOT END SOUND //
	PIN_WRITE_H(SPK_PRT, SPK_PIN);
	delay(200);
	PIN_WRITE_L(SPK_PRT, SPK_PIN);
	delay(200);
	PIN_WRITE_H(SPK_PRT, SPK_PIN);
	delay(200);
	PIN_WRITE_L(SPK_PRT, SPK_PIN);
	delay(500);
	
	// START ADC CONVERSION //
	startADCConversion(adcPins[adcPin]);
	
	#ifdef DEBUG
	Serial.println("BOOT OK!");
	#endif // DEBUG*/
	
	
}

void loop() {
	TiltAlarm.loop();
	SpektrumRC.loop();
	ctrldata.height = 0;
	Chassis.qRotsChange = 0;
	
	updateCarData();
	Lights.loop(cardata.rc.steer);

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
}

void sendDebug() {
	Serial.println(millis());
	Serial.print("car.battery_percentage=");Serial.println(cardata.battery_percentage);
	Serial.print("car.tilt.degrees=");Serial.println(cardata.tilt.degrees);
	/*Serial.print("car.tilt.tilted=");Serial.println(cardata.tilt.tilted);
	Serial.print("car.lights.is_below_threshold=");Serial.println(cardata.lights.is_below_threshold);*/
	Serial.print("car.lights.level=");Serial.println(cardata.lights.level);
	Serial.print("car.rc.throttle=");Serial.println(cardata.rc.throttle);
	Serial.print("car.rc.steer=");Serial.println(cardata.rc.steer);
	//Serial.print("car.parking.sensor_data=");Serial.println(cardata.parking.sensor_data[0]);*/
	Serial.print("ctrl.height=");Serial.println(ctrldata.height);
	Serial.print("ctrl.astr_mode=");Serial.println(ctrldata.astr_mode);
}

void updateCarData() {
	cardata.battery_percentage = batteryPercentage;
	Lights.updateCarData(cardata);
	TiltAlarm.updateCarData(cardata);
	//ParkingSensors.updateCarData(cardata);
	SpektrumRC.updateCarData(cardata);
}

void startADCConversion(uint8_t pin) {
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (pin & (1 << MUX5));
	ADMUX = (1 << REFS0) | (pin & 0x07);
	ADCSRA |= (1 << ADSC);
}

int8_t calculateBatteryPrecentage(float voltage)
{
	float percent = (1 / (pow(NIMH_BASE, NIMH_H_OFFSET - voltage / NIMH_K) + 1)) + NIMH_V_OFFSET;
	return (int8_t)(100*percent);
	return min(100,(int8_t)(100*percent));
}

ISR(ADC_vect) {
	int16_t reading = ADC;
	if (adcPins[adcPin] >= 8 && adcPins[adcPin] <= 15) {
		//ParkingSensors.interr(reading);
	} else if (adcPins[adcPin] == LXS_SENSOR_PIN) {
		Lights.interr(reading);
	} else if (adcPins[adcPin] == VBT_SENSE_PIN) {
		batteryPercentage = reading;
		lastBatCheck = millis();
	}
	adcPin = ADC_NEXT(adcPin);
	if (adcPins[adcPin] == VBT_SENSE_PIN && lastBatCheck + BAT_INTERVAL > millis()) {
		adcPin = ADC_NEXT(adcPin);
	}
	startADCConversion(adcPins[adcPin]);
}

// SPEKTRUM TIMERS //

ISR(TIMER4_CAPT_vect) {
	SpektrumRC.strInputInterr();
}

ISR(TIMER5_CAPT_vect) {
	SpektrumRC.thrInputInterr();
}

ISR(TIMER5_COMPA_vect) {
	SpektrumRC.astrOutputInterr();
}

// CHASSIS ENDSTOP TIMERS //
/*
ISR(INT2_vect) {
	Chassis.maxHigh = PIN_READ(PIND, PD2);
}

ISR(INT3_vect) {
	Chassis.maxLow = PIN_READ(PIND, PD3);
}*/

// CHASSIS REV SENSORS TIMER //
/*
ISR(TIMER1_CAPT_vect) {
	Chassis.qRots += Chassis.direction;
	Chassis.qRotsChange++;;
}*/
