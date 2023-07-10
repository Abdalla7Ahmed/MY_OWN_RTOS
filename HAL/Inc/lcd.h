/*
 * LCD.h
 *
 * Created: 14/09/2022 01:27:17 ص
 *  Author: Abotaleb
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL
#include "STM32F103C6.h"
#include "STM32F103C6_GPIO_Driver.h"

/*=========================== User Layer ===================================*/
#define LCD_PORT GPIOA
#define LCD_CTRL GPIOA
#define RS_SWITCH GPIO_PIN_10
#define RW_SWITCH GPIO_PIN_9
#define EN_SWITCH GPIO_PIN_8

#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE
/*==================================================================================*/


#ifdef EIGHT_BIT_MODE
	#define DATA_shift 0
#endif
#ifdef FOUR_BIT_MODE
	#define DATA_shift 4 
#endif

/*================ Commands ===============================*/
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)
/*=================================================================*/


/*===================Functions declaration======================*/
void LCD_INIT();
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char character);
void LCD_WRITE_STRING(char* string);
void LCD_check_lcd_isbusy(void);
void LCD_lcd_kick(void);
void LCD_clear_screen();
void LCD_GOTO_XY(unsigned char line, unsigned char position);
void LCD_DISPLAY_NUMBER(uint32_t number);
void LCD_DISPLAY_REAL_NUMBER(double number);
void Wait_m(uint32_t time);
/*=================================================================*/


#endif /* LCD_H_ */
