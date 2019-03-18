#ifndef COMM_H_
#define COMM_H_

#include <stdint.h>

#define COMM_MASK_SYS (0b111 << 5)
#define COMM_MASK_FUN (COMM_MASK_SYS | 0b11 << 3)
#define COMM_MASK_VAL (0b111)

#define COMM_LXS (0b001 << 5)
#define COMM_SRC (0b010 << 5)
#define COMM_TAL (0b011 << 5)
#define COMM_CHS (0b100 << 5)
#define COMM_PRS (0b101 << 5)
#define COMM_CTR (0b111 << 5)

// LIGHTS //
#define COMM_LXS_SETTHRESHOLD (COMM_LXS | 0b01 << 3)
#define COMM_LXS_BEAMS (COMM_LXS | 0b10 << 3)

#define COMM_LXS_BEAMS_AUTO (COMM_LXS_BEAMS | 0b000)
#define COMM_LXS_BEAMS_OFF (COMM_LXS_BEAMS | 0b010)
#define COMM_LXS_BEAMS_ON (COMM_LXS_BEAMS | 0b011)

// SPEKTRUM RC //
#define COMM_SRC_MODE (COMM_SRC | 0b00 << 3)

#define COMM_SRC_MODE_NORMAL (COMM_SRC_MODE | 0b000)
#define COMM_SRC_MODE_LOCK (COMM_SRC_MODE | 0b001)
#define COMM_SRC_MODE_CRAB (COMM_SRC_MODE | 0b010)

// TILTALARM //
#define COMM_TAL_STATE (COMM_TAL | 0b00 << 3)

// CHASSIS //
#define COMM_CHS_STEP_UP (COMM_CHS | 0b10 << 3)
#define COMM_CHS_STEP_DOWN (COMM_CHS | 0b11 << 3)

struct CarData
{
	//Misc car data
	int16_t battery_percentage;

	//TiltAlarm
	struct
	{
		int16_t degrees;
		bool tilted;
	} tilt;

	//Lights
	struct
	{
		bool is_below_threshold;
		int16_t level;
	} lights;

	//RemoteControl
	struct {
		int8_t throttle;
		int8_t steer;
	} rc;

	//ControllerData
	struct {
		int8_t astr_mode;
		int8_t beams_mode;
	} ctrl;

	//ParkingSensors
	struct {
		int8_t sensor_data[0];
	} parking;
};

struct ControllerData {
	int8_t height;
	int8_t astr_mode;
};

#endif /* COMM_H_ */
