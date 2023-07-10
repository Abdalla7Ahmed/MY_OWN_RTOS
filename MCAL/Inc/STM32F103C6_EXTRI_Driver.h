/*
 * EXTRI_Driver.h
 *
 *  Created on: ١٩‏/٠٩‏/٢٠٢٢
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_EXTRI_DRIVER_H_
#define INC_STM32F103C6_EXTRI_DRIVER_H_

/**================================================================
*
* 1: EXTRI_GPIO_Mapping_t structure
* 2: @ref  EXTRI_Number
* 3: @ref EXTRI_define
* 4: @ref EXTRI_Trigger_define
* 5: @ref EXTRI_IRQ_define
* 6: APIs
================================================================**/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------------------------------------------------
// Includes
//----------------------------------------------------------
#include "../../MCAL/Inc/STM32F103C6.h"
#include "../../MCAL/Inc/STM32F103C6_GPIO_Driver.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//----------------------------------------------------------
// User type definitions
//----------------------------------------------------------
//1: EXTRI_GPIO_Mapping_t structure
typedef struct
{
	uint16_t       EXTRI_InputLine ;
	GPIO_TypeDef   *GPIO_PORT      ;
	uint16_t       GPIO_PinNumber  ;
	uint8_t        IVT_IRQ_Number  ;
}EXTRI_GPIO_Mapping_t;

typedef struct
{
	// specifies the EXTRI interrupt  GPIO mapping.
    // the parameters can be value of @ref EXTRI_define.
	EXTRI_GPIO_Mapping_t PIN_INPUT ;
	// specifies the trigger case .
    // the parameters can be set based on @ref EXTRI_Trigger_define.(subject 4)
	uint8_t              EXTRI_Trigger_Case;
	// Enable or Disable the external interrupt .
	// the parameters can be set based on @ref EXTRI_IRQ_define.
	uint8_t              IRQ_ENABLE;
	// Set the c function which will be called once the IRQ happened.
	void(* P_IRQ_CallBack)(void);

}EXTRI_PinConfig_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------------------------------------------------
// Macros configuration references
//----------------------------------------------------------
// 2-@ref  EXTRI_Number
#define EXTRI0                   0
#define EXTRI1                   1
#define EXTRI2                   2
#define EXTRI3                   3
#define EXTRI4                   4
#define EXTRI5                   5
#define EXTRI6                   6
#define EXTRI7                   7
#define EXTRI8                   8
#define EXTRI9                   9
#define EXTRI10                  10
#define EXTRI11                  11
#define EXTRI12                  12
#define EXTRI13                  13
#define EXTRI14                  14
#define EXTRI15                  15
//3-@ref EXTRI_define
//EXTRI0
#define EXTRI0PA0                            (EXTRI_GPIO_Mapping_t){EXTRI0,GPIOA,GPIO_PIN_0,EXTRI0_IRQ}
#define EXTRI0PB0                            (EXTRI_GPIO_Mapping_t){EXTRI0,GPIOB,GPIO_PIN_0,EXTRI0_IRQ}
#define EXTRI0PC0                            (EXTRI_GPIO_Mapping_t){EXTRI0,GPIOC,GPIO_PIN_0,EXTRI0_IRQ}
#define EXTRI0PD0                            (EXTRI_GPIO_Mapping_t){EXTRI0,GPIOD,GPIO_PIN_0,EXTRI0_IRQ}


//EXTRI1
#define EXTRI1PA1                            (EXTRI_GPIO_Mapping_t){EXTRI1,GPIOA,GPIO_PIN_1,EXTRI1_IRQ}
#define EXTRI1PB1                            (EXTRI_GPIO_Mapping_t){EXTRI1,GPIOB,GPIO_PIN_1,EXTRI1_IRQ}
#define EXTRI1PC1                            (EXTRI_GPIO_Mapping_t){EXTRI1,GPIOC,GPIO_PIN_1,EXTRI1_IRQ}
#define EXTRI1PD1                            (EXTRI_GPIO_Mapping_t){EXTRI1,GPIOD,GPIO_PIN_1,EXTRI1_IRQ}


//EXTRI2
#define EXTRI2PA2                            (EXTRI_GPIO_Mapping_t){EXTRI2,GPIOA,GPIO_PIN_2,EXTRI2_IRQ}
#define EXTRI2PB2                            (EXTRI_GPIO_Mapping_t){EXTRI2,GPIOB,GPIO_PIN_2,EXTRI2_IRQ}
#define EXTRI2PC2                            (EXTRI_GPIO_Mapping_t){EXTRI2,GPIOC,GPIO_PIN_2,EXTRI2_IRQ}
#define EXTRI2PD2                            (EXTRI_GPIO_Mapping_t){EXTRI2,GPIOD,GPIO_PIN_2,EXTRI2_IRQ}


//EXTRI3
#define EXTRI3PA3                            (EXTRI_GPIO_Mapping_t){EXTRI3,GPIOA,GPIO_PIN_3,EXTRI3_IRQ}
#define EXTRI3PB3                            (EXTRI_GPIO_Mapping_t){EXTRI3,GPIOB,GPIO_PIN_3,EXTRI3_IRQ}
#define EXTRI3PC3                            (EXTRI_GPIO_Mapping_t){EXTRI3,GPIOC,GPIO_PIN_3,EXTRI3_IRQ}
#define EXTRI3PD3                            (EXTRI_GPIO_Mapping_t){EXTRI3,GPIOD,GPIO_PIN_3,EXTRI3_IRQ}


//EXTRI4
#define EXTRI4PA4                            (EXTRI_GPIO_Mapping_t){EXTRI4,GPIOA,GPIO_PIN_4,EXTRI4_IRQ}
#define EXTRI4PB4                            (EXTRI_GPIO_Mapping_t){EXTRI4,GPIOB,GPIO_PIN_4,EXTRI4_IRQ}
#define EXTRI4PC4                            (EXTRI_GPIO_Mapping_t){EXTRI4,GPIOC,GPIO_PIN_4,EXTRI4_IRQ}
#define EXTRI4PD4                            (EXTRI_GPIO_Mapping_t){EXTRI4,GPIOD,GPIO_PIN_4,EXTRI4_IRQ}


//EXTRI5
#define EXTRI5PA5                            (EXTRI_GPIO_Mapping_t){EXTRI5,GPIOA,GPIO_PIN_5,EXTRI5_IRQ}
#define EXTRI5PB5                            (EXTRI_GPIO_Mapping_t){EXTRI5,GPIOB,GPIO_PIN_5,EXTRI5_IRQ}
#define EXTRI5PC5                            (EXTRI_GPIO_Mapping_t){EXTRI5,GPIOC,GPIO_PIN_5,EXTRI5_IRQ}
#define EXTRI5PD5                            (EXTRI_GPIO_Mapping_t){EXTRI5,GPIOD,GPIO_PIN_5,EXTRI5_IRQ}


//EXTRI6
#define EXTRI6PA6                            (EXTRI_GPIO_Mapping_t){EXTRI6,GPIOA,GPIO_PIN_6,EXTRI6_IRQ}
#define EXTRI6PB6                            (EXTRI_GPIO_Mapping_t){EXTRI6,GPIOB,GPIO_PIN_6,EXTRI6_IRQ}
#define EXTRI6PC6                            (EXTRI_GPIO_Mapping_t){EXTRI6,GPIOC,GPIO_PIN_6,EXTRI6_IRQ}
#define EXTRI6PD6                            (EXTRI_GPIO_Mapping_t){EXTRI6,GPIOD,GPIO_PIN_6,EXTRI6_IRQ}


//EXTRI7
#define EXTRI7PA7                            (EXTRI_GPIO_Mapping_t){EXTRI7,GPIOA,GPIO_PIN_7,EXTRI7_IRQ}
#define EXTRI7PB7                            (EXTRI_GPIO_Mapping_t){EXTRI7,GPIOB,GPIO_PIN_7,EXTRI7_IRQ}
#define EXTRI7PC7                            (EXTRI_GPIO_Mapping_t){EXTRI7,GPIOC,GPIO_PIN_7,EXTRI7_IRQ}
#define EXTRI7PD7                            (EXTRI_GPIO_Mapping_t){EXTRI7,GPIOD,GPIO_PIN_7,EXTRI7_IRQ}


//EXTRI8
#define EXTRI8PA8                            (EXTRI_GPIO_Mapping_t){EXTRI8,GPIOA,GPIO_PIN_8,EXTRI8_IRQ}
#define EXTRI8PB8                            (EXTRI_GPIO_Mapping_t){EXTRI8,GPIOB,GPIO_PIN_8,EXTRI8_IRQ}
#define EXTRI8PC8                            (EXTRI_GPIO_Mapping_t){EXTRI8,GPIOC,GPIO_PIN_8,EXTRI8_IRQ}
#define EXTRI8PD8                            (EXTRI_GPIO_Mapping_t){EXTRI8,GPIOD,GPIO_PIN_8,EXTRI8_IRQ}


//EXTRI9
#define EXTRI9PA9                            (EXTRI_GPIO_Mapping_t){EXTRI9,GPIOA,GPIO_PIN_9,EXTRI9_IRQ}
#define EXTRI9PB9                            (EXTRI_GPIO_Mapping_t){EXTRI9,GPIOB,GPIO_PIN_9,EXTRI9_IRQ}
#define EXTRI9PC9                            (EXTRI_GPIO_Mapping_t){EXTRI9,GPIOC,GPIO_PIN_9,EXTRI9_IRQ}
#define EXTRI9PD9                            (EXTRI_GPIO_Mapping_t){EXTRI9,GPIOD,GPIO_PIN_9,EXTRI9_IRQ}


//EXTRI10
#define EXTRI10PA10                           (EXTRI_GPIO_Mapping_t){EXTRI10,GPIOA,GPIO_PIN_10,EXTRI10_IRQ}
#define EXTRI10PB10                           (EXTRI_GPIO_Mapping_t){EXTRI10,GPIOB,GPIO_PIN_10,EXTRI10_IRQ}
#define EXTRI10PC10                           (EXTRI_GPIO_Mapping_t){EXTRI10,GPIOC,GPIO_PIN_10,EXTRI10_IRQ}
#define EXTRI10PD10                           (EXTRI_GPIO_Mapping_t){EXTRI10,GPIOD,GPIO_PIN_10,EXTRI10_IRQ}


//EXTRI11
#define EXTRI11PA11                           (EXTRI_GPIO_Mapping_t){EXTRI11,GPIOA,GPIO_PIN_11,EXTRI11_IRQ}
#define EXTRI11PB11                           (EXTRI_GPIO_Mapping_t){EXTRI11,GPIOB,GPIO_PIN_11,EXTRI11_IRQ}
#define EXTRI11PC11                           (EXTRI_GPIO_Mapping_t){EXTRI11,GPIOC,GPIO_PIN_11,EXTRI11_IRQ}
#define EXTRI11PD11                           (EXTRI_GPIO_Mapping_t){EXTRI11,GPIOD,GPIO_PIN_11,EXTRI11_IRQ}


//EXTRI12
#define EXTRI12PA12                           (EXTRI_GPIO_Mapping_t){EXTRI12,GPIOA,GPIO_PIN_12,EXTRI12_IRQ}
#define EXTRI12PB12                           (EXTRI_GPIO_Mapping_t){EXTRI12,GPIOB,GPIO_PIN_12,EXTRI12_IRQ}
#define EXTRI12PC12                           (EXTRI_GPIO_Mapping_t){EXTRI12,GPIOC,GPIO_PIN_12,EXTRI12_IRQ}
#define EXTRI12PD12                           (EXTRI_GPIO_Mapping_t){EXTRI12,GPIOD,GPIO_PIN_12,EXTRI12_IRQ}

//EXTRI13
#define EXTRI13PA13                           (EXTRI_GPIO_Mapping_t){EXTRI13,GPIOA,GPIO_PIN_13,EXTRI13_IRQ}
#define EXTRI13PB13                           (EXTRI_GPIO_Mapping_t){EXTRI13,GPIOB,GPIO_PIN_13,EXTRI13_IRQ}
#define EXTRI13PC13                           (EXTRI_GPIO_Mapping_t){EXTRI13,GPIOC,GPIO_PIN_13,EXTRI13_IRQ}
#define EXTRI13PD13                           (EXTRI_GPIO_Mapping_t){EXTRI13,GPIOD,GPIO_PIN_13,EXTRI13_IRQ}


//EXTRI14
#define EXTRI14PA14                           (EXTRI_GPIO_Mapping_t){EXTRI14,GPIOA,GPIO_PIN_14,EXTRI14_IRQ}
#define EXTRI14PB14                           (EXTRI_GPIO_Mapping_t){EXTRI14,GPIOB,GPIO_PIN_14,EXTRI14_IRQ}
#define EXTRI14PC14                           (EXTRI_GPIO_Mapping_t){EXTRI14,GPIOC,GPIO_PIN_14,EXTRI14_IRQ}
#define EXTRI14PD14                           (EXTRI_GPIO_Mapping_t){EXTRI14,GPIOD,GPIO_PIN_14,EXTRI14_IRQ}

//4-@ref EXTRI_Trigger_define
#define EXTRI_Trigger_Failing                 0
#define EXTRI_Trigger_Rising                  1
#define EXTRI_Trigger_RisingANDFailing        2

//5-@ref EXTRI_IRQ_define
#define EXTRI_IRQ_Disable                     0
#define EXTRI_IRQ_Enable                      1


// 6- APIS
//----------------------------------------------------------
// ABIs supported by MCAL GPIO Driver
//----------------------------------------------------------

void MCAL_EXTRI_GPIO_INIT(EXTRI_PinConfig_t *EXTRI_Config);
void MCAL_EXTRI_GPIO_Update(EXTRI_PinConfig_t *EXTRI_Config);
void MCAL_EXTRI_GPIO_DEINIT(void);






#endif /* INC_STM32F103C6_EXTRI_DRIVER_H_ */
