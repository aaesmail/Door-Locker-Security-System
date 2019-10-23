/***********************************************************************************
 * Module: DC Motor
 *
 * File Name: dcmotor.h
 *
 * Description: Header File for DC Motor Driver
 *
 * Created on: Oct 3, 2019
 *
 * Author: Ali Adel
***********************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

/**************************************************************************
 * 								Including Files							  *
**************************************************************************/
/* File for Standard Types */
#include "../general_files/std_types.h"

/* File for Most used Macros */
#include "../general_files/common_macros.h"

/* File for MCU specific configurations */
#include "../general_files/micro_config.h"

/**************************************************************************
 * 								Static Configurations					  *
**************************************************************************/
/* Port Direction connected IN1, IN2 */
#define OUTPORT_DIR DDRB

/* Port output connected IN1, IN2 */
#define OUTPORT PORTB

/* Pin of IN1 */
#define IN1 PB7

/* Pin of IN2 */
#define IN2 PB6

/**************************************************************************
 * 								Functions Prototypes					  *
**************************************************************************/
/***********************************************************************
 * Function Name: DCMOTOR_init
 *
 * Description: Sets DC Motor for Rotations
 *
 * Args:
 * 		[void]: Doesn't take any arguments
 *
 * Return Type: [void] Doesn't return anything
***********************************************************************/
void DCMOTOR_init(void);

/***********************************************************************
 * Function Name: DCMOTOR_rotateCW
 *
 * Description: Rotates DC Motor in Clock-Wise Direction
 *
 * Args:
 * 		[void]: Doesn't take any arguments
 *
 * Return Type: [void] Doesn't return anything
***********************************************************************/
void DCMOTOR_rotateCW(void);

/***********************************************************************
 * Function Name: DCMOTOR_rotateCCW
 *
 * Description: Rotates DC Motor in Counter-Clock-Wise Direction
 *
 * Args:
 * 		[void]: Doesn't take any arguments
 *
 * Return Type: [void] Doesn't return anything
***********************************************************************/
void DCMOTOR_rotateCCW(void);

/***********************************************************************
 * Function Name: DCMOTOR_changeDirection
 *
 * Description: Makes DC motor change its current direction
 *
 * Args:
 * 		[void]: Doesn't take any arguments
 *
 * Return Type: [void] Doesn't return anything
***********************************************************************/
void DCMOTOR_changeDirection(void);

/***********************************************************************
 * Function Name: DCMOTOR_stop
 *
 * Description: Stops DC Motor from rotations
 *
 * Args:
 * 		[void]: Doesn't take any arguments
 *
 * Return Type: [void] Doesn't return anything
***********************************************************************/
void DCMOTOR_stop(void);

#endif /* DCMOTOR_H_ */
