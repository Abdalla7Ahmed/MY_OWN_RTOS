/*
 * STM32F103C6_SPI_Driver.h
 *
 *  Created on: ٠٣‏/٠٢‏/٢٠٢٣
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_SPI_DRIVER_H_
#define INC_STM32F103C6_SPI_DRIVER_H_

#include "STM32F103C6.h"


typedef struct
{
	uint8_t TXEI:1     ;         // Tx buffer empty interrupt
	uint8_t RXNEI:1    ;		 // RX buffer is not empty buffer
	uint8_t ERRI:1     ;		 // Error interrupt
	uint8_t reserved:5 ;		 // reserved bits in struct
}IRQ_source;

typedef struct
{
	// Specify the mode of SPI
	//this parameter must be set based on @ref SPI_Device_Mode_Define
	uint16_t Device_mode ;
	// Specify the mode of SPI bidirectional mode
	//this parameter must be set based on @ref SPI_Direction_define
	uint16_t Communication_mode;
	// Specify the the type of sending data
	//this parameter must be set based on @ref SPI_Frame_formate_define
	uint16_t Frame_formate;
	// Specify the size of sending data
	//this parameter must be set based on @ref SPI_Data_Size_define
	uint16_t Data_size;
	// Specify the the polarity of the clock
	//this parameter must be set based on @ref SPI_CLK_Polarity_define
	uint16_t CLK_Polarity;
	// Specify the the Phase of the clock
	//this parameter must be set based on @ref SPI_CLK_Phase_define
	uint16_t CLK_Phase;
	// Specify whether Nss is Hardware or software
	//this parameter must be set based on @ref SPI_NSS_define
	uint16_t NSS;
	// Specify the baud rate of the SPI
	//this parameter must be set based on @ref SPI_Baud_rate_define
	uint16_t Baud_rate;
	// Specify the type of interrupt will enabled
	//this parameter must be set based on @ref SPI_IRQ_Enable_define
	uint16_t IRQ_Enable;
	// Set the c function which will be called once the IRQ happened.
	void(* P_IRQ_CallBack)(IRQ_source);
}SPI_Config;




//----------------------------------------------------------
// Macros configuration references
//----------------------------------------------------------

//@ref SPI_Device_Mode_Define
#define SPI_Device_Mode_Slave 							   (uint16_t)(0x0)  //SPI_CR1.2 : the SPI will be Slave
#define SPI_Device_Mode_Master							   (uint16_t)(1<<2) //SPI_CR1.2 : the SPI will be Master

//@ref SPI_Direction_define
#define SPI_Direction_2_line_unidirectional                (uint16_t)(0x0)    //SPI_CR1.15 : two line enable
#define SPI_Direction_2_line_bidirectional_received_only   (uint16_t)(0x0)	  //SPI_CR1.15,10 : two line received only
#define SPI_Direction_2_line_bidirectional_Full_duplex     (uint16_t)(1<<10)  //SPI_CR1.15,10 : two line received and transmit
#define SPI_Direction_1_line_bidirectional_received_only   (uint16_t)(1<<15)  //SPI_CR1.15,14 : one line received only
#define SPI_Direction_1_line_bidirectional_transmit_only   (uint16_t)((1<<15) | (1<<14)) //SPI_CR1.15,14 : one line transmit only


//@ref SPI_Frame_formate_define
#define SPI_Frame_formate_LSB_First                   	   (uint16_t)(1<<7)  //SPI_CR1.7 : least significant bit will send first
#define SPI_Frame_formate_MSB_First					       (uint16_t)(0x0)	 //SPI_CR1.7 : Most significant bit will send first


// @ref SPI_Data_Size_define
#define SPI_Data_Size_8_Bits 							   (uint16_t)(0)     //SPI_CR1.16 : 8-bit data frame format is selected for transmission/reception
#define SPI_Data_Size_16_Bits					     	   (uint16_t)(1<<16) //SPI_CR1.16 : 16-bit data frame format is selected for transmission/reception

//@ref SPI_CLK_Polarity_define
#define SPI_CLK_Polarity_0_When_Idle					    (uint16_t)(0x0)  //SPI_CR1.1 : ClocK to 0 when idle
#define SPI_CLK_Polarity_1_When_Idle						(uint16_t)(1<<1) //SPI_CR1.1 : ClocK to 1 when idle


//@ref SPI_CLK_Phase_define
#define SPI_CLK_Phase_capture_IN_first_edge   			     (uint16_t)(0x0)  //SPI_CR1.0 : The first clock transition is the first data capture edge
#define SPI_CLK_Phase_capture_IN_second_edge    			 (uint16_t)(1<<0) //SPI_CR1.0 : The second clock transition is the first data capture edge

//@ref SPI_NSS_define
#define SPI_NSS_HW_slave                     				 (uint16_t)(0)    //SPI_CR1.9 : enable Hardware NSS and disable software
#define SPI_NSS_HW_Master_Outout_Disable                     (uint16_t)(~(1<<2))	  //SPI_CR2.2 : Hardware output disable
#define SPI_NSS_HW_Master_Outout_enable                      (uint16_t)(1<<2) //SPI_CR2.2 : Hardware output enable
#define SPI_NSS_SW_Set                     					 (uint16_t)((1<<8) |(1<<9))	  //SPI_CR1.8,9 :
#define SPI_NSS_SW_Reset                     				 (uint16_t)(1<<9)	  	      //SPI_CR1.8,9 :

//@ref SPI_Baud_rate_define
#define SPI_Baud_rate_Fpclk_Div_2							 (uint16_t)(0)      	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 2
#define SPI_Baud_rate_Fpclk_Div_4							 (uint16_t)(0b001<<3)      //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 4
#define SPI_Baud_rate_Fpclk_Div_8							 (uint16_t)(0b010<<3)	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 8
#define SPI_Baud_rate_Fpclk_Div_16							 (uint16_t)(0b011<<3)	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 16
#define SPI_Baud_rate_Fpclk_Div_32							 (uint16_t)(0b100<<3)	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 32
#define SPI_Baud_rate_Fpclk_Div_64							 (uint16_t)(0b101<<3)	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 64
#define SPI_Baud_rate_Fpclk_Div_128							 (uint16_t)(0b110<<3)	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 128
#define SPI_Baud_rate_Fpclk_Div_256							 (uint16_t)(0b111<<3)	   //SPI_CR1 3-->5 : the baud rate is the frequency of the bus divided by 256

//@ref SPI_IRQ_Enable_define
#define SPI_IRQ_Enable_NONE									 (uint16_t)(0)
#define SPI_IRQ_Enable_TXEIE								 (uint16_t)(1<<7)			//SPI_CR2.7  :  TX buffer empty interrupt
#define SPI_IRQ_Enable_RXNEIE								 (uint16_t)(1<<6)			//SPI_CR2.7  :	RX buffer not empty interrupt
#define SPI_IRQ_Enable_ERRIE								 (uint16_t)(1<<5)			//SPI_CR2.7  :	ERROR interrupt


enum SPI_polling_mecism {
	SPI_polling_Enable,
	SPI_polling_Disable
};
//----------------------------------------------------------
// =========================ABIS===========================
//----------------------------------------------------------

void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config *SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);
void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer,enum SPI_polling_mecism polling_state);
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16_t *pRxBuffer,enum SPI_polling_mecism polling_state);
void MCAL_SPI_ReceiveANDTransmitData(SPI_TypeDef *SPIx,uint16_t *pBuffer,enum SPI_polling_mecism polling_state);


#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
