// SpektrumRC.h
// Author: Juraj Marcin

#ifndef _SPEKTRUMRC_h
#define _SPEKTRUMRC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Servo.h>

#include "comm.h"
#include "pindef.h"

#define SR_STR_MIN 995
#define SR_STR_DMIN 1480
#define SR_STR_DMAX 1495
#define SR_STR_MAX 1980
#define SR_THR_MIN 1090
#define SR_THR_DMIN 1498
#define SR_THR_DMAX 1507
#define SR_THR_MAX 1890

#define SR_ASR_MIN 130
#define SR_ASR_CEN 120
#define SR_ASR_MAX 70

class _SpektrumRC {
	
	Servo aServo;

	int8_t lastThrottle;
	int8_t lastSteer;
	
	public:

	void init();
	void loop();

	int8_t getThrottle();
	int8_t getSteer();

	void updateCarData(class CarData& cardata);

	_SpektrumRC();
	~_SpektrumRC();
	
};

extern _SpektrumRC SpektrumRC;

#endif
