// pindef.h
// Author: Juraj Marcin

#ifndef PINS_H_
#define PINS_H_

#define PIN_OUT(DIR, PIN) (DIR |= _BV(PIN))

#define PIN_WRITE(PORT, PIN, VAL) ( VAL ? PORT |= _BV(PIN) : PORT &= ~_BV(PIN) )
#define PIN_WRITE_H(PORT, PIN) (PORT |= _BV(PIN))
#define PIN_WRITE_L(PORT, PIN) (PORT &= ~_BV(PIN))

#define VBAT_SENSE_PIN A0

//ADC
#define ADC_PIN_COUNT 1

//ESP8266
#define ESP_RST_PRT PORTE
#define ESP_RST_PIN PE3
#define ESP_SERIAL Serial2

//PARKINGSENSORS
#define PS_SENSOR_COUNT 0
#define PS_IR_DIR DDRJ
#define PS_IR_PRT PORTJ
#define PS_IR_PIN PJ7

//SPKR
#define SPKR_DIR DDRA
#define SPKR_PRT PORTA
#define SPKR_PIN PA0

//LIGHTS
#define LXS_PIN A7
#define LXS_ADP 7
#define LX_DIR DDRF
#define LX_PORT PORTF
#define LX0_FRONT_PIN PF6
#define LX1_REAR_PIN PF5
#define LX2_REV0_PIN PF4
#define LX3_REV1_PIN PF3
#define LX4_LEFT_PIN PF2
#define LX5_RIGHT_PIN PF1

//SPEKTRUM RC
#define STRI_PIN 49
#define STRO_PIN 45
#define ASTR_PIN 46
#define THRI_PIN 48
#define THRO_PIN 44

//CHASSIS
#define CHS_MOT_UP 4
#define CHS_MOT_DW 39

#endif /* PINS_H_ */