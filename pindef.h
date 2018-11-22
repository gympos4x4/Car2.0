// pindef.h
// Author: Juraj Marcin

#ifndef PINS_H_
#define PINS_H_

#define VBAT_SENSE_PIN A0

//ESP8266
#define ESP_RST_PIN 5
#define ESP_SERIAL Serial2

//PARKINGSENSORS
#define PS_IR_PIN 69

//SPKR
#define SPKR_PIN 62
//#define PIEZO_PIN 62

//LIGHTS
#define LXS_PIN A7
#define LX0_FRONT_PIN 55
#define LX1_REAR_PIN 56
#define LX2_REVERSE_PIN 57
#define LX3_LEFT_PIN 58
#define LX4_RIGHT_PIN 59
#define LX5_PIN 60

//SPEKTRUM RC
#define STRI_PIN 49
#define STRO_PIN 45
#define ASTR_PIN 46
#define THRI_PIN 48
#define THRO_PIN 44

//CHASSIS
#define CHS_MOT_PWM 4
#define CHS_MOT_DIR 39

#endif /* PINS_H_ */