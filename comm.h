#ifndef COMM_H_
#define COMM_H_

#include <stdint.h>

struct CarData
{
	//Misc car data
	int8_t battery_percentage;

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
	} lights;

	//RemoteControl
	struct {
		int8_t throttle;
		int8_t steer;
	} rc;
};

#endif /* COMM_H_ */
