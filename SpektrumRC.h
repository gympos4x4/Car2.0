// SpektrumRC.h
// Author: Juraj Marcin

#ifndef _SPEKTRUMRC_h
#define _SPEKTRUMRC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define SR_STR_PIN 7
#define SR_THR_PIN 8
#define SR_STR_MIN 990
#define SR_STR_DMIN 1474
#define SR_STR_DMAX 1481
#define SR_STR_MAX 1990
#define SR_THR_MIN 1090
#define SR_THR_DMIN 1498
#define SR_THR_DMAX 1507
#define SR_THR_MAX 1890

#include "comm.h"

class _SpektrumRC {

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
