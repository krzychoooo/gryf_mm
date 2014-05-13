/*
 * timer0.c
 *
 *  Created on: 8 kwi 2014
 *      Author: krzysztofklimas@interia.pl
 */

#include "timer0x.h"
#include <util/atomic.h>
#include "pcb.h"
#include "radioFrame.h"
#include "moduleConfig.h"

volatile uint8_t *timer0T;
volatile uint8_t ledTimer, inputPortTimer, newInputValue, OldInputValue;

// Timer/Counter TCC0 initialization
void tcc0_init(void)
{

	cli();

	TCC0.INTCTRLA     =    TC_OVFINTLVL_LO_gc;         // przepe³nienie ma generowaæ przerwanie LO
	PMIC.CTRL         =    PMIC_LOLVLEN_bm;            // odblokowanie przerwañ o priorytecie LO
	// konfiguracja timera
	TCC0.CTRLB        =    TC_WGMODE_NORMAL_gc;        // tryb normalny
	//  TCC0.CTRLFSET     =    TC0_DIR_bm;                 // liczenie w dó³
	TCC0.CTRLA        =    TC_CLKSEL_DIV256_gc;       // ustawienie preskalera i uruchomienie timera
	TCC0.PER = 1250;
	// Restore interrupts enabled/disabled state
	sei();
}

void registerTimerInTimer0( volatile uint8_t * time){
	timer0T = time;
}

uint8_t getInputValue(){
	uint8_t data,i;
	
	data = PORTD.IN & 0x03;
	data = data<<2;
	i = PORTC.IN & 0XC0;
	i = i>>6;
	data |= i;
	//data = PORTC.IN & 0XC0;
	//data = data>>4;
	//data |= PORTD.IN & 0x03;

	return data;
}


// Timer/Counter TCC0 Overflow/Underflow interrupt service routine
ISR (TCC0_OVF_vect)
{
	uint8_t xorData, inTemp, i;
	if(*timer0T)(*timer0T)--;
	inputPortTimer--;
	if (inputPortTimer == 0){
		inputPortTimer = 100;
		newInputValue = getInputValue();
		xorData = newInputValue ^ OldInputValue;
		inTemp = newInputValue;
		if (xorData){
			for(i=0; i != 4; i++){			//4 - number input data pins
				if (xorData & 0x01){
					if (inTemp & 0x01){
						outFrameBuffer[outFrameBufferWrIndex] = moduleConfigRam.returnAlarmCode[i];
					}else{
						outFrameBuffer[outFrameBufferWrIndex] = moduleConfigRam.alarmCode[i];
					}
					outFrameBufferWrIndex++;
					if(outFrameBufferWrIndex==OUTFRAMERADIOBUFFERSIZE)outFrameBufferWrIndex=0;
				}
				xorData = xorData>>1;
				inTemp = inTemp>>1;
			}
			OldInputValue = newInputValue;
		}
		
	}
}
