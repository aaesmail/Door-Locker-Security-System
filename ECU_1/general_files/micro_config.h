/***************************************************************************************
 * Module: Microcontroller Configurations
 *
 * File Name: micro_config.h
 *
 * Description: File to include Microcontroller libraries and specific configurations
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
***************************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

/* Select Microcontroller Clock Frequency - Set to 1 MHZ */
#define F_CPU 8000000UL

/***************************************************************************
 *						Including AVR Library Files						   *
 **************************************************************************/

/* Library for I/O Pins */
#include <avr/io.h>

/* Library for Interrupts */
#include <avr/interrupt.h>

/* Library for Busy Delay Functions */
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
