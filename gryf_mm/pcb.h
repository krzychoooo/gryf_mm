/*! \file pcb.h
 *
 *  Created on: 21 gru 2013
 *      Author: krzysztof
 */

#include <avr/io.h>

#ifndef PCB_H_
#define PCB_H_

/*!
\def PCB_RS485_RC11XX_2
|PROCESOR PIN| PORT| FUNCTION |
|--------------------|----------|------------:|
|         1          |   PA5   |    LED   |
|        7          |   PB3	|		CTS USB |
*/
#define		PCB_RS485_RC11XX_2

#define	USARTE0_DE_PORT PORTD
#define	USARTE0_DE_PIN 4
#define USARTE0_DE_DIR USARTE0_DE_PORT.DIR
#define USARTE0_DE_ODBIERANIE (USARTE0_DE_PORT.OUTCLR = 1<<USARTE0_DE_PIN)
#define USARTE0_DE_NADAWANIE (USARTE0_DE_PORT.OUTSET = 1<<USARTE0_DE_PIN)

#define	USARTE0_RE_PORT PORTD
#define	USARTE0_RE_PIN 5
#define USARTE0_RE_DIR USARTE0_RE_PORT.DIR
#define USARTE0_RE_ODBIERANIE (USARTE0_RE_PORT.OUTCLR = 1<<USARTE0_RE_PIN)
#define USARTE0_RE_NADAWANIE (USARTE0_RE_PORT.OUTSET = 1<<USARTE0_RE_PIN)

#define LED1_PORT	PORTA
#define LED1_PIN	5
#define LED1_ON		LED1_PORT.OUTSET = 1<<LED1_PIN
#define LED1_OFF	LED1_PORT.OUTCLR = 1<<LED1_PIN
#define LED1_TOGLE  LED1_PORT.OUTTGL = 1<<LED1_PIN

#define OUT1_PORT	PORTC
#define OUT1_PIN	4
#define OUT1_ON		OUT1_PORT.OUTSET = 1<< OUT1_PIN
#define OUT1_OFF	OUT1_PORT.OUTCLR = 1<< OUT1_PIN

#define OUT2_PORT	PORTC
#define OUT2_PIN	5
#define OUT2_ON		OUT2_PORT.OUTSET = 1<< OUT2_PIN
#define OUT2_OFF	OUT2_PORT.OUTCLR = 1<< OUT2_PIN

#define RESET_RADIO_PORT	PORTC
#define RESET_RADIO_PIN		0
#define RESET_RADIO_ON		RESET_RADIO_PORT.OUTSET = 1<< RESET_RADIO_PIN
#define RESET_RADIO_OFF		RESET_RADIO_PORT.OUTCLR = 1<< RESET_RADIO_PIN
#define RESET_RADIO_TOGLE	RESET_RADIO_PORT.TOGLE = 1<< RESET_RADIO_PIN

#define CONFIG_RADIO_PORT		PORTC
#define CONFIG_RADIO_PIN		1
#define CONFIG_RADIO_DIR		CONFIG_RADIO_PORT.DIR
#define CONFIG_RADIO_DIR_OUT	CONFIG_RADIO_DIR  = 1<< CONFIG_RADIO_PIN
#define CONFIG_RADIO_OFF		CONFIG_RADIO_PORT.OUTSET = 1<< CONFIG_RADIO_PIN
#define CONFIG_RADIO_ON			CONFIG_RADIO_PORT.OUTCLR = 1<< CONFIG_RADIO_PIN

#endif /* PCB_H_ */