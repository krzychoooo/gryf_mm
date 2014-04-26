/**
 * \file moduleConfig.h
 *
 * Created: 2014-04-20 21:24:12
 *  Author: krzysztofklimas@interia.pl
 */ 


#ifndef MODULECONFIG_H_
#define MODULECONFIG_H_

#include <avr/pgmspace.h>
#include <avr/eeprom.h>


/*
* \struct <TModuleConfig>
* \brief kody alarmów i powrotów

* alarmy generowane w przerwaniach timer0
*/

#define NUMBERALARMCODE 8

typedef struct modConfig{
	uint8_t alarmCode[NUMBERALARMCODE];			/* \var alarmCode[] */
	uint8_t returnAlarmCode[NUMBERALARMCODE];		/* \var returnAlarmCode */
} TModuleConfig;


extern TModuleConfig moduleConfigRam;
extern TModuleConfig eeModuleConfig EEMEM;
extern const TModuleConfig moduleConfigFlash PROGMEM;

void copyModuleConfigFlashToRam();
void copyModuleConfigEEpromToRam();
void copyModuleConfigRamToEEprom();
void userSetModule();

#endif /* MODULECONFIG_H_ */