/*
 * Seven_Segment.h
 *
 *  Created on: ١٨‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */

#ifndef SEVEN_SEGMENT_SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_SEVEN_SEGMENT_H_
#include <STM32F103C6_GPIO_Driver.h>
#include "STM32F103C6.h"


/*=========================== User Layer ======================*/

#define Seven_segment_Port 	 GPIOB
#define S0					 GPIO_PIN_9
#define S1 					 GPIO_PIN_10
#define S2 					 GPIO_PIN_11
#define S3 					 GPIO_PIN_12
#define S4 					 GPIO_PIN_13
#define S5					 GPIO_PIN_14
#define S6					 GPIO_PIN_15


/*==============================================================*/


// ======= Numbers in hexa =========
#define ZERO	 0x01
#define ONE 	 0x79
#define TWO 	 0x24
#define THREE 	 0x30
#define FOUR 	 0x4C
#define FIVE 	 0x12
#define SIX 	 0x02
#define SEVEN 	 0x19
#define EIGHT 	 0x00
#define NINE 	 0x10
// ========= Functions Prototype ==========

void Seven_Segment_Init();

#endif /* SEVEN_SEGMENT_SEVEN_SEGMENT_H_ */
