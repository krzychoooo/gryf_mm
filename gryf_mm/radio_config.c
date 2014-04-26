#include <avr/io.h>
#include "radio_config.h"
#include "pcb.h"
#include "USART/usartc0.h"
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <stdio.h>

const TRC1180Config rc1180ConfigFlash PROGMEM = { 
		{ 0x19, 1 },		//UIAddress
		{ 0x21, 0 },		//DIDAddres
		{ 0x28, 255 },		//BrAddress
		{ 0x1a, 0x01},		//System id
		{ 0x30, 5 },		//BRateRS232
		{ 0x30, 5 },		//BRateRadio
		{ 0x00, 13 },		//Chanel
		{ 0x01, 5 },		//Power
		{ 0x05, 1 },		//Rssi
		{ 0x15, 2 },		//crc
		{ 0x11, 0 },		//End character
		{ 0x14, 2 },		//address mode
		{ 0x0e, 0 },		//Member Max packet	length high	byte.
		{ 0x0f, 4 },		//Member Max packet	length low	byte.
		{ 0x10, 1 }			//Member Time before modem timeout and transmitting the buffer 1 -> 16ms
};

TRC1180Config rc1180ConfigRam;
TRC1180Config rc1180ConfigEEPROM EEMEM;

void copyConfigRadioEEpromToRam() {
	eeprom_read_block(&rc1180ConfigRam, &rc1180ConfigEEPROM, sizeof(rc1180ConfigRam));
}

void copyConfigRadioRamToEEprom() {
	eeprom_write_block(&rc1180ConfigRam, &rc1180ConfigEEPROM, sizeof(rc1180ConfigRam));
}

void copyConfigRadioFlashToRam() {
	memcpy_P(&rc1180ConfigRam, &rc1180ConfigFlash, sizeof(rc1180ConfigRam));
}

void setRC1180FromConfigRam() {
	programMemoryRC1180(&rc1180ConfigRam.uIAddress[0], sizeof(rc1180ConfigRam));
}

void radioRC1180Init() {
	CONFIG_RADIO_DIR_OUT;
	putcharc0('X');
	CONFIG_RADIO_OFF;
}

void setDestinationAddres(uint8_t destAddress) {
	sendCommandToRC1180('T', destAddress);
}


uint8_t sendCommandToRC1180(uint8_t command, uint8_t data) {
	uint8_t retData = 0;
	
	CONFIG_RADIO_ON;  //linia config -> 0V
	getcharc0();  // get '>'

	switch (command) {

	case 'C': {			// set chanel
		putcharc0(command);
		getcharc0();
		putcharc0(data);
		getcharc0();
		break;
	}
	case 'P': {			// set Power
		putcharc0(command);
		getcharc0();
		putcharc0(data);
		getcharc0();
		break;
	}
	case 'T': {			// set target addres DID
		putcharc0(command);
		getcharc0();
		putcharc0(data);
		getcharc0();
		break;
	}
	case 'S': {			//  get RSSI
		putcharc0(command);
		retData = getcharc0();
		break;
	}
	case 'Y': {				//  get data from eeprom
		putcharc0(command);
		getcharc0();
		putcharc0(data);	// send address
		retData = getcharc0();
		break;
	}
	case 'X': {			// end Command mode
		putcharc0(command);
		break;
	}
	case 'Z': {			// enter SLEEP
		putcharc0(command);
		getcharc0();
		break;
	}
	case 'R': {			// enter ROUTER MODE (ONLY FOR TINY MESH VERSION)
		putcharc0(command);
		getcharc0();
		break;
	}
	case 'G': {			// enter GATEWAY MODE (ONLY FOR TINY MESH VERSION)
		putcharc0(command);
		getcharc0();
		break;
	}
	case 'N': {			// enter END NODE (ONLY FOR TINY MESH VERSION)
		putcharc0(command);
		getcharc0();
		break;
	}
	}

	CONFIG_RADIO_OFF;		//linia config -> VCC
	if (command != 'X')
		putcharc0('X');
	return retData;
}

/**
 * param *data		pointer to table data
 * param numberData	number to sent data  (numberData = data.len/2)  {adr1, data1, ..... adrn, datan}
 */
void programMemoryRC1180(uint8_t *data, uint8_t numberData) {
	uint8_t i;
	uint8_t j;

	CONFIG_RADIO_ON;

	printf("test\n");

	j = getcharc0();		// rec '>'

	printf("test=%c\n",j);

	putcharc0('M');
//	getcharc0();
	printf("test po M =%c\n",j);
	for (i = 0; i != numberData/2; i++) {
		putcharc0(*data++);
		putcharc0(*data++);
	}

	putcharc0(0xff);
//	getcharc0();
	putcharc0('X');
	CONFIG_RADIO_OFF;
}

void printNewVal() {
	printf("podaj now¹ wartoœæ\n");
}

/*! \fn void userSetRC1180(void)
* \brief ustawia parametry w strukturze rc1180ConfigRam i zapisuje do eeprom
 uint8_t UIAddress;
 uint8_t DIDAddres;
 uint8_t BrAddress;
 uint8_t BRateRS232;
 uint8_t BRateRadio;
 uint8_t Chanel;
 uint8_t Power;
 uint8_t Rssi;
 uint8_t CRCMode;
 */
void userSetRC1180(void) {
	//	uint8_t i;
	uint16_t getData;
	//	uint8_t *ptr;

	printf("%cUSTAWIENIA RADIOWE\n",12);

	while (1) {
		printf("0 Wyjœcie z edycji\n");
		printf("1 Unikatowy adres %d\n", rc1180ConfigRam.uIAddress[1]);
		printf("2 Adres rozg³oszeniowy %d\n", rc1180ConfigRam.brAddress[1]);
		printf("3 Szybkoœæ transmisji %d\n", rc1180ConfigRam.bRateRS232[1]);
		printf("4 Kana³ radiowy %d\n", rc1180ConfigRam.chanel[1]);
		printf("5 Moc od 1 do 5 - %d\n", rc1180ConfigRam.power[1]);
		printf("6 CRC 0-brak; 1-kontrola aktywna%d\n", rc1180ConfigRam.cRCMode[1]);
		printf("7 System id %d",rc1180ConfigRam.sysAddress[1]);
		printf("\nWybierz numer parametru do edycji\n");

		scanf("%d", &getData);
		switch (getData) {
			case 0: {
				printf("Koniec konfiguracji radia\n");
				copyConfigRadioRamToEEprom();
				return;
				break;
			}
			case 1: {
				printNewVal();
				scanf("%d", &getData);
				rc1180ConfigRam.uIAddress[1] = (uint8_t) getData;
				break;
			}
			case 2: {
				printNewVal();
				scanf("%d", &getData);
				rc1180ConfigRam.brAddress[1] = (uint8_t) getData;
				break;
			}
			case 3: {
				printNewVal();
				scanf("%d", &getData);
				rc1180ConfigRam.bRateRS232[1] = (uint8_t) getData;
				break;
			}
			case 4: {
				printNewVal();
				scanf("%d", &getData);
				rc1180ConfigRam.chanel[1] = (uint8_t) getData;
				break;
			}
			case 5: {
				printNewVal();
				scanf("%i", &getData);
				rc1180ConfigRam.power[1] = (uint8_t) getData;
				break;
			}
			case 6: {
				printNewVal();
				scanf("%d", &getData);
				rc1180ConfigRam.cRCMode[1] = (uint8_t) getData;
				break;
		}
		case 7: {
			printNewVal();
			scanf("%d", &getData);
			rc1180ConfigRam.sysAddress[1] = (uint8_t) getData;
			break;
		}
			default: {
				printf("wybierz poprawny numer");
			}
		}
	}
}



