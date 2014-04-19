/**
 * \file radioframe.h
 *
 *  @date Created on: 3 kwi 2014
 *   @Author: krzysztof
 */

#ifndef RADIOFRAME_H_
#define RADIOFRAME_H_

#include <avr/io.h>

#define INFRAMERADIOBUFFERSIZE 64

extern volatile uint8_t inFrameBufferWrIndex;
extern volatile uint8_t inFrameBufferRdIndex;
extern uint8_t inFrameBuffer[INFRAMERADIOBUFFERSIZE];

/*! fn void sendAlarmFrameRadio()
\brief wysy�a ramk� z zdarzeniami

*/
void sendAlarmFrameRadio();


/*! fn uint8_t getFrameRadio()
* \brief odbiera ramk� radiow�

Je�li nie ma ramki niezw�ocznie zwracana jest warto�� 1 (Nie czeka)

* \return uint8_t error code.

 0 - OK.
 1 - no frame in buffer.
 2 - already no implement.
 3 - already no implement.
 4 - frame OK but not my address.
 5 - CRC16 error.
*/
uint8_t getFrameRadio();
void alarmSimulate(void);

#endif /* RADIOFRAME_H_ */
