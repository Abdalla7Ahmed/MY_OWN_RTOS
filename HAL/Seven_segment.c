/*
 * Seven_segment.c
 *
 *  Created on: ١٨‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */
#include "Seven_Segment.h"

GPIO_PinConfig_t PinConfigSevenSegment;
void Seven_Segment_Init()
{
	PinConfigSevenSegment.GPIO_PinNumber =S0;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);

	PinConfigSevenSegment.GPIO_PinNumber =S1;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);

	PinConfigSevenSegment.GPIO_PinNumber =S2;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);

	PinConfigSevenSegment.GPIO_PinNumber =S3;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);

	PinConfigSevenSegment.GPIO_PinNumber =S4;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);

	PinConfigSevenSegment.GPIO_PinNumber =S5;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);

	PinConfigSevenSegment.GPIO_PinNumber =S6;
	PinConfigSevenSegment.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigSevenSegment.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(Seven_segment_Port, &PinConfigSevenSegment);
}
