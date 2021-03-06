// ESP8266.cpp
// Author: Juraj Marcin

#include "ESP8266.h"

#define DEBUG

_ESP8266 ESP8266;

void _ESP8266::init() {
	Serial.println("DECONFIGURING NETWORK...");
	PIN_OUT(ESP_DIR, ESP_RST_PIN);
	PIN_WRITE_H(ESP_PRT, ESP_RST_PIN);
	PIN_OUT(ESP_DIR, ESP_EN_PIN);
	PIN_WRITE_H(ESP_PRT, ESP_EN_PIN);
	ESP_SERIAL.begin(115200);
	ESP_SERIAL.setTimeout(ES_TIMEOUT);
	cmd("AT+RST");
	serialFind("ready", 5);
	cmd("ATE0");
	serialFind("OK", 2);
	cmd("AT+CWMODE_CUR=3");
	serialFind("OK", 2);
	cmd("AT+CWDHCP_CUR=2,1");
	serialFind("OK", 2);
	cmd(ESP_AP);
	serialFind("OK", 2);
	//cmd("AT+CIPMUX=1");
	cmd("AT+CIPMUX=0");
	serialFind("OK", 2);
	//cmd("AT+CIPSERVER=1,1181");
	cmd("AT+CIPSTART=\"UDP\",\"0.0.0.0\",1181,1181,2");
	serialFind("OK", 2);
	cmd("AT+CIPDINFO=0");
	serialFind("OK", 2);
	Serial.println("NETWORK CONFIGURATION DONE");
	gotResponse = true;
}

bool _ESP8266::sendCarData(CarData* data) {
	if (gotResponse) {
		ESP_SERIAL.print("AT+CIPSEND=");
		ESP_SERIAL.println(sizeof(CarData));
	}
	uint64_t cmdtxend = millis();
	while (millis() < cmdtxend + ES_TIMEOUT) {
		if (ESP_SERIAL.read() == '>') {
			gotResponse = true;
			break;
		}
	}
	if (gotResponse) {
		for(uint8_t i = 0; i < sizeof(CarData); i++) {
			ESP_SERIAL.write(((uint8_t*)data)[i]);
		}
		return true;
	}
	return false;
}

void _ESP8266::loop(ControllerData* data) {
	uint8_t i = 0;
	bool timeoutfail = false;
	uint64_t start = 0;
	while (ESP_SERIAL.available()) {
		char serRead = ESP_SERIAL.read();
		if (serRead == '+') {
			uint8_t buffer[6];
			for (uint8_t j = 0; j < 6; j++) {
				start = millis();
				while(!ESP_SERIAL.available()) {
					if (millis() > start + ES_TIMEOUT) {
						timeoutfail = true;
						break;
					}
					if (timeoutfail) break;
				}
				buffer[j] = ESP_SERIAL.read();
			}
			if (timeoutfail) {
				#ifdef DEBUG
				Serial.println("PACKET TIMEOUT");
				#endif // DEBUG
			} else {
				while(!ESP_SERIAL.available());
				uint8_t b0 = ESP_SERIAL.read();
				uint8_t b0sys = b0 & COMM_MASK_SYS;
				uint8_t b0fun = b0 & COMM_MASK_FUN;
				uint8_t b0val = b0 & COMM_MASK_VAL;
				#ifdef DEBUG
				Serial.print("<DATA>");
				Serial.print(b0, HEX); Serial.print(' ');
				Serial.println("</DATA>");
				#endif // DEBUG
				switch (b0sys) {
				case COMM_LXS:
					if (b0fun == COMM_LXS_SETTHRESHOLD) {
						Lights.setTreshold();
						Serial.println("LXS_SETTHRESHOLD");
					} else if (b0fun == COMM_LXS_BEAMS) {
						Lights.beamsMode = b0val;
						Serial.print("LXS_BEAMS ");
						Serial.println(b0val);
					}
					// TODO: indicators
					break;
				case COMM_SRC:
					if (b0 == COMM_SRC_MODE_NORMAL) {
						SpektrumRC.astrMode = 1;
						Serial.println("SRC_MODE_NORMAL");
					} else if (b0 == COMM_SRC_MODE_LOCK) {
						SpektrumRC.astrMode = 0;
						Serial.println("SRC_MODE_LOCK");
					} else if (b0 == COMM_SRC_MODE_CRAB) {
						SpektrumRC.astrMode = -1;
						Serial.println("SRC_MODE_CRAB");
					}
					// TODO: values
					break;
				case COMM_TAL:
					if (b0fun == COMM_TAL_STATE) {
						TiltAlarm.enabled = b0val;
						Serial.print("TA_ENABLE ");
						Serial.println(b0val);
					}
					// TODO: threshold
					break;
				case COMM_CHS:
					if (b0fun == COMM_CHS_STEP_UP) {
						((uint8_t*)data)[0] = b0val * 16;
						Serial.print("CH_UP ");
						Serial.println(b0val);
					} else if (b0fun == COMM_CHS_STEP_DOWN) {
						((uint8_t*)data)[0] = b0val * -16;
						Serial.print("CH_DW");
						Serial.println (b0val);
					}
					break;
				case COMM_PRS:
					// TODO: PARKING SENSORS
					break;
				case COMM_CTR:
					Serial.println("CTR_CONNECT");
					break;
				}
				/*for (uint8_t k = 0; k < sizeof(ControllerData); k++) {
					while(!ESP_SERIAL.available());
					((uint8_t*)data)[k] = ESP_SERIAL.read();
					#ifdef DEBUG
					Serial.print(((uint8_t*)data)[k], HEX); Serial.print(' ');
					#endif // DEBUG
				}*/
			}
		}
		if (i > 64) { Serial.println("broke"); break; }
		i++;
	}
}

void _ESP8266::cmd(const char cmd[]) {
	ESP_SERIAL.println(cmd);
}

void _ESP8266::serialFind(const char target[], uint8_t targetLenght) {
	uint8_t i = 0;
	uint64_t searchstart = millis();
	while (i < targetLenght) {
		if (ESP_SERIAL.available()) {
			if (ESP_SERIAL.read() == target[i])
				i++;
			else
				i = 0;
		}
	}
}