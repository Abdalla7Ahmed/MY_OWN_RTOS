/*
 * STM32F103C6_GPIO_Drivers.c
 *
 *  Created on: Sep 15, 2022
 *      Author: Abotaleb
 */

#include "../MCAL/Inc/STM32F103C6_GPIO_Driver.h"
uint8_t Get_CRLH_position (uint16_t pinNumber)
{
	switch(pinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIOx_INIT
 * @brief 	  - initialization GPIOx piny according to the specified parameters in pin configuration
 * @param[in] - base address of GPIOx : can be (A ..... E depending on device used)
 * @param[in] - PinConfig pointer to GPIO_PinConfig_t structure that contains
 * 			   the configuration information for specified GPIO pin
 * @retval	  - none
 * Note		  - stm32f103c6 MCU has GPIOz [z one of A ,B , C ,D ,E]
 * 			   but LQFP48 Package has only GPIOA , GPIOB and Partial of GPIOC , GPIOD
================================================================**/
void MCAL_GPIO_INIT(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL) (x=A..G) pin 0 to 7
	//Port configuration register High (GPIOx_CRL) (x=A..G) pin 8 to 15
	volatile uint32_t *ConfigRegister = NULL;
	uint8_t Pin_Config=0;
	// check for set the pointer to CRL or CRH
	ConfigRegister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8 ) ? &GPIOx->CRL : &GPIOx->CRH;
	// clear CNF[1:0] MODE[1:0]
	(*ConfigRegister) &= ~(0xF<<Get_CRLH_position(PinConfig->GPIO_PinNumber));
	// if pin is output ?
	if ((PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)||(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD)
			||(PinConfig->GPIO_MODE == GPIO_MODE_ALTERNATIVE_OUTPUT_PP) ||(PinConfig->GPIO_MODE == GPIO_MODE_ALTERNATIVE_OUTPUT_OD))
	{
		// set CNFx[1:0] MODE[1:0]
		Pin_Config = ( (((PinConfig->GPIO_MODE -4 )<<2) | PinConfig->GPIO_OUTPUT_SPEED) & 0x0F);
	}
	else // if pin is input
	{
		if ((PinConfig->GPIO_MODE == GPIO_MODE_ANALOG ) ||(PinConfig->GPIO_MODE == GPIO_MODE_FLOATINg_INPUT))
		{
			Pin_Config = ( (((PinConfig->GPIO_MODE )<<2) | 0x0) & 0x0F);
		}
		else if	(PinConfig->GPIO_MODE == GPIO_MODE_ALTERNATIVE_INPUT ) // consider it as input floating
		{
			Pin_Config = ( (((GPIO_MODE_FLOATINg_INPUT)<<2) | 0x0) & 0x0F);

		}
		else // pull up / pull down input
		{
			Pin_Config = ( (((GPIO_MODE_INPUT_PU)<<2) | 0x0) & 0x0F);
			if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//	Table 20. Port bit configuration table Px ODR register = 1 --> pull up
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;

			}
			else // GPIO_MODE_INPUT_PD
			{
				//	Table 20. Port bit configuration table Px ODR register = 0 --> pull down
				GPIOx->ODR &=~(PinConfig->GPIO_PinNumber);

			}
		}
	}
	(*ConfigRegister) |= Pin_Config <<Get_CRLH_position(PinConfig->GPIO_PinNumber);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_DEINIT
 * @brief 	  - Reset all GPIOx pins
 * @param[in] - base address of GPIOx : can be (A ..... E depending on device used)
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_GPIO_DEINIT(GPIO_TypeDef *GPIOx)
{
	/* if the MCU havn't reset controller , enable this to reset it manually
	GPIOx->CRL  = 0x44444444;
	GPIOx->CRH  = 0x44444444;
	GPIOx->ODR  = 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->BRR  = 0x00000000;
	GPIOx->LCKR = 0x00000000;
	                         // note that ---> GPIOx->IDR is Read only
	@@@@@@@@@@@@@@@@@@@@@@@@@@
	 */
	// if you have a reset controller
	// use register APB2RSTR  to reset the GPIOx
	// Set and cleared by software
	if (GPIOx == GPIOA)
	{
		RCC_GPIOA_Reset();
		/*RCC->APB2RSTR |= 1<<2 ;
		RCC->APB2RSTR &= ~(1<<2);*/
	}
	else if (GPIOx == GPIOB)
	{
		RCC_GPIOB_Reset();
		/*RCC->APB2RSTR |= 1<<3;
		RCC->APB2RSTR &= ~(1<<3);*/
	}
	else if (GPIOx == GPIOC)
	{
		RCC_GPIOC_Reset();
		/*RCC->APB2RSTR |= 1<<4;
		RCC->APB2RSTR &= ~(1<<4);*/
	}
	else if (GPIOx == GPIOD)
	{
		 RCC_GPIOD_Reset();
		/*RCC->APB2RSTR |= 1<<5;
		RCC->APB2RSTR &= ~(1<<5);*/
	}
	else if (GPIOx == GPIOE)
	{
		RCC_GPIOE_Reset();
		/*RCC->APB2RSTR |= 1<<6;
		RCC->APB2RSTR &= ~(1<<6);*/
	}

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_READ_PIN
 * @brief 	  - Read specified pin
 * @param[in] - base address of GPIOx : can be (A ..... E depending on device used)
 * @param[in] - pin number set by @ref GPIO_PINS_define
 * @retval	  - the input pin value according to @ref GPIO_PIN_state
 * Note		  - none
================================================================**/
uint8_t MCAL_GPIO_READ_PIN(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	uint8_t bitstatus;
	if (((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_READ_PORT
 * @brief 	  - Read specified port
 * @param[in] - base address of GPIOx : can be (A ..... E depending on device used)
 * @retval	  - the input port value
 * Note		  - none
================================================================**/
uint16_t MCAL_GPIO_READ_PORT(GPIO_TypeDef *GPIOx)
{
	uint16_t port_value;
	port_value = (uint16_t)(GPIOx->IDR) ;
	return port_value;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_WRITE_PIN
 * @brief 	  - write specified pin on GPIOx :can be (A ..... E depending on device used)
 * @param[in] - base address of GPIOx :can be (A ..... E depending on device used)
 * @param[in] - pin number set by @ref GPIO_PINS_define
 * @param[in] - pin value
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_GPIO_WRITE_PIN(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t PinValue)
{
	if (PinValue != (uint8_t)GPIO_PIN_RESET)
	{
		// GPIOx->ODR |= PinNumber;
		//      or
		//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Set the corresponding ODRx bit
		GPIOx->BSRR =(uint32_t)PinNumber;
	}
	else
	{
		// GPIOx->ODR &= ~(PinNumber);
		//      or
		//		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Reset the corresponding ODRx bit
		GPIOx->BRR =(uint32_t)PinNumber;
	}

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_WRITE_PORT
 * @brief 	  - write specified GPIOx :can be (A ..... E depending on device used)
 * @param[in] - base address of GPIOx :can be (A ..... E depending on device used)
 * @param[in] - port value
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_GPIO_WRITE_PORT(GPIO_TypeDef *GPIOx ,uint16_t PortValue)
{
	GPIOx->ODR = (uint32_t)PortValue;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_TOGGLE_PIN
 * @brief 	  - toggle specified GPIOx piny
 * @param[in] - base address of GPIOx :can be (A ..... E depending on device used)
 * @param[in] - pin number set by @ref GPIO_PINS_define
 * @retval	  - none
 * Note		  - none
================================================================**/
void MCAL_GPIO_TOGGLE_PIN(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**================================================================
 * @Fn		  - MCAL_GPIO_LOCK
 * @brief 	  - the locking mechanism allows the IO configuration to be frozen
 * @param[in] - base address of GPIOx :can be (A ..... E depending on device used)
 * @param[in] - pin number set by @ref GPIO_PINS_define
 * @retval	  - ok if pin confige is locked and error if pin not locked according to @ref GPIO_RETURNE_LOCK_State
 * Note		  - none
================================================================**/
uint8_t MCAL_GPIO_LOCK(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked
	volatile uint32_t tmp=1<<16;
	tmp |=PinNumber;
	//	Write 1
	GPIOx->LCKR = tmp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = tmp;
	//	Read 0
	tmp = GPIOx->LCKR;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if ((uint32_t)GPIOx->LCKR & 1<<16)
	{
		return GPIO_RETURNE_LOCK_DONE;
	}
	else
	{
		return GPIO_RETURNE_LOCK_ERROR;
	}
}



