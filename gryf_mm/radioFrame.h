/**
 * \file radioframe.h
 *
 *  @date Created on: 3 kwi 2014
 *   @Author: krzysztof
 */

#ifndef RADIOFRAME_H_
#define RADIOFRAME_H_

#include <avr/io.h>

#define OUTFRAMERADIOBUFFERSIZE 64

extern volatile uint8_t outFrameBufferWrIndex;
extern volatile uint8_t outFrameBufferRdIndex;
extern uint8_t outFrameBuffer[OUTFRAMERADIOBUFFERSIZE];

/*! fn void sendAlarmFrameRadio()
\brief wysy³a ramkê z zdarzeniami które zbierane s¹ w outFrameBuffer

*/
void sendAlarmFrameRadio();


void indexIncrement(volatile uint8_t* index, uint8_t len);
	
	

/*! fn uint8_t getFrameRadio()
* \brief odbiera ramkê radiow¹

Jeœli nie ma ramki niezw³ocznie zwracana jest wartoœæ 1 (Nie czeka)

* \return uint8_t error code.

 0 - OK.
 1 - no frame in buffer.
 2 - all OK but uncnow command.
 3 - already no implement.
 4 - frame OK but not my address.
 5 - CRC16 error.
*/
uint8_t getFrameRadio();
void alarmSimulate(void);

#endif /* RADIOFRAME_H_ */
