/*****************************************************************************
 * Module: Prototypes
 *
 * File Name: definitions.h
 *
 * Description: Header file to write Project definitions
 *
 * Created on: Oct 3, 2019
 *
 * Author: Ali Adel
*****************************************************************************/

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/*						Static Configurations 								*/
#define PASSWORD_SIZE			5				/* Size of password */
#define BUZZER_PERIOD			4				/* Buzzer period */
#define MAX_PASSWORD_CHECKS 	3				/* Number of times to check on password before locking */
#define LOCK_DOWN_PERIOD		60				/* Time for lock down */
#define DOOR_OPEN_TIME			1				/* Time takes motor to open and close door */

/* 						Communication Checks								*/
#define DISPLAY_DELAY 			500				/* Delay between each LCD screen in MS */
#define DISPLAY_DELAY_LONG 		1500			/* Long Delay between each LCD screen in MS */
#define ENTER 					13				/* ASCII Code of enter */
#define ERROR 					0xFF			/* Define this as error */
#define FIRST_PART_OVER 		0xFF			/* define for communication */
#define SECOND_PART_OVER 		0xFE			/* define for communication */
#define MATCHED					0xFD			/* define for communication */
#define NOT_MATCHED				0xFC			/* define for communication */
#define OPEN_DOOR				0xFB			/* define for communication */
#define CHANGE_PASSWORD			0xFA			/* define for communication */
#define PASSWORD_AGAIN 			0xF9			/* Ask for password again */
#define PASSWORD_CORRECT		0xF8			/* Password was correct */
#define INITIATE_LOCKDOWN		0xF7			/* Lock down system */
#define PASSWORD_LOCATION		0x0311			/* Location to store password */

#endif /* DEFINITIONS_H_ */
