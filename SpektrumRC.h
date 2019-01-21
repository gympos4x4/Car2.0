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

#define SRC_STR_INV 742
#define SRC_STR_CTR 382
#define SRC_THR_CTR 371

class _SpektrumRC {

	private:
	volatile uint16_t strH, strL, str;
	volatile uint16_t thrH, thrL, thr, tthr;
	
	volatile uint8_t strIH = 0;
	volatile uint8_t thrIH = 0;

	volatile uint8_t pulseCounter = 0;

	public:
	void init();
	
	void loop(int8_t astrMode);
	
	void strInputInterr();
	
	void thrInputInterr();
	
	void astrOutputInterr();
	
	void updateCarData(CarData& cardata);
};

extern _SpektrumRC SpektrumRC;

#endif

