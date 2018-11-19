// ESP8266.cpp
// Author: Juraj Marcin

#include "ESP8266.h"

#define DEBUG

_ESP8266 ESP8266;

void _ESP8266::init() {
	Serial.begin(9600);
	pinMode(ESP_RST_PIN, OUTPUT);
	//bitWrite(PORTE, 2, 1);
	digitalWrite(ESP_RST_PIN, HIGH);
	ESP_SERIAL.begin(115200);
	ESP_SERIAL.setTimeout(ES_TIMEOUT);
	cmd("AT+RST");
	serialFind("ready", 5);
	cmd("ATE0");
	serialFind("OK", 2);
	cmd("AT+CWMODE_CUR=3");
	serialFind("OK", 2);
	cmd("AT+CWDHCP_CUR=2,0");
	serialFind("OK", 2);
	cmd("AT+CWSAP_CUR=\"ColumbaRacing\",\"ImunituPreMo\",13,3,1,0");
	serialFind("OK", 2);
	//cmd("AT+CIPMUX=1");
	cmd("AT+CIPMUX=0");
	serialFind("OK", 2);
	//cmd("AT+CIPSERVER=1,1181");
	cmd("AT+CIPSTART=\"UDP\",\"0.0.0.0\",1181,1181,2");
	serialFind("OK", 2);
	#ifdef DEBUG
	Serial.println("Server started!");
	#endif // DEBUG
}

bool _ESP8266::sendCarData(CarData* data) {
	ESP_SERIAL.print("AT+CIPSEND=");
	ESP_SERIAL.println(sizeof(CarData) * 2 + 1);
	uint64_t cmdtxend = millis();
	bool gotresponse = false;
	while (millis() < cmdtxend + ES_TIMEOUT) {
		if (ESP_SERIAL.read() == '>') {
			gotresponse = true;
			break;
		}
	}
	if (gotresponse) {
		for(uint8_t i = 0; i < sizeof(CarData); i++) {
			ESP_SERIAL.print(((byte*)data)[i] / 16, HEX);
			ESP_SERIAL.print(((byte*)data)[i] % 16, HEX);
		}
		ESP_SERIAL.println("\n");
		return true;
	}
	ESP_SERIAL.println("+++");
	return false;
}

void _ESP8266::loop() {
	if (ESP_SERIAL.available()) {
		char serRead = ESP_SERIAL.read();
		if (serRead == '+') {
			Serial.print("\r\n<DATA>");
			/*uint8_t* buffer[6];
			ESP_SERIAL.readBytes(*buffer, 6);*/
			for (uint64_t i = 0; i < 9; i++) {
				Serial.write(ESP_SERIAL.read());
			}
			Serial.println("</DATA>\r\n");
		} else {
			Serial.write(serRead);
		}
	}
}

void _ESP8266::cmd(const char cmd[]) {
	ESP_SERIAL.println(cmd);
}

void _ESP8266::serialFind(const char target[], uint8_t targetLenght) {
	uint8_t i = 0;
	while (i < targetLenght) {
		if (ESP_SERIAL.available()) {
			if (ESP_SERIAL.read() == target[i])
			i++;
			else
			i = 0;
		}
	}
}