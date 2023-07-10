/*
 * STM32F103C6_GPIO_Drivers.h
 *
 *  Created on: Sep 15, 2022
 *      Author: Abotaleb
 */

#ifndef INC_STM32F103C6_GPIO_DRIVERS_H_
#define INC_STM32F103C6_GPIO_DRIVERS_H_

/**================================================================
*
* 1: GPIO_PinConfig_t structure
* 2: @ref GPIO_PIN_define
* 3: @ref GPIO_MODE_define
* 4: @ref GPIO_OUTPUT_SPEED_define
* 5: @ref GPIO_PIN_state
* 6: @ref GPIO_RETURNE_LOCK_State
* 7: APIs
================================================================**/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------------------------------------------------
// Includes
//----------------------------------------------------------
#include "../../MCAL/Inc/STM32F103C6.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//----------------------------------------------------------
// User type definitions
//----------------------------------------------------------
//1: GPIO_PinConfig_t structure
typedef struct
{
	// specifies the GPIO pins to be configured.
    // the parameters must be set based on @ref GPIO_PIN_define
	uint16_t GPIO_PinNumber ;
	// specifies the operation mode for the selected pins.
    // the parameters can be value of @ref GPIO_MODE_define
	uint8_t GPIO_MODE       ;
	// specifies the operation speed for the selected pins in order to the pin is output.
	// the parameters can be value of @ref GPIO_OUTPUT_SPEED_define
	uint8_t GPIO_OUTPUT_SPEED  ;

}GPIO_PinConfig_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------------------------------------------------
// Macros configuration references
//----------------------------------------------------------
//2: @ref GPIO_PIN_define
#define GPIO_PIN_0             ((uint16_t)0x0001U) // pin 0      0b0000 0000 0000 0001
#define GPIO_PIN_1             ((uint16_t)0x0002U) // pin 1      0b0000 0000 0000 0010
#define GPIO_PIN_2             ((uint16_t)0x0004U) // pin 2      0b0000 0000 0000 0100
#define GPIO_PIN_3 	           ((uint16_t)0x0008U) // pin 3      0b0000 0000 0000 1000
#define GPIO_PIN_4             ((uint16_t)0x0010U) // pin 4      0b0000 0000 0001 0000
#define GPIO_PIN_5             ((uint16_t)0x0020U) // pin 5      0b0000 0000 0010 0000
#define GPIO_PIN_6             ((uint16_t)0x0040U) // pin 6      0b0000 0000 0100 0000
#define GPIO_PIN_7             ((uint16_t)0x0080U) // pin 7      0b0000 0000 1000 0000
#define GPIO_PIN_8             ((uint16_t)0x0100U) // pin 8      0b0000 0001 0000 0000
#define GPIO_PIN_9             ((uint16_t)0x0200U) // pin 9      0b0000 0010 0000 0000
#define GPIO_PIN_10            ((uint16_t)0x0400U) // pin 10     0b0000 0100 0000 0000
#define GPIO_PIN_11            ((uint16_t)0x0800U) // pin 11     0b0000 1000 0000 0000
#define GPIO_PIN_12            ((uint16_t)0x1000U) // pin 12     0b0001 0000 0000 0000
#define GPIO_PIN_13            ((uint16_t)0x2000U) // pin 13     0b0010 0000 0000 0000
#define GPIO_PIN_14            ((uint16_t)0x4000U) // pin 14     0b0100 0000 0000 0000
#define GPIO_PIN_15            ((uint16_t)0x8000U) // pin 15     0b1000 0000 0000 0000
#define GPIO_PINS_All          ((uint16_t)0xFFFFU) // all pins from 0 to 15            0b1111 1111 1111 1111

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//3: @ref GPIO_MODE_define
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input
#define GPIO_MODE_ANALOG                  0x00000000U    //Analog mode
#define GPIO_MODE_FLOATINg_INPUT          0x00000001U    //Floating input (reset state)
#define GPIO_MODE_INPUT_PU          	  0x00000002U    //Input with pull-up
#define GPIO_MODE_INPUT_PD          	  0x00000003U	 //Input with pull-down
#define GPIO_MODE_OUTPUT_PP          	  0x00000004U    //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD          	  0x00000005U 	 //General purpose output Open-drain
#define GPIO_MODE_ALTERNATIVE_OUTPUT_PP   0x00000006U	 //Alternate function output Push-pull
#define GPIO_MODE_ALTERNATIVE_OUTPUT_OD   0x00000007U    //Alternate function output Open-drain
#define GPIO_MODE_ALTERNATIVE_INPUT       0x00000008U    //Alternate function input
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//4:@ref GPIO_OUTPUT_SPEED_define
//0: Output mode, max speed 10 MHz.
//1: Output mode, max speed 2 MHz.
//2: Output mode, max speed 50 MHz.
#define GPIO_OUTPUT_SPEED_10M                   0x00000001U // Output mode, max speed 10 MHz.
#define GPIO_OUTPUT_SPEED_2M					0x00000002U // Output mode, max speed 2 MHz.
#define GPIO_OUTPUT_SPEED_50M					0x00000003U // Output mode, max speed 50 MHz.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//5:@ref GPIO_PIN_state
#define GPIO_PIN_SET                          1
#define GPIO_PIN_RESET                        0
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//6:@ref GPIO_RETURNE_LOCK_State
#define GPIO_RETURNE_LOCK_DONE                     1
#define GPIO_RETURNE_LOCK_ERROR                    0
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//----------------------------------------------------------
// ABIs supported by MCAL GPIO Driver
//----------------------------------------------------------
//7 : APIs
void MCAL_GPIO_INIT(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DEINIT(GPIO_TypeDef *GPIOx);
// read
uint8_t MCAL_GPIO_READ_PIN(GPIO_TypeDef *GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_READ_PORT(GPIO_TypeDef *GPIOx);
// write
void MCAL_GPIO_WRITE_PIN(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t PinValue);
void MCAL_GPIO_WRITE_PORT(GPIO_TypeDef *GPIOx ,uint16_t PortValue);
// toggle
void MCAL_GPIO_TOGGLE_PIN(GPIO_TypeDef *GPIOx,uint16_t PinNumber);
// lock
uint8_t MCAL_GPIO_LOCK(GPIO_TypeDef *GPIOx,uint16_t PinNumber);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif /* INC_STM32F103C6_GPIO_DRIVERS_H_ */
