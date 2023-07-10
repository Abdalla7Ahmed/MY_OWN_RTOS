/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: ٠٦‏/٠٢‏/٢٠٢٣
 *      Author: Abotaleb
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_

#include "STM32F103C6.h"
#include "STM32F103C6_I2C_Driver.h"



#define EEPROM_Slave_Address 			0x2A


void EEPROM_init(void);
uint8_t EEPROM_Write_Nbyte(uint32_t Memory_Address,uint8_t *Data_out,uint8_t DataLen);
uint8_t EEPROM_Read_Nbyte(uint32_t Memory_Address,uint8_t *Data_out,uint8_t DataLen);


#endif /* INC_I2C_SLAVE_EEPROM_H_ */
