// SpektrumRC.h
// Author: Juraj Marcin

#ifndef _SPEKTRUMRC_h
#define _SPEKTRUMRC_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "comm.h"
#include "pindef.h"

#define SRC_STR_INV 748
#define SRC_STR_CTR 374
#define SRC_THR_CTR 378

class _SpektrumRC {

	private:
	volatile uint16_t strH, strL, str;
	volatile uint16_t thrH, thrL, thr, tthr;
	
	volatile uint8_t strIH = 0;
	volatile uint8_t thrIH = 0;

	volatile uint8_t pulseCounter = 0;
	
	public:
	volatile int8_t astrMode = 1;
	
	void init();
	
	void loop();
	
	void strInputInterr();
	
	void thrInputInterr();
	
	void astrOutputInterr();
	
	void updateCarData(CarData& cardata);
};

extern _SpektrumRC SpektrumRC;

#endif

