/***********************************************************************************
 * Module: DC Motor
 *
 * File Name: dcmotor.c
 *
 * Description: Source File for DC Motor Driver
 *
 * Created on: Oct 3, 2019
 *
 * Author: Ali Adel
***********************************************************************************/

/* Including its header file */
#include "dcmotor.h"

void DCMOTOR_init(void)
{
	/* Just make pins as output pins */
	SET_BIT(OUTPORT_DIR, IN1);
	SET_BIT(OUTPORT_DIR, IN2);
	/* Make sure it's Stopped first */
	CLEAR_BIT(OUTPORT, IN1);
	CLEAR_BIT(OUTPORT, IN2);
}

void DCMOTOR_rotateCW(void)
{
	/* for clock-wise IN1 = 0, IN2 = 1 */
	CLEAR_BIT(OUTPORT, IN1);
	SET_BIT(OUTPORT, IN2);
}

void DCMOTOR_rotateCCW(void)
{
	/* for counter-clock-wise IN1 = 1, IN2 = 0 */
	SET_BIT(OUTPORT, IN1);
	CLEAR_BIT(OUTPORT, IN2);
}

void DCMOTOR_changeDirection(void)
{
	/* Change output of both pins */
	TOGGLE_BIT(OUTPORT, IN1);
	TOGGLE_BIT(OUTPORT, IN2);
}

void DCMOTOR_stop(void)
{
	/* Clear both bits for stop */
	CLEAR_BIT(OUTPORT, IN1);
	CLEAR_BIT(OUTPORT, IN2);
}
