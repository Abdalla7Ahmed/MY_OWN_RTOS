/*
 * STM32F103C6_I2C_Driver.h
 *
 *  Created on: ٠٥‏/٠٢‏/٢٠٢٣
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_I2C_DRIVER_H_
#define INC_STM32F103C6_I2C_DRIVER_H_


#include "STM32F103C6.h"
#include "STM32F103C6_GPIO_Driver.h"
#include "STM32F103C6_RCC_Driver.h"
#include "STM32F103C6_RCC_Driver.h"

typedef struct
{
	uint16_t	 DUAL_Address_Enable      ;				// @ref Dual_Address_define
	uint16_t 	 I2C_Addressing_Slave_Mode;			    //@ref I2C_Addressing_Slave_define
	uint16_t 	 Primary_Slave_Address    ;
	uint16_t 	 Secondary_Slave_Address  ;            // if you enable the Dual address


}I2C_Slave_Address;


typedef enum
{
	I2C_EV_STOP        ,
	I2C_ERROR_AF       ,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ	   ,		// the APP layer should send the data(I2C_Slave_Send_Data)
	I2C_EV_DATA_REC				// the APP layer should read the data (I2C_Slave_Receive_Data)
}Slave_state;
typedef struct
{
	// Specify the speed of I2C
	//this parameter must be set based on @ref I2C_Clock_Define
	uint32_t I2C_clock_speed;
	// Enable or Disable the stretching
	//this parameter must be set based on @ref I2C_stretching_Define
	uint16_t stretching_mode;
	// Specify the mode of I2C
	//this parameter must be set based on @ref I2C_Mode_define
	uint16_t I2C_Mode;
	// Specify the primary slave address and the secondary if you enable Dual address
	//this parameter must be set based on struct I2C_Slave_Address
	I2C_Slave_Address I2C_Slave_Device_Address;
	// Enable or disable Acknowledge
	//this parameter must be set based on @ref I2C_ACK_define
	uint16_t I2C_ACK_control;
	// Enable or disable General call enable
	//this parameter must be set based on //@ref I2C_ENGC_define
	uint16_t I2C_General_call_address_detection;
	// Set the c function which will be called once the IRQ happened.
	void(* P_Slave_Event_CallBack)(Slave_state stete);
}I2C_Config;


//----------------------------------------------------------
// Macros configuration references
//----------------------------------------------------------
//@ref I2C_Clock_Define
#define I2C_SM_10K										(uint32_t)(10000U)
#define I2C_SM_20K										(uint32_t)(20000U)
#define I2C_SM_30K										(uint32_t)(30000U)
#define I2C_SM_40K										(uint32_t)(40000U)
#define I2C_SM_50K										(uint32_t)(50000U)
#define I2C_SM_60K										(uint32_t)(60000U)
#define I2C_SM_70K										(uint32_t)(70000U)
#define I2C_SM_80K										(uint32_t)(80000U)
#define I2C_SM_90K										(uint32_t)(90000U)
#define I2C_SM_100K										(uint32_t)(100000U)
// todo
#define I2C_FM_150K										(uint32_t)(150000U)		// Fast mode not supported yet
#define I2C_FM_200K										(uint32_t)(200000U)		// Fast mode not supported yet
#define I2C_FM_400K										(uint32_t)(400000U)		// Fast mode not supported yet

//@ref I2C_stretching_Define
#define I2C_stretching_Enable							 (uint16_t)(0x0)
#define I2C_stretching_Disable							 (uint16_t)(I2C_CR1_NOSTRETCH)


//@ref I2C_Mode_define
#define I2C_Mode_I2C								     (uint16_t)(~I2C_CR1_SMBUS)
#define I2C_Mode_SMBus							 		 (uint16_t)(I2C_CR1_SMBUS)


// @ref Dual_Address_define
#define Dual_Address_Disable							  (uint16_t)(0x0)
#define Dual_Address_Enable							 	  (uint16_t)(I2C_OAR2_ENDUAL)

//@ref I2C_Addressing_Slave_define
#define I2C_Addressing_Slave_7bit						  (uint16_t)(0x0)
#define I2C_Addressing_Slave_10bit						  (uint16_t)(I2C_OAR1_ADDMODE)

//@ref I2C_ACK_define
#define I2C_ACK_Disable						  			  (uint16_t)(0x0)
#define I2C_ACK_Enable						 			  (uint16_t)(I2C_CR1_ACK)


//#define I2C_ACK_Disable						  			  (0x0)
//#define I2C_ACK_Enable						 			  (1)

//@ref I2C_ENGC_define
#define I2C_ENGC_Disable								  (uint16_t)(0x0)
#define I2C_ENGC_Enable						 			  (uint16_t)(I2C_CR1_ENGC)




//#define I2C_EV_Master_Byte_Transmiting


// at the end of the 1 Byte transmission is there stop bit or will continue
typedef enum {
	With_Stop_bit,
	Without_Stop_bit
}Stop_Condition;

// the type of start bit
typedef enum {
	Start_bit,
	Repeated_Start_bit
}Start_Type;

// Check if the flag is set or not
typedef enum
{
	Flag_Reset,
	Flag_SET
}Flage_State;

// the all flags
typedef enum
{
	I2C_Flag_Busy,
	I2C_Start_bit_Flag,           //EV5: SB=1, cleared by reading SR1 register followed by writing the DR register.
	I2C_Stop_bit_Flag,
	I2C_Address_Mathced,			 //EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	I2C_Data_register_Empty,	     //EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
	EV8_1,
	I2C_Data_register_NOT_Empty,	 //EV7:RxNE =1 cleared by reading the DR register
	/*TXE flag BTF flag
	 * TXE flag at 	SR1.7
	 * BTF flag at 	SR1.2
	 */
	EV8_2  = ((uint16_t)0x00000080),
	/*TXE ,TRA , MSL, Busy flag
	 * TXE flag at 	SR1.7
	 * TRA flag at 	SR2.2
	 * MSL flag at 	SR2.1
	 * Busy flag at SR2.0
	 * the total hexa of the two registers is 0x00070080
	 *  */

	I2C_EV_Master_Byte_Transmiting = ((uint32_t)0x00070080)
}Stated_Flag;


typedef enum
{
	Function_State_Enable,
	Function_State_Disable
}Function_State;

typedef enum
{
	I2C_Direction_Transmitter ,
	I2C_Direction_Receiver
}I2C_Direction;

//typedef enum
//{
//	BUS_BUSY,												/* BUSY: Bus busy 1: Communication ongoing on the bus */
//	SB,														/* SB: Start bit (Master mode) 1: Start condition generated. */
//	ADDR,													/* ADDR: Address sent (master mode)/matched (slave mode) */
//	TXE,													/* TxE: Data register empty (transmitters) */
//	RXNE,													/* RxNE: Data register not empty (receivers) */
//	Master_Transmitter_Event = ((uint32_t)(0x00070080))		/* Check if BUSY ,TRA ,MSL W,TXE flags are all set */
//}Status;


////----------------------------------------------------------
//// =========================ABIS===========================
////----------------------------------------------------------
//
void MCAL_I2C_Init(I2C_TypeDef *I2Cx,I2C_Config *I2C_Config);
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx);
void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx,uint32_t device_Address,uint8_t *Data_Out,uint32_t DataLen,Stop_Condition Stop_bit,Start_Type Start_bit );
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx,uint32_t device_Address,uint8_t *Data_Out,uint32_t DataLen,Stop_Condition Stop_bit,Start_Type Start_bit );
void MCAL_I2C_Slave_TX(I2C_TypeDef *I2Cx,uint8_t buffer);
uint8_t MCAL_I2C_Slave_RX(I2C_TypeDef *I2Cx);

// ===================================Generic functions =========================
void MCAL_I2C_GPIO_set_pins(I2C_TypeDef *I2Cx);
void I2C_Generate_Start_bit(I2C_TypeDef *I2Cx,Function_State New_State,Start_Type Start_bit);
void I2C_Generate_Stop_bit(I2C_TypeDef *I2Cx,Function_State New_State);
void I2C_Acknowledge_Config(I2C_TypeDef *I2Cx,Function_State New_State);
Flage_State I2C_Get_Flag_State(I2C_TypeDef *I2Cx,Stated_Flag Flag);
void Send_Slave_Address(I2C_TypeDef *I2Cx,uint8_t device_Address,I2C_Direction Direction);



#endif /* INC_STM32F103C6_I2C_DRIVER_H_ */
