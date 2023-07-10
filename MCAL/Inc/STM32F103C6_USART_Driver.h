/*
 * EXTRI_Driver.h
 *
 *  Created on: ١٩‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_
#include "STM32F103C6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_RCC_Driver.h"


typedef struct
{
	// Specify TX/RX Enable/Disable
	//this parameter must be set based on @ref USART_Mode_Define
	uint16_t USART_Mode;
	// configure the USART communication baud rate
	//this parameter must be set based on @ref USART_BaudRate_Define
	uint32_t Baud_rate;
	// Specify the number of transmitted bits
	//this parameter must be set based on @ref USART_Payload_Length_define
	uint16_t PayLoad_Length;
	// Specify the parity mode (none , even or odd)
	//this parameter must be set based on @ref USART_Paratiy_define
	uint16_t parity;
	// Specify the number of stop bits
	//this parameter must be set based on @ref USART_StopBits_define
	uint16_t stopBits;
	// Specifies whether the Hardware flow control mode is enable or disable
	//this parameter must be set based on @ref USART_FlowCtrl_define
	uint16_t HWFlowCtrl;
	// Enable or disable the interrupt
	//this parameter must be set based on @ref USART_IRQ_Enable_define
	uint16_t IRQ_Enable;
	// Set the c function which will be called once the IRQ happened.
	void(* P_IRQ_CallBack)(void);
}UART_Config;




//----------------------------------------------------------
// Macros configuration references
//----------------------------------------------------------

//@ref USART_Mode_Define
#define USART_Mode_TX 							   (uint16_t)(1<<3) // bit 3 enable the transmit
#define USART_Mode_RX							   (uint16_t)(1<<2) // bit 2 enable the receive
#define USART_Mode_TX_RX						   (uint16_t)(1<<3 | 1<<2) // enable both the transmit and  the receive

//@ref USART_BaudRate_Define
#define USART_BaudRate_2400                       2400
#define USART_BaudRate_9600                       9600
#define USART_BaudRate_19200                      19200
#define USART_BaudRate_57600                      57600
#define USART_BaudRate_115200                     115200
#define USART_BaudRate_230400                     230400
#define USART_BaudRate_460800                     460800
#define USART_BaudRate_921600                     921600
#define USART_BaudRate_2250000                    2250000
#define USART_BaudRate_4500000                    4500000

//@ref USART_Payload_Length_define
#define USART_Payload_Length_8B                   (uint16_t)(0)
#define USART_Payload_Length_9B					  (uint16_t)(1<<12)
// @ref USART_Paratiy_define
#define USART_Paratiy_NONE 						  (uint16_t)(0)
#define USART_Paratiy_EVEN					      (uint16_t)(1<<10 )
#define USART_Paratiy_ODD						  (uint16_t)(1<<10 | 1<<9)

//@ref USART_StopBits_define
#define USART_StopBits_HALF						  (uint16_t)(0b01<<12)
#define USART_StopBits_ONE						  (uint16_t)(0)
#define USART_StopBits_ONE_HALF					  (uint16_t)(0b11<<12)
#define USART_StopBits_TWO						  (uint16_t)(0b10<<12)

//@ref USART_FlowCtrl_define
#define USART_FlowCtrl_NONE    					  (uint16_t)(0)
#define USART_FlowCtrl_CTS_Enable    			  (uint16_t)(1<<9)
#define USART_FlowCtrl_RTS_Enable				  (uint16_t)(1<<8)
#define USART_FlowCtrl_CTS_RTS_Enable			  (uint16_t)(1<<8 | 1<<9)

//@ref USART_IRQ_Enable_define
#define USART_IRQ_Enable_NONE                     (uint16_t)(0)
#define USART_IRQ_Enable_TXE                      (uint16_t)(1<<7) // transmit data register empty
#define USART_IRQ_Enable_TC                       (uint16_t)(1<<6) // transmission complete
#define USART_IRQ_Enable_RXNEIE                   (uint16_t)(1<<5) // Received data ready to be read & Overrun error detected
#define USART_IRQ_Enable_PE                       (uint16_t)(1<<8) //Parity error


enum polling_mecism {
	Enable,Disable
};
//----------------------------------------------------------
// =========================ABIS===========================
//----------------------------------------------------------

void MCAL_UART_Init(USART_TypeDef *USARTx,UART_Config *UART_Config);
void MCAL_UART_DeInit(USART_TypeDef *USARTx);
void MCAL_UART_SendData(USART_TypeDef *USARTx,uint16_t *pTxBuffer,enum polling_mecism pollingEn);
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx,uint16_t *pRxBuffer,enum polling_mecism pollingEn);
void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx);

// todo MCAL_USART_Init();         Synchronous
// todo MCAL_USART_LIN_Init();     LIN
// todo MCAL_USART_DMA_Init();     DMA Multi buffer communications

//BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 =uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100

#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )

#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
