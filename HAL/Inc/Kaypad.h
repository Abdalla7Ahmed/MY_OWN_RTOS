/*
 * Kaypad.h
 *
 * Created: 14/09/2022 07:35:53 ص
 *  Author: Abotaleb
 */ 


#ifndef KAYPAD_H_
#define KAYPAD_H_

#include "STM32F103C6.h"
#include <STM32F103C6_GPIO_Driver.h>


/*=========================== User Layer ===================================*/
#define KAYPAD_PORT      	GPIOB

//===========  Row =========
#define R0 					GPIO_PIN_0
#define R1 					GPIO_PIN_1
#define R2 					GPIO_PIN_3
#define R3 					GPIO_PIN_4
// ========= Columns ==========
#define C0				    GPIO_PIN_5
#define C1 					GPIO_PIN_6
#define C2 					GPIO_PIN_7
#define C3				    GPIO_PIN_8





/*=================================================================*/


/*===================Functions declaration======================*/
void KAYPAD_INIT();
char GET_CHARACTER();
/*=================================================================*/

#endif /* KAYPAD_H_ */
