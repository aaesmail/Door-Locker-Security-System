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

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

/* Function to Initialize All Drivers */
void Drivers_Init(void);

/* Function to type new Password */
void Receive_New_Password(void);

/* Display Main Screen */
void Display_Main_Screen(void);

/* Open Door Function */
void Open_Door(void);

/* Change Password Function */
void Change_Password(void);

/* To Take password and check if it matches */
bool Check_Password(void);

/* To lock down system for 1 minute if wrong password */
void Lock_Down(void);

#endif /* PROTOTYPES_H_ */
