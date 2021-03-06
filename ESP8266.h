// ESP8266.h
// Author: Juraj Marcin

#ifndef _ESP8266_h
#define _ESP8266_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "comm.h"
#include "pindef.h"
#include "config.h"
#include "SpektrumRC.h"
#include "Chassis.h"
#include "Lights.h"
#include "TiltAlarm.h"

#define ES_TIMEOUT 10

class _ESP8266 {
	
	private:
	bool gotResponse;
	
	public:
	void init();

	bool sendCarData(CarData* data);
	
	void loop(ControllerData* data);

	private:
	void cmd(const char cmd[]);

	void serialFind(const char target[], uint8_t targetLenght);
};

extern _ESP8266 ESP8266;

#endif

