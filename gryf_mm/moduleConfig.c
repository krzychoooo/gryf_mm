/*
* moduleConfig.c
*
* Created: 2014-04-20 21:30:51
*  Author: krzysztofklimas@interia.pl
*/


#include <avr/io.h>
#include <stdio.h>
#include "moduleConfig.h"


TModuleConfig moduleConfigRam;

const TModuleConfig moduleConfigFlash PROGMEM = {
	{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	{0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18}
};

TModuleConfig eeModuleConfig EEMEM;

void copyModuleConfigFlashToRam() {
	memcpy_P(&moduleConfigRam, &moduleConfigFlash, sizeof(moduleConfigRam));
}

void copyModuleConfigEEpromToRam() {
	eeprom_read_block(&moduleConfigRam, &eeModuleConfig, sizeof(moduleConfigRam));
}

void copyModuleConfigRamToEEprom() {
	eeprom_write_block(&moduleConfigRam, &eeModuleConfig, sizeof(moduleConfigRam));
}

void userSetModule(){
	uint16_t getData;
	uint8_t i;

	
	while (1){
		printf("%cUSTAWIENIA MODU£U\n\r",12);
		printf("\n\n0 Wyjœcie z edycji\n\r");
		printf("1 kody zwaræ   ");
		for(i=0; i!=NUMBERALARMCODE; i++){
			printf("%02X ",moduleConfigRam.alarmCode[i]);
		}
		printf("\n\r2 kody rozwaræ ");
		for(i=0; i!=NUMBERALARMCODE; i++){
			printf("%02X ",moduleConfigRam.returnAlarmCode[i]);
		}
		
		scanf("%d", &getData);
		switch(getData){
			case 0:{
				copyModuleConfigRamToEEprom();
				return;
			}
			case 1:{
				for(i=0; i!=NUMBERALARMCODE; i++){
					printf("\n\rpodaj now¹ wartoœæ dla wejœcia %d\n\r",i+1);
					scanf("%x", &getData);
					moduleConfigRam.alarmCode[i] = getData;
				}
				break;
			}
				case 2:{
					for(i=0; i!=NUMBERALARMCODE; i++){
						printf("\n\rpodaj now¹ wartoœæ dla wejœcia %d\n\r",i+1);
						scanf("%x", &getData);
						moduleConfigRam.returnAlarmCode[i] = getData;
						
					}
					break;
				}
			}
		}
	}
