/*I2C_stretching_Enable
 * I2C_Slave_EEPROM.c
 *
 *  Created on: ٠٦‏/٠٢‏/٢٠٢٣
 *      Author: Abotaleb
 */


#include "I2C_Slave_EEPROM.h"

void EEPROM_init(void)
{
	I2C_Config I2C_Configuration;
	I2C_Configuration.I2C_ACK_control = I2C_ACK_Enable;
	I2C_Configuration.I2C_clock_speed = I2C_SM_100K;
	I2C_Configuration.I2C_Mode = I2C_Mode_I2C;
	I2C_Configuration.stretching_mode=I2C_stretching_Enable;
	I2C_Configuration.I2C_General_call_address_detection = I2C_ENGC_Enable;
	I2C_Configuration.P_Slave_Event_CallBack = NULL;
	I2C_Configuration.I2C_Slave_Device_Address.I2C_Addressing_Slave_Mode = I2C_Addressing_Slave_7bit;
	MCAL_I2C_Init(I2C1, &I2C_Configuration);



}
uint8_t EEPROM_Write_Nbyte(uint32_t Memory_Address,uint8_t *Data_out,uint8_t DataLen)
{
	int counter;
	uint8_t buffer[256];
	buffer[0] = (uint8_t)(Memory_Address >>8);
	buffer[1] = (uint8_t)(Memory_Address);
	for (counter = 2; counter < DataLen +2; counter++)
	{
		buffer[counter] = Data_out[counter-2];
	}
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, (DataLen +2), With_Stop_bit, Start_bit);
	return 0;

}
uint8_t EEPROM_Read_Nbyte(uint32_t Memory_Address,uint8_t *Data_out,uint8_t DataLen)
{
	uint8_t buffer[2];
	buffer[0] = (uint8_t)(Memory_Address >>8);
	buffer[1] = (uint8_t)(Memory_Address);
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer,2, Without_Stop_bit, Start_bit);

	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, Data_out,DataLen, With_Stop_bit, Repeated_Start_bit);

	return 0;
}
