/*
 * radioFrame.c
 *
 *  Created on: 6 kwi 2014
 *      Author: krzysztofklimas@interia.pl
 */

/*
 * 			RC1180 CONNECT TO USART C
 */

#include "radioFrame.h"
#include "radio_config.h"
#include "USART/usartc0.h"
#include "usart/usartd0.h"
#include "timer0x.h"
#include <stdlib.h>
#include <util/delay.h>

volatile uint8_t outFrameBufferWrIndex;
volatile uint8_t outFrameBufferRdIndex;
uint8_t outFrameBuffer[OUTFRAMERADIOBUFFERSIZE];		// sk³adowane s¹ adresy i kody zdarzeñ z modu³ów które zosta³y odpytane

/*! \fn uint8_t lenData
* \brief calculate how many data read
* \variable uint8_t wrIndex
* \variable  uint8_t rdIndex
* \variable  uint8_t bufLen
* \return uint8_t how many data read from rdIndex to wrIndex
*/

uint8_t lenData(uint8_t wrIndex, uint8_t rdIndex,uint8_t bufLen){
	if(wrIndex >= rdIndex) return (wrIndex-rdIndex);
	return ((bufLen - rdIndex) + wrIndex);
}


void indexIncrement(volatile uint8_t *index, uint8_t len){
	*index++;
	if (*index == len){
		*index = 0;
	}
	}

// see rc11xx pdf length packet set to 4 (radio config)
void sendAlarmFrameRadio(){
	uint8_t i;

	setDestinationAddres(0);
	_delay_ms(5);
	putcharc0(0);									//destination address
	putcharc0(rc1180ConfigRam.uIAddress[1]);		//source address
	//putcharc0(lenData(outFrameBufferWrIndex, outFrameBufferRdIndex, OUTFRAMERADIOBUFFERSIZE));	//sprawdziæ czy da siê tak zrobiæ aby RC1180 wysy³a³ automatycznie zmienn¹ d³ugoœæ ramki
	putcharc0(1);									//len data = 1  
	if (outFrameBufferWrIndex == outFrameBufferRdIndex){
		putcharc0(0);
		return;
	}
	for(i=0; i!=1; i++){
			putcharc0(outFrameBuffer[outFrameBufferRdIndex]);
			outFrameBufferRdIndex++;
			if(outFrameBufferRdIndex == OUTFRAMERADIOBUFFERSIZE)outFrameBufferRdIndex = 0;
	}
}


void alarmSimulate(void){
	uint8_t i,j;

	j=random()%5;
	for(i=0; i!=j; i++){
		outFrameBuffer[outFrameBufferWrIndex++] = i+1;
		outFrameBuffer[outFrameBufferWrIndex++] = random()%4 + 1;
	}
}

uint8_t getFrameRadio() {

	uint8_t i,data;
	uint16_t iData;

	if (rx_counter_usartc0) {
		iData = getcharc0Time(10);			//destination address == my addres
		data = (uint8_t) iData;
		if (data != rc1180ConfigRam.uIAddress[1])
		{
			return 4;						//frame OK but not my address
		}
		iData = getcharc0Time(10);			// sender radio address
		
		iData = getcharc0Time(10);			//  command
				
		i = (uint8_t) iData;
		if (i != '?'){
			return 2;						// all OK but uncknow command
		}

		iData = getcharc0Time(10);			//get 0

		iData = getcharc0Time(10);			// get rssi
		printf("P%d ",((uint8_t)iData)/2);
		while(rx_counter_usartc0){			// clear buffer
			iData = getcharc0Time(10);
		}
		return 0;
	} else
		return 1;
}

uint8_t newgetFrameRadio() {

	uint8_t i,data, errorCode;
	uint16_t iData;

	errorCode = 0;
	if (rx_counter_usartc0) {
		iData = getcharc0Time(10);			//destination address == my addres
		data = (uint8_t) iData;
		if (data != rc1180ConfigRam.uIAddress[1])
		{
			errorCode |= 1<<4;						//frame OK but not my address
		}
		iData = getcharc0Time(10);			// sender radio address
		
		iData = getcharc0Time(10);			//  command
		
		i = (uint8_t) iData;
		if (i != '?'){
			errorCode |= 1<<2;						// all OK but uncknow command
		}

		iData = getcharc0Time(10);			//get 0

		iData = getcharc0Time(10);			// get rssi
		printf("P%d ",((uint8_t)iData)/2);
		while(rx_counter_usartc0){			// clear buffer
			iData = getcharc0Time(10);
		}
		return errorCode;
	} else
	return 1;
}
