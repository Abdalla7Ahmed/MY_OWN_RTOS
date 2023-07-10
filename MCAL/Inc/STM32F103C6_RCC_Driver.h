/*
 * EXTRI_Driver.h
 *
 *  Created on: ١٩‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC__STM32F103C6_RCC_DRIVER_H_

// Includes
#include "../../MCAL/Inc/STM32F103C6.h"
#include "../../MCAL/Inc/STM32F103C6_GPIO_Driver.h"


#define HSI_RCC_Clock                 (uint32_t)8000000
#define HSE_RCC_Clock                 (uint32_t)16000000

// APIS
uint32_t MCAL_RCC_GET_SysClockFreq(void);
uint32_t MCAL_RCC_GET_HCLKFreq(void);
uint32_t MCAL_RCC_GET_PCLK1Freq(void);
uint32_t MCAL_RCC_GET_PCLK2Freq(void);



#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
