/*
 * EXTRI_Driver.c
 *
 *  Created on: ١٩‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */
// =======================================
// Includes
#include "STM32F103C6_USART_Driver.h"
//========================================

// ===================================Generic Variables =========================
UART_Config* Global_UART_Config[3]  = {NULL,NULL,NULL};
UART_Config Global_UART_Config1;
UART_Config Global_UART_Config2;
UART_Config Global_UART_Config3;
static uint8_t UART_number;
// ===========================================================================

// ===================================Generic Macros =========================


// ===========================================================================




// ===================================Generic functions =========================
void MCAL_UART_GPIO_set_pins(USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t PinCfg ;

	if ( USARTx == USART1 )
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_INPUT;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if (Global_UART_Config[UART_number]->HWFlowCtrl==USART_FlowCtrl_CTS_Enable  || Global_UART_Config[UART_number]->HWFlowCtrl ==USART_FlowCtrl_CTS_RTS_Enable  ){
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}


		if (Global_UART_Config[UART_number]->HWFlowCtrl  == USART_FlowCtrl_RTS_Enable|| Global_UART_Config[UART_number]->HWFlowCtrl ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);

		}
	}
	else if ( USARTx == USART2 )
	{
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS


		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_INPUT;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if (Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_CTS_Enable  || Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}

		if (Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_RTS_Enable || Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}
	}
	else if ( USARTx == USART3 )
	{
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_INPUT;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		if (Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_CTS_Enable  || Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable  )
		{
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
		if (Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_RTS_Enable || Global_UART_Config[UART_number]->HWFlowCtrl  ==USART_FlowCtrl_CTS_RTS_Enable )
		{
			//PA14 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
	}

}



/**===================================================================
 * @Fn				- MCAL_UART_Init
 * @brief 			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration
 * @retval 			- none
 * Note				- Support for Now Asynchronous mode & Clock 8 MHZ S
======================================================================**/
void MCAL_UART_Init(USART_TypeDef *USARTx,UART_Config *UART_Config)
{
	if(USARTx == USART1)
	{
	 	UART_number =0;
	 	RCC_USART1_CLK_EN();
	 	Global_UART_Config1 = *UART_Config;
	 	Global_UART_Config[0] = &Global_UART_Config1;
	}
	else if(USARTx == USART2)
	{
	 	UART_number =1;
	 	RCC_USART2_CLK_EN();
	 	Global_UART_Config2 = *UART_Config;
	 	Global_UART_Config[1] = &Global_UART_Config2;
	}
	else if(USARTx == USART3)
	{
	 	UART_number =2;
	 	RCC_USART3_CLK_EN();
	 	Global_UART_Config3 = *UART_Config;
	 	Global_UART_Config[2] = &Global_UART_Config3;
	}

	uint32_t pclk,BRR;
	// Enable the USART by writing the UE bit in USART_CR1 register to 1
	USARTx->CR1 |=1<<13;
	// select the mode
	USARTx->CR1 |=UART_Config->USART_Mode;
	// Program the M bit in USART_CR1 to define the word length.
	USARTx->CR1 |=UART_Config->PayLoad_Length;
	//Configuration of parity control bit fields
	// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->parity ;
	//Program the number of stop bits in USART_CR2.
	USARTx->CR2 |=UART_Config->stopBits;
	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->HWFlowCtrl ;
	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2, 3
	//PCLK2 for USART1
	if(USARTx==USART1)  	{pclk=MCAL_RCC_GET_PCLK2Freq();}
	else 				    {pclk=MCAL_RCC_GET_PCLK1Freq();}
	BRR = UART_BRR_Register(pclk, UART_Config->Baud_rate);
	USARTx->BRR = BRR ;

	if (UART_Config->IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |=UART_Config->IRQ_Enable;
		if		(USARTx==USART1)  		 {NVIC_IRQ37_USART1_Enable;}
		else if (USARTx==USART2)		 {NVIC_IRQ38_USART2_Enable;}
		else if (USARTx==USART3)		 {NVIC_IRQ39_USART3_Enable;}
	}

	// set pins of GPIO
	MCAL_UART_GPIO_set_pins(USARTx);
}
/**===================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_UART_DeInit(USART_TypeDef *USARTx)
{
	if		(USARTx==USART1)  		{RCC_USART1_Reset();	NVIC_IRQ37_USART1_Disable;}
	else if (USARTx==USART2)		{RCC_USART2_Reset();	NVIC_IRQ38_USART2_Disable;}
	else if (USARTx==USART3)		{RCC_USART3_Reset();	NVIC_IRQ39_USART3_Disable;}
}



/**===================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_UART_SendData(USART_TypeDef *USARTx,uint16_t *pTxBuffer,enum polling_mecism pollingEn)
{
	if (pollingEn==Enable) {while(!(USARTx->SR & 1<<7));}

	if(Global_UART_Config[UART_number]->PayLoad_Length == USART_Payload_Length_9B)
	{
		/*When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
		because it is replaced by the parity.
		When receiving with the parity enabled, the value read in the MSB bit is the received parity
		bit*/
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}
}
void MCAL_UART_WAIT_TC (USART_TypeDef *USARTx )
{
	// wait till TC flag is set in the SR
	while( ! (USARTx->SR & 1<<6 ));
}
/**===================================================================
 * @Fn				- MCAL_UART_ReceiveData
 * @brief 			- Receive the buffer
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- Global_UART_Config[UART_number]: All UART Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx,uint16_t *pRxBuffer,enum polling_mecism pollingEn)
{
	if (pollingEn==Enable) {while(!(USARTx->SR & 1<<5));}
	if(Global_UART_Config[UART_number]->PayLoad_Length == USART_Payload_Length_9B)
	{
		if(Global_UART_Config[UART_number]->parity == USART_Paratiy_NONE)
		{
			//no parity So all 9bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->DR ;
		}
		else
		{
			//Parity is used, so, 8bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
		}
	}
	else
	{
		if(Global_UART_Config[UART_number]->parity == USART_Paratiy_NONE)
		{
			//no parity So all 8bit are considered data
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
		}
		else
		{
			//Parity is used, so,7 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0x7F );
		}

	}
}


//ISR
void USART1_IRQHandler (void)
{
	Global_UART_Config[0]->P_IRQ_CallBack();
}

void USART2_IRQHandler (void)
{
	Global_UART_Config[1]->P_IRQ_CallBack();
}
void USART3_IRQHandler (void)
{
	Global_UART_Config[2]->P_IRQ_CallBack();
}

