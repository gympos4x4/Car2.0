// eepromdef.h
// Author: Juraj Marcin


#ifndef EEPROMDEF_H_
#define EEPROMDEF_H_


#include <EEPROM.h>

#define EE_READ8(addr) (EEPROM.read(addr))
#define EE_READ16(addr) (EEPROM.read(addr) << 8 | EEPROM.read(addr + 1))

#define EE_WRITE8(addr, val) (EEPROM.write(addr, val))
#define EE_WRITE16(addr, val) EEPROM.write(addr, val >> 8); EEPROM.write(addr + 1, val & 0xFF)

#define EE_TEST (EE_READ8(0) == EE_CB0 && EE_READ8(1) == EE_CB1)

#define EE_RESET \
EE_WRITE8(0, EE_CB0);\
EE_WRITE8(1, EE_CB1);\
EE_WRITE16(LXS_ADDR, LXS_TRESHOLD)

#define EE_CB0 0x42
#define EE_CB1 0x16

#define LXS_ADDR 2
#define LXS_TRESHOLD 14

#endif /* EEPROMDEF_H_ */