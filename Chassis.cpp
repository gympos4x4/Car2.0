// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {
	pinMode(CHS_MOT_PWM, OUTPUT);
	pinMode(CHS_MOT_DIR, OUTPUT);
}

void _Chassis::setHeight(uint8_t height) {
	if (height > 128 && currentHeigth != 255) {
		digitalWrite(CHS_MOT_PWM, HIGH);
		delay(500);
		digitalWrite(CHS_MOT_PWM, LOW);
		currentHeigth = 255;
	} else if (height < 128 && currentHeigth != 0) {
		digitalWrite(CHS_MOT_DIR, HIGH);
		delay(500);
		digitalWrite(CHS_MOT_DIR, LOW);
		currentHeigth = 0;
	}
}