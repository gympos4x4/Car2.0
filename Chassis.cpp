// Chassis.cpp
// Author: Juraj Marcin

#include "Chassis.h"

_Chassis Chassis;

void _Chassis::init() {
	pinMode(CHS_MOT_UP, OUTPUT);
	pinMode(CHS_MOT_DW, OUTPUT);
}

void _Chassis::setHeight(int8_t height) {
	if (height > 0/* && currentHeigth != 100*/) {
		digitalWrite(CHS_MOT_UP, HIGH);
		delay(200);
		digitalWrite(CHS_MOT_UP, LOW);
		currentHeigth = 100;
	} else if (height < 0/* && currentHeigth != -100*/) {
		digitalWrite(CHS_MOT_DW, HIGH);
		delay(200);
		digitalWrite(CHS_MOT_DW, LOW);
		currentHeigth = -100;
	}
}
