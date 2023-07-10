/*
 * EXTRI_Driver.c
 *
 *  Created on: ١٩‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */
// =======================================
// Includes
#include "../MCAL/Inc/STM32F103C6_EXTRI_Driver.h"

#include "../MCAL/Inc/STM32F103C6_GPIO_Driver.h"
//========================================

// ===================================Generic Variables =========================
void(* GP_IRQ_CallBack[15])(void);


// ===========================================================================

// ===================================Generic Macros =========================

#define AFIO_GPIO_GPIO_Mapping(x)      (   (x==GPIOA)?0:\
										   (x==GPIOB)?1:\
										   (x==GPIOC)?2:\
										   (x==GPIOD)?3:0)

// ===========================================================================




// ===================================Generic functions =========================
void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTRI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTRI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTRI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTRI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTRI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTRI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTRI10_15_Enable;
		 break;
	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTRI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTRI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTRI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTRI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTRI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTRI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTRI10_15_Disable;
		 break;
	}
}
void Update_EXTRI(EXTRI_PinConfig_t *EXTRI_Config)
{
	// 1- Configure GPIO as an alternative input --> floating input
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_PinNumber=EXTRI_Config->PIN_INPUT.GPIO_PinNumber;
	PinConfig.GPIO_MODE=GPIO_MODE_FLOATINg_INPUT;
	MCAL_GPIO_INIT(EXTRI_Config->PIN_INPUT.GPIO_PORT, &PinConfig);

	// 2- Update AFIO to rout between EXTRI line and  port
	// Index of EXTRI
	uint8_t AFIO_EXTICR_Index = (EXTRI_Config->PIN_INPUT.EXTRI_InputLine)/4;
	// Position of the pins in EXTRICR register
	uint8_t AFIO_EXTRICR_Posision = ( (EXTRI_Config->PIN_INPUT.EXTRI_InputLine)%4)*4;
	// Clear the register (four bit)
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF<<AFIO_EXTRICR_Posision);
	AFIO->EXTICR[AFIO_EXTICR_Index] |=( (AFIO_GPIO_GPIO_Mapping(EXTRI_Config->PIN_INPUT.GPIO_PORT) &0xF) << AFIO_EXTRICR_Posision);
	// 3- Update rising and failing Edge
	EXTRI->RTSR &=~(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
	EXTRI->FTSR &=~(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);

	if (EXTRI_Config->EXTRI_Trigger_Case == EXTRI_Trigger_Rising)
	{
		EXTRI->RTSR |=(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
	}
	else if (EXTRI_Config->EXTRI_Trigger_Case == EXTRI_Trigger_Failing)
	{
		EXTRI->FTSR |=(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
	}
	else if (EXTRI_Config->EXTRI_Trigger_Case == EXTRI_Trigger_RisingANDFailing)
	{
		EXTRI->RTSR |=(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
		EXTRI->FTSR |=(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
	}
	// 4- Update IRQ handing callback
	GP_IRQ_CallBack[EXTRI_Config->PIN_INPUT.EXTRI_InputLine]=EXTRI_Config->P_IRQ_CallBack;

	// 5- Enable / Disable IRQ and NVIC
	if(EXTRI_Config->IRQ_ENABLE==EXTRI_IRQ_Enable)
	{
		EXTRI->IMR |= (1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
		Enable_NVIC(EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
	}
	else if(EXTRI_Config->IRQ_ENABLE==EXTRI_IRQ_Disable)
	{
		EXTRI->IMR &= ~(1<<EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
		Disable_NVIC(EXTRI_Config->PIN_INPUT.EXTRI_InputLine);
	}
}
// ================================================================================

/**================================================================
 * @Fn		  - MCAL_EXTRI_GPIO_DEINIT
 * @brief 	  - Reset the EXTRI registers and NVIC corresponding IRQ mask
 * @param[in] - none
 * @retval	  - none
 * Note		  - stm32f103c6 MCU has GPIOz [z one of A ,B , C ,D ,E]
 * 			   but LQFP48 Package has only GPIOA , GPIOB and Partial of GPIOC , GPIOD
================================================================**/
void MCAL_EXTRI_GPIO_DEINIT(void)
{
	// Reset External interrupt registers
	EXTRI->IMR  =0x00000000;
	EXTRI->EMR  =0x00000000;
	EXTRI->RTSR =0x00000000;
	EXTRI->FTSR =0x00000000;
	EXTRI->SWIER=0x00000000;
//	0: No trigger request occurred
//	1: selected trigger request occurred
//	This bit is set when the selected edge event arrives on the external interrupt line. This bit is
//	cleared by writing a ‘1’ into the bit.
	EXTRI->PR  =0xFFFFFFFF;
	// Disable the EXTRI from NVIC
	NVIC_IRQ6_EXTRI0_Disable;
	NVIC_IRQ7_EXTRI1_Disable;
	NVIC_IRQ8_EXTRI2_Disable;
	NVIC_IRQ9_EXTRI3_Disable;
	NVIC_IRQ10_EXTRI4_Disable;
	NVIC_IRQ23_EXTRI5_9_Disable;
	NVIC_IRQ40_EXTRI10_15_Disable;
}
/**================================================================
 * @Fn		  - MCAL_EXTRI_GPIO_INIT
 * @brief 	  - initialize the EXTRI from specific GPIO PIN
 * @param[in] - EXTRI_Config Set by @ref EXTRI_define , EXTRI_Trigger_define and EXTRI_IRQ_define
 * @retval	  - none
 * Note		  - stm32f103c6 MCU has GPIOz [z one of A ,B , C ,D ,E]
 * 			   but LQFP48 Package has only GPIOA , GPIOB and Partial of GPIOC , GPIOD
================================================================**/
void MCAL_EXTRI_GPIO_INIT(EXTRI_PinConfig_t *EXTRI_Config)
{
	Update_EXTRI(EXTRI_Config);

}
/**================================================================
 * @Fn		  - MCAL_EXTRI_GPIO_Update
 * @brief 	  - Update the EXTRI from specific GPIO PIN
 * @param[in] - EXTRI_Config Set by @ref EXTRI_define , EXTRI_Trigger_define and EXTRI_IRQ_define
 * @retval	  - none
 * Note		  - stm32f103c6 MCU has GPIOz [z one of A ,B , C ,D ,E]
 * 			    but LQFP48 Package has only GPIOA , GPIOB and Partial of GPIOC , GPIOD
================================================================**/
void MCAL_EXTRI_GPIO_Update(EXTRI_PinConfig_t *EXTRI_Config)
{
	Update_EXTRI(EXTRI_Config);
}




// ================================================================
// IRQ Functions
//=================================================================
void EXTI0_IRQHandler(void)
{
	//clear by writing 1 into the bit Pending register EXTRI_PR
	EXTRI->PR |= (1<<0);
	// call IRQ callBack
	GP_IRQ_CallBack[0]();
}
void EXTI1_IRQHandler(void)
{
	EXTRI->PR |= (1<<1);
	// call IRQ callBack
	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)
{
	EXTRI->PR |= (1<<2);
	// call IRQ callBack
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	//clear by writing 1 into the bit Pending register EXTRI_PR
	EXTRI->PR |= (1<<3);
	// call IRQ callBack
	GP_IRQ_CallBack[3]();

}void EXT4_IRQHandler(void)
{
	//clear by writing 1 into the bit Pending register EXTRI_PR
	EXTRI->PR |= (1<<4);
	// call IRQ callBack
	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void)
{
	// Check the EXTRI line number
	//clear by writing 1 into the bit Pending register EXTRI_PR
	// Call IRQ callBack
	if(EXTRI->PR & 1<<5) {EXTRI->PR |= (1<<5); 		GP_IRQ_CallBack[5]();}
	if(EXTRI->PR & 1<<6) {EXTRI->PR |= (1<<6); 		GP_IRQ_CallBack[6]();}
	if(EXTRI->PR & 1<<7) {EXTRI->PR |= (1<<7); 		GP_IRQ_CallBack[7]();}
	if(EXTRI->PR & 1<<8) {EXTRI->PR |= (1<<8); 		GP_IRQ_CallBack[8]();}
	if(EXTRI->PR & 1<<9) {EXTRI->PR |= (1<<9); 		GP_IRQ_CallBack[9]();}
}
void EXTI15_10_IRQHandler(void)
{
	// Check the EXTRI line number
	//clear by writing 1 into the bit Pending register EXTRI_PR
	// Call IRQ callBack
	if(EXTRI->PR & 1<<10) {EXTRI->PR |= (1<<10);    GP_IRQ_CallBack[10]();}
	if(EXTRI->PR & 1<<11) {EXTRI->PR |= (1<<11);    GP_IRQ_CallBack[11]();}
	if(EXTRI->PR & 1<<12) {EXTRI->PR |= (1<<12);    GP_IRQ_CallBack[12]();}
	if(EXTRI->PR & 1<<13) {EXTRI->PR |= (1<<13); 	GP_IRQ_CallBack[13]();}
	if(EXTRI->PR & 1<<14) {EXTRI->PR |= (1<<14); 	GP_IRQ_CallBack[14]();}
	if(EXTRI->PR & 1<<15) {EXTRI->PR |= (1<<15); 	GP_IRQ_CallBack[15]();}
}
