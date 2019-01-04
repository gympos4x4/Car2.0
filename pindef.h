// pindef.h
// Author: Juraj Marcin

#ifndef _PINDEF_H_
#define _PINDEF_H_

#define BOARD_REV 1

#define PIN_OUT(DIR, PIN) (DIR |= _BV(PIN))
#define PIN_IN(DIR, PIN) (DIR &= ~_BV(PIN))

#define PIN_WRITE(PORT, PIN, VAL) (VAL ? PORT |= _BV(PIN) : PORT &= ~_BV(PIN))
#define PIN_WRITE_H(PORT, PIN) (PORT |= _BV(PIN))
#define PIN_WRITE_L(PORT, PIN) (PORT &= ~_BV(PIN))

#if BOARD_REV == 0

#define VBT_SENSE_PIN 0

//ADC
#define ADC_PIN_COUNT 2
#define ADC_NEXT(ADCPIN) (ADCPIN + 1 >= ADC_PIN_COUNT ? 0 : ADCPIN + 1)

//ESP8266
#define ESP_DIR DDRE
#define ESP_PRT PORTE
#define ESP_RST_PIN PE3
#define ESP_EN_PIN PE2
#define ESP_SERIAL Serial2

//PARKINGSENSORS
#define PRS_SENSOR_COUNT 0
#define PRS_IR_DIR DDRK
#define PRS_IR_PRT PORTK
#define PRS_IR_PIN PK7

//SPEAKER
#define SPK_DIR DDRK
#define SPK_PRT PORTK
#define SPK_PIN PK0

//LIGHTS
#define LXS_SENSOR_PIN 7
#define LXS_DIR DDRF
#define LXS_PORT PORTF
#define LXS_C0_FRONT_PIN PF6
#define LXS_C1_REAR_PIN PF5
#define LXS_C2_REV0_PIN PF4
#define LXS_C3_REV1_PIN PF3
#define LXS_C4_LEFT_PIN PF2
#define LXS_C5_RIGHT_PIN PF1

//SPEKTRUM RC
#define SRC_ASTR_DIR DDRL
#define SRC_ASTR_PIN PL3

//CHASSIS
#define CHS_MOT_UP 4
#define CHS_MOT_DW 39

#else

#if BOARD_REV == 1

#define VBT_SENSE_PIN 0

//ADC
#define ADC_PIN_COUNT 3
#define ADC_NEXT(ADCPIN) (ADCPIN + 1 >= ADC_PIN_COUNT ? 0 : ADCPIN + 1)

//ESP8266
#define ESP_DIR DDRE
#define ESP_PRT PORTE
#define ESP_RST_PIN PE3
#define ESP_EN_PIN PE2
#define ESP_SERIAL Serial2

//PARKINGSENSORS
#define PRS_SENSOR_COUNT 1
#define PRS_SENSOR0_PIN 8
#define PRS_IR_DIR DDRJ
#define PRS_IR_PRT PORTJ
#define PRS_IR_PIN PJ7

//SPEAKER
#define SPK_DIR DDRA
#define SPK_PRT PORTA
#define SPK_PIN PA0

//LIGHTS
#define LXS_SENSOR_PIN 7
#define LXS_DIR DDRF
#define LXS_PORT PORTF
#define LXS_C0_FRONT_PIN PF6
#define LXS_C1_REAR_PIN PF5
#define LXS_C2_REV0_PIN PF4
#define LXS_C3_REV1_PIN PF3
#define LXS_C4_LEFT_PIN PF2
#define LXS_C5_RIGHT_PIN PF1

//SPEKTRUM RC
#define SRC_ASTR_DIR DDRL
#define SRC_ASTR_PIN PL3

//CHASSIS
#define CHS_MOT_UP 4
#define CHS_MOT_DW 39

#endif /* BOARD_REV */

#endif /* BOARD_REV */


#endif /* _PINDEF_H_ */