/*
 * Kaypad.c
 *
 * Created: 14/09/2022 07:35:38 AM
 *  Author: Abotaleb
 */ 

#include "Kaypad.h"

GPIO_PinConfig_t PinConfigKayPad;

uint32_t Kaypad_column[]={C0,C1,C2,C3};
uint32_t Kaypad_Row[]={R0,R1,R2,R3};

void KAYPAD_INIT()
{

	PinConfigKayPad.GPIO_PinNumber= R0;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);

	PinConfigKayPad.GPIO_PinNumber= R1;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);

	PinConfigKayPad.GPIO_PinNumber= R2;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);

	PinConfigKayPad.GPIO_PinNumber= R3;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);


	// ========================================================

	PinConfigKayPad.GPIO_PinNumber= C0;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);

	PinConfigKayPad.GPIO_PinNumber= C1;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);

	PinConfigKayPad.GPIO_PinNumber= C2;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);

	PinConfigKayPad.GPIO_PinNumber= C3;
	PinConfigKayPad.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	PinConfigKayPad.GPIO_OUTPUT_SPEED=GPIO_OUTPUT_SPEED_10M;
	MCAL_GPIO_INIT(KAYPAD_PORT, &PinConfigKayPad);
	MCAL_GPIO_WRITE_PORT(KAYPAD_PORT, 0xFF);

}
char GET_CHARACTER()
{
	uint32_t i,j;
	for (i=0;i<4;i++)
	{
		MCAL_GPIO_WRITE_PIN(KAYPAD_PORT,Kaypad_column[0],GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KAYPAD_PORT,Kaypad_column[1],GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KAYPAD_PORT,Kaypad_column[2],GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KAYPAD_PORT,Kaypad_column[3],GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KAYPAD_PORT,Kaypad_column[i],GPIO_PIN_RESET);
		for (j=0;j<4;j++)
		{

			if (MCAL_GPIO_READ_PIN(KAYPAD_PORT, Kaypad_Row[j])==0)
			{
				while (MCAL_GPIO_READ_PIN(KAYPAD_PORT, Kaypad_Row[j])==0);
				switch(i)
				{
				case 0:
				{
					if (j==0)
					{
						return '7';
					}
					else if (j==1)
					{
						return '4';
					}
					else if (j==2)
					{
						return '1';
					}
					else if (j==3)
					{
						return 'C';
					}
					break;
				}
				case 1:
				{
					if (j==0)
					{
						return '8';
					}
					else if (j==1)
					{
						return '5';
					}
					else if (j==2)
					{
						return '2';
					}
					else if (j==3)
					{
						return '0';
					}
					break;
				}
				case 2:
				{
					if (j==0)
					{
						return '9';
					}
					else if (j==1)
					{
						return '6';
					}
					else if (j==2)
					{
						return '3';
					}
					else if (j==3)
					{
						return '=';
					}
					break;
				}
				case 3:
				{
					if (j==0)
					{
						return '/';
					}
					else if (j==1)
					{
						return '*';
					}
					else if (j==2)
					{
						return '-';
					}
					else if (j==3)
					{
						return '+';
					}
					break;
				}
				}
			}
		}

	}
	return 'N'; // return null 
}

//void SET_KAYPAD_COLUMN()
//{
//	uint32_t count;
//	for (count=0;count<4;count++)
//	{
//		MCAL_GPIO_WRITE_PIN(KAYPAD_PORT, Kaypad_column[count], GPIO_PIN_SET);
//	}
//}
