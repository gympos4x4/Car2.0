// TiltAlarm.cpp
// Author: Juraj Marcin

#include "TiltAlarm.h"

_TiltAlarm TiltAlarm;

void _TiltAlarm::init() {
	pinMode(SPKR_PIN, OUTPUT);
	Wire.begin();
	Wire.beginTransmission(TA_MPU_ADDR);
	Wire.write(TA_PWR_MGMT_1);  // PWR_MGMT_1 register
	Wire.write(0);     // set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);
}

void _TiltAlarm::loop() {
	nextCheck();
	if (millis() > lastCheck + TA_ALERT_INTERVAL) {
		if (tilted()) {
			alertON = !alertON;
			} else {
			alertON = false;
		}
		signal(alertON);
		lastCheck = millis();
	}
}

bool _TiltAlarm::tilted() {
	return alreadyTilted;
}

void _TiltAlarm::nextCheck() {
	bool r = check();
	if (r == isTilted) {
		trueChecks++;
	} else {
		trueChecks = 0;
		isTilted = r;
	}
	if (trueChecks > TA_ALERT_TRESHOLD) {
		alreadyTilted = isTilted;
	}
}

bool _TiltAlarm::check() {
	Wire.beginTransmission(TA_MPU_ADDR);
	Wire.write(0x3B);  // starting with register 0x43 (GYRO_XOUT_H)
	Wire.endTransmission(false);
	Wire.requestFrom(TA_MPU_ADDR, 6, true);  // request a total of 14 registers
	AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
	AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	rotZ = getAngle(AcX, AcZ);
	return rotZ - TA_ALERT_OFFSET > TA_ALERT_ANGLE_POS || rotZ - TA_ALERT_OFFSET < TA_ALERT_ANGLE_NEG;
}

int16_t _TiltAlarm::getAngle(int16_t x, int16_t z) {
	return degrees(atan2(z, x));
}

void _TiltAlarm::signal(bool value) {
#ifdef PIEZO_PIN
	tone(PIEZO_PIN, 440, 500);
#else
	digitalWrite(SPKR_PIN, value);
#endif
}

void _TiltAlarm::updateCarData(class CarData& cardata) {
	cardata.tilt.degrees = rotZ - TA_ALERT_OFFSET;
	cardata.tilt.tilted = tilted();
}