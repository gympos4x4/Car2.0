// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {
	PIN_OUT(CHS_DIR_DIR, CHS_DIR_PIN);
	PIN_OUT(CHS_PWM_DIR, CHS_PWM_PIN);
}

void _Chassis::setHeight(int8_t height) {
	if (height > 0) {
		PIN_WRITE_H(CHS_DIR_PORT, CHS_DIR_PIN);
		PIN_WRITE_H(CHS_PWM_PORT, CHS_PWM_PIN);
		delay(200);
		PIN_WRITE_L(CHS_PWM_PORT, CHS_PWM_PIN);
		delay(200);
	} else if (height < 0) {
		PIN_WRITE_L(CHS_DIR_PORT, CHS_DIR_PIN);
		PIN_WRITE_H(CHS_PWM_PORT, CHS_PWM_PIN);
		delay(200);
		PIN_WRITE_L(CHS_PWM_PORT, CHS_PWM_PIN);
		delay(200);
	}
}
