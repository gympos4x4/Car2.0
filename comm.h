#ifndef COMM_H_
#define COMM_H_

#include <stdint.h>

#define COMM_MASK 0b11100000
#define COMM_MASK_0 0b1
#define COMM_MASK_1 0b11
#define COMM_MASK_2 0b111
#define COMM_MASK_3 0b1111
#define COMM_MASK_4 0b11111
#define COMM_LIGHTS 0b00100000
#define COMM_SPEKTRUM 0b01000000
#define COMM_TILT 0b01100000
#define COMM_CHASSIS 0b10000000
#define COMM_PARKING 0b10100000

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

	//ParkingSensors
	struct {
		int8_t sensor_data[4];
	} parking;
};

struct ControllerData {
	int8_t height;
	int8_t astr_mode;
};

#endif /* COMM_H_ */
