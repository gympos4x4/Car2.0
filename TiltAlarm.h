// TiltAlarm.h
// Author: Juraj Marcin

#ifndef _TILTALARM_h
#define _TILTALARM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "comm.h"
#include "pindef.h"
#include <Wire.h>

#define TA_ALERT_TRESHOLD 10
#define TA_ALERT_ANGLE_POS 23
#define TA_ALERT_ANGLE_NEG -20
#define TA_ALERT_OFFSET 90
#define TA_MPU_ADDR 0x68 // MPU-6050 #1 IC2 address
#define TA_PWR_MGMT_1 0x6B
#define TA_ALERT_INTERVAL 250
#define TA_ALERT_ENABLED HIGH

class CarData;
class _TiltAlarm {
	
	public:
	int16_t AcX, AcY, AcZ;
	int rotZ;
	uint64_t lastCheck;
	bool alertON;
	bool isTilted;
	bool alreadyTilted;
	uint16_t trueChecks;
	uint8_t enabled;

	public:

	void init();

	void loop();
	
	void updateCarData(CarData& cardata);

	private:

	bool tilted();

	void nextCheck();

	bool check();

	int16_t getAngle(int16_t x, int16_t z);

	void signal(bool value);
	
	void setRightTreshold();
	
	void setLeftTreshold();
};

extern _TiltAlarm TiltAlarm;

#endif

