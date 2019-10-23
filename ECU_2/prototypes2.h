/*****************************************************************************
 * Module: Prototypes
 *
 * File Name: prototypes.h
 *
 * Description: Header file to write functions prototypes of Main
 *
 * Created on: Oct 3, 2019
 *
 * Author: Ali Adel
*****************************************************************************/

#ifndef PROTOTYPES2_H_
#define PROTOTYPES2_H_

/* Function to Initialize All Drivers */
void Drivers_Init(void);

/* Function to Receive new Password */
void Receive_New_Password(void);

/* Function to Make buzzer Sound */
void Activate_Buzzer(void);

/* Function to Stop Buzzer */
void Stop_Buzzer(void);

/* Switch Buzzer Operation */
void Switch_Buzzer(void);

/* Function to check on entry password */
bool Check_Password(void);

/* Function for open door operation */
void Open_Door(void);

/* Interrupt Function for open door */
void Open_Door_Interrupt(void);

/* To lock down system for 1 minute if wrong password */
void Lock_Down(void);

/* For periodic Lock down action */
void Lock_Down_Interrupt(void);

#endif /* PROTOTYPES2_H_ */
