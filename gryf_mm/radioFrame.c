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
#include "timer0x.h"
#include <stdlib.h>

volatile uint8_t outFrameBufferWrIndex;
volatile uint8_t outFrameBufferRdIndex;
uint8_t outFrameBuffer[OUTFRAMERADIOBUFFERSIZE];		// sk�adowane s� adresy i kody zdarze� z modu��w kt�re zosta�y odpytane


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


void indexIncrement(volatile uint8_t* index, uint8_t len){
	*index++;
	if (*index == len){
		*index = 0;
	}
	}

// see rc11xx pdf length packet set to 4 (radio config)
void sendAlarmFrameRadio(){
	uint8_t i;

	putcharc0(0);									//destination address
	putcharc0(rc1180ConfigRam.uIAddress[1]);		//source address
	//putcharc0(lenData(outFrameBufferWrIndex, outFrameBufferRdIndex, OUTFRAMERADIOBUFFERSIZE));	//sprawdzi� czy da si� tak zrobi� aby RC1180 wysy�a� automatycznie zmienn� d�ugo�� ramki
	putcharc0(1);									//len data = 1  
	if (outFrameBufferWrIndex == outFrameBufferRdIndex){
		putcharc0(0);
		return;
	}
	for(i=0; i!=1; i++){
			putcharc0(outFrameBuffer[outFrameBufferRdIndex]);
			indexIncrement(&outFrameBufferRdIndex, OUTFRAMERADIOBUFFERSIZE);
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

	uint8_t i;
	uint16_t iData;

	if (rx_counter_usartc0) {
		iData = getcharc0Time(10);			//destination address == my addres
		if ((iData & 0x0100) == 0)
			return 1;						// no data in buffer
		if (iData != rc1180ConfigRam.uIAddress[1])
		{
			return 4;						//frame OK but not my address
		}
		iData = getcharc0Time(10);			// sender radio address
		iData = getcharc0Time(10);			
		i = (uint8_t) iData;
		if (i != '?'){
			return 2;						// all OK but uncknow command
		}
		return 0;
	} else
		return 1;
}


