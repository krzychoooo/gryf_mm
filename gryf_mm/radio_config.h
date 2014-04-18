/**
 * \file radio_config.h
 *
 *  @date Created on: 3 kwi 2014
 *   @Author: krzysztof
 */

#ifndef RADIO_CONFIG_H_
#define RADIO_CONFIG_H_

#include <avr/io.h>

#define NUMBER_SLAVE 8

extern uint8_t slaveModulesAddress[NUMBER_SLAVE];
extern uint8_t numberSlaveModules;
extern uint8_t EEslaveModulesAddress[NUMBER_SLAVE];
extern uint8_t EEnumberSlaveModules;
extern const uint8_t FlashslaveModulesAddress[NUMBER_SLAVE];
extern const uint8_t FlashnumberSlaveModules;

/** 
 *  \struct <TRC1180Config>
 *  \brief Konfiguracja modu�u RC1180
 */

typedef struct RC1180Config{
	uint8_t uIAddress[2];	/**  \var  TRC1180Config#uIAddress.
							 *  Member uIAddress  zawiera unikatowy adres
							 */
	uint8_t dIDAddres[2];	/**  \var  TRC1180Config#dIDAddres[2];
							*  Member dIDAddres zawiera adres celu
							*/
	uint8_t brAddress[2];	/**  \var TRC1180Config#brAddress[2];
							*  Member brAddress zawiera adres rozg�oszeniowy*/
	uint8_t bRateRS232[2];	/**  \var TRC1180Config#bRateRS232[2];
							*  Member bRateRS232 zawiera szybko�� transmisji rs232*/
	uint8_t bRateRadio[2];	/**  \var TRC1180Config#bRateRadio[2];
							*  Member bRateRadio zawiera szybko�� transmisji po radiu (sprawdzi�. Prawdopodobnie nie da si� ustawi� odzielnie brate dla rs232 i radia)*/
	uint8_t chanel[2];		/**  \var TRC1180Config#chanel[2];
							*  Member chanel zawiera numer kana�u*/
	uint8_t power[2];		/**  \var TRC1180Config#power[2];
							*  Member power zawiera poziom mocy od 1 do 5*/
	uint8_t rssi[2];		/**  \var TRC1180Config#rssi[2];
							*  Member rssi zawiera czy ma zwraca� RSSI*/
	uint8_t cRCMode[2];		/**  \var TRC1180Config#cRCMode[2];
							*  Member cRCMode zawiera czy ma obs�ugiwa� CRC*/
	uint8_t endChar[2];		/**  \var TRC1180Config#endChar[2];
							*  Member endChar zawiera znak po kt�rym nast�pi wys�anie ramki*/
	uint8_t addressMode[2];	/**  \var TRC1180Config#addressMode[2];
							*  Member addressMode zawiera tryb adresowania RC1180 */
} TRC1180Config;
//#define CONFIGSIZE 11;

void radioRC1180Init();
void setDestinationAddres(uint8_t destAddress);;
uint8_t sendCommandToRC1180(uint8_t command, uint8_t data);
void programMemoryRC1180(uint8_t *data, uint8_t numberData);
void copyConfigEEpromToRam();
void copyConfigRamToEEprom();
void copyConfigFlashToRam();
void setRC1180FromConfigRam();
void userSetRC1180(void);
void copyApplicationSetingFromFlashToRam();
void copyApplicationSetingFromEepromToRam();
void copyApplicationSetingFromRamToEeprom();


#endif /* RADIO_CONFIG_H_ */
