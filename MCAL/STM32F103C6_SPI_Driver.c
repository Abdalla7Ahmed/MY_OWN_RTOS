/*
 * STM32F103C6_SPI_Driver.c
 *
 *  Created on: ٠٣‏/٠٢‏/٢٠٢٣
 *      Author: Abotaleb
 */




// =======================================
// Includes
#include "STM32F103C6.h"
#include "STM32F103C6_SPI_Driver.h"
#include "STM32F103C6_GPIO_Driver.h"
//========================================

// ===================================Generic Variables =========================
SPI_Config Global_SPI_Config[2]  = {0};


// ===========================================================================

// ===================================Generic Macros =========================
#define SPI1_index                           0
#define SPI2_index                           1

// ===========================================================================




// ===================================Generic functions =========================
void MCAL_SPI_GPIO_set_pins(SPI_TypeDef *SPIx)
{
	/*
	 SPI pinout  			Configuration 												GPIO configuration

	 SPIx_SCK			    Master 														Alternate function push-pull
	 SPIx_SCK			    Slave 														Input floating

	 SPIx_MOSI 				Full duplex / master 										Alternate function push-pull
	 SPIx_MOSI				Full duplex / 												slave Input floating /Input pull-up
	 SPIx_MOSI				Simplex bidirectional data wire / master 					Alternate function push-pull
	 SPIx_MOSI			    Simplex bidirectional data wire/ slave 						Not used. Can be used as a GPIO

	SPIx_MISO 				Full duplex / master 										Input floating /Input pull-up
	SPIx_MISO				Full duplex / slave (point to point) 						Alternate function push-pull
	SPIx_MISO				Full duplex / slave (multi-slave) 							Alternate function open drain
	SPIx_MISO				Simplex bidirectional data wire / master 					Not used. Can be used as a GPIO
	SPIx_MISO				Simplex bidirectional data wire/ slave(point to point) 		Alternate function push-pull
	SPIx_MISO				Simplex bidirectional data wire/ slave
	SPIx_MISO				(multi-slave) Alternate function open drain


	SPIx_NSS				Hardware master /slave 										Input floating/Input pull-up / Input pull-down
	SPIx_NSS				Hardware master/ NSS output enabled 						Alternate function push-pull
	SPIx_NSS				Software Not used.											Can be used as a GPIO

	 */

	GPIO_PinConfig_t GPIO_pin_config;


	// set GPIO pins for SPI1
	if(SPIx == SPI1)
	{
		// if SPI1 is Master
		if( Global_SPI_Config[SPI1_index].Device_mode == SPI_Device_Mode_Master)
		{
			// SPI1_SCK  : PA5     Alternate function push-pull
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);

			// SPI1_MOSI : PA7     Alternate function push-pull
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);


			// SPI1_MISO : PA6   Input floating
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);

			if( Global_SPI_Config[SPI1_index].NSS == SPI_NSS_HW_Master_Outout_enable)
			{
				//SPI1_NSS  : PA4     Alternate function push-pull
				GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
				GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
				GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);
			}
			else if( Global_SPI_Config[SPI1_index].NSS == SPI_NSS_HW_Master_Outout_Disable)
			{
				//SPI1_NSS  : PA4 Input floating
				GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
				GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);
			}
		}
		// if SPI1 is Slave
		else if ( Global_SPI_Config[SPI1_index].Device_mode == SPI_Device_Mode_Slave)
		{

			// SPI1_SCK  : PA5   Input floating
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);


			// SPI1_MOSI : PA7   Input floating
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);


			// SPI1_MISO : PA6    Alternate function push-pull
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);



			if( Global_SPI_Config[SPI1_index].NSS == SPI_NSS_HW_Master_Outout_Disable)
			{
				//SPI1_NSS  : PA4 Input floating
				GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
				GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_INIT(GPIOA, &GPIO_pin_config);
			}
		}

	}



	// set GPIO pins for SPI2
	else if(SPIx == SPI2)
	{
		// if SPI2 is Master
		if( Global_SPI_Config[SPI2_index].Device_mode == SPI_Device_Mode_Master)
		{
			// SPI2_SCK  : PB13     Alternate function push-pull
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);

			// SPI2_MOSI : PB15     Alternate function push-pull
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);


			// SPI2_MISO : PB14   Input floating
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);

			if( Global_SPI_Config[SPI2_index].NSS == SPI_NSS_HW_Master_Outout_enable)
			{
				//SPI2_NSS  : PB12     Alternate function push-pull
				GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
				GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
				GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);
			}
			else if( Global_SPI_Config[SPI2_index].NSS == SPI_NSS_HW_Master_Outout_Disable)
			{
				//SPI2_NSS  : PB12 Input floating
				GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
				GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);
			}


		}
		// if SPI2 is Slave
		else if ( Global_SPI_Config[SPI2_index].Device_mode == SPI_Device_Mode_Slave)
		{

			// SPI2_SCK  : PB13   Input floating
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);


			// SPI2_MOSI : PB15   Input floating
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);


			// SPI2_MISO : PB14    Alternate function push-pull
			GPIO_pin_config.GPIO_MODE = GPIO_MODE_ALTERNATIVE_OUTPUT_PP;
			GPIO_pin_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10M;
			GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);

			if( Global_SPI_Config[SPI2_index].NSS == SPI_NSS_HW_Master_Outout_Disable)
			{
				//SPI1_NSS  : PA4 Input floating
				GPIO_pin_config.GPIO_MODE = GPIO_MODE_FLOATINg_INPUT;
				GPIO_pin_config.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_INIT(GPIOB, &GPIO_pin_config);
			}

		}


	}
}

/**===================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief 			- Initializes SPI
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @param [in] 		- SPI_Config : All SPI Configuration
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config *SPI_Config)
{

	if     (SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_index] = *SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_index] = *SPI_Config;
		RCC_SPI1_CLK_EN();
	}

	uint16_t TMP_SPI_CR1 =0;
	uint16_t TMP_SPI_CR2 =0;

	// enable SPI
	TMP_SPI_CR1 |=(1<<6);

	// select the mode of the SPI (Master or slave)
	TMP_SPI_CR1 |=SPI_Config->Device_mode;

	// the mode communication
	TMP_SPI_CR1 |= SPI_Config->Communication_mode;

	// the frame format
	TMP_SPI_CR1 |= SPI_Config->Frame_formate;

	// the size of data
	TMP_SPI_CR1 |= SPI_Config->Data_size;

	// the clock polarity
	TMP_SPI_CR1 |= SPI_Config->CLK_Polarity;

	// the clock Phase
	TMP_SPI_CR1 |= SPI_Config->CLK_Phase;


	// NSS
	if(SPI_Config->NSS == SPI_NSS_HW_Master_Outout_Disable)
		TMP_SPI_CR2 |=SPI_Config->NSS;
	else if (SPI_Config->NSS == SPI_NSS_HW_Master_Outout_enable)
		TMP_SPI_CR2 &=SPI_Config->NSS;
	else
		TMP_SPI_CR1 |= SPI_Config->NSS;


	// the prescailer baud rate
	TMP_SPI_CR1 |=SPI_Config->Baud_rate;


	// the stat ofinterrupt
	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		// enable the type of interrupt
		TMP_SPI_CR2 |=SPI_Config->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->CR1 = TMP_SPI_CR1;
	SPIx->CR2 = TMP_SPI_CR2;

	//  GPIO mapping
	MCAL_SPI_GPIO_set_pins(SPIx);


}

/**===================================================================
 * @Fn				- MCAL_SPI_DeInit
 * @brief 			- DEInitializes SPI
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @retval 			- none
 * Note				- none
======================================================================**/

void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}
	else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}
}
/**===================================================================
 * @Fn				- MCAL_SPI_SendData
 * @brief 			- send data to SPI
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @param [in] 		- pTxBuffer
 * @param [in]		- SPI_polling_mecism
 * @retval 			- none
 * Note				- none
======================================================================**/

void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer,enum SPI_polling_mecism polling_state)
{
	if(polling_state == SPI_polling_Enable)
		while(!( (SPIx->SR) & (1<<1)  )  );

	SPIx->DR =  *pTxBuffer;
}

/**===================================================================
 * @Fn				- MCAL_SPI_ReceiveData
 * @brief 			- receive data from SPI
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @param [in] 		- pTxBuffer
 * @param [in]		- SPI_polling_mecism
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16_t *pRxBuffer,enum SPI_polling_mecism polling_state)
{
	if(polling_state == SPI_polling_Enable)
		while(!( (SPIx->SR) & (1<<0)  )  );

	*pRxBuffer = (uint16_t)SPIx->DR;

}
/**===================================================================
 * @Fn				- MCAL_SPI_ReceiveANDTransmitData
 * @brief 			- receive and send data from and to SPI
 * @param [in] 		- SPIx: where x can be (1..2 depending on device used)
 * @param [in] 		- pTxBuffer
 * @param [in]		- SPI_polling_mecism
 * @retval 			- none
 * Note				- none
======================================================================**/
void MCAL_SPI_ReceiveANDTransmitData(SPI_TypeDef *SPIx,uint16_t *pBuffer,enum SPI_polling_mecism polling_state)
{

	// first transmit the buffer
	if(polling_state == SPI_polling_Enable)
		while(!( (SPIx->SR) & (1<<1)  )  );

	SPIx->DR =  *pBuffer;

	// and then receive the new buffer
 	if(polling_state == SPI_polling_Enable)
		while(!( (SPIx->SR) & (1<<0)  )  );

	*pBuffer = (uint16_t)SPIx->DR;
}

// ===================================ISR =========================
void SPI1_IRQHandler(void)
{
	IRQ_source IRQ_src;
	IRQ_src.TXEI  = (SPI1->SR &(1<<1) >>1);
	IRQ_src.RXNEI = (SPI1->SR &(1<<0) >>0);
	IRQ_src.ERRI  = (SPI1->SR &(1<<4) >>4);

	Global_SPI_Config[SPI1_index].P_IRQ_CallBack(IRQ_src);
}


void SPI2_IRQHandler(void)
{
	IRQ_source IRQ_src;
	IRQ_src.TXEI  = (SPI2->SR &(1<<1) >>1);
	IRQ_src.RXNEI = (SPI2->SR &(1<<0) >>0);
	IRQ_src.ERRI  = (SPI2->SR &(1<<4) >>4);

	Global_SPI_Config[SPI2_index].P_IRQ_CallBack(IRQ_src);
}
