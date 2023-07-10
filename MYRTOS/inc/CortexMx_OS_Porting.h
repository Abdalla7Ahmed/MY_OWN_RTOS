/*
|========================================================================|
|File             |:- CortexMx_OS_Porting.h				-:|
|Author           |:- Abdallah Ahmed Mohammed   		-:|
|Created on       |:- 3/7/2023     `					-:|
|========================================================================|
*/

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_


#include "core_cm3.h"
#include "stdio.h"
#include "string.h"


extern int _estack ;
extern int _eheap  ;

#define Main_Stack_Size       3072            // 3K = 3*1024 = 3072



/* Switch CPU Access Level */
#define Switch_To_Privileged_Access_Level			__asm volatile("MRS R3,CONTROL \n\t LSR R3,R3,#0x1 \n\t LSL R3,R3,#0x1 \n\t MSR CONTROL,R3");
#define Switch_To_UnPrivileged_Access_Level			__asm volatile("MRS R3,CONTROL \n\t ORR R3,R3,#0x1 \n\t  MSR CONTROL,R3");



/*SET and GET PSP */
#define OS_SET_PSP(address)				   			 __asm volatile("MOV R0 , %0    \n\t MSR PSP , R0 " : :"r"  (address))
#define OS_GET_PSP(address)				   			 __asm volatile("MRS R0 ,PSP    \n\t MOV %0  , R0 " : "=r" (address))


/* Switch SP */
#define OS_Switch_SP_to_PSP			 			  	__asm volatile("MRS R0,CONTROL \n\t MOV R1  , #0x02 \n\t ORR R0,R0,R1 \n\t MSR CONTROL,R0")
#define OS_Switch_SP_to_MSP		 					__asm volatile("MRS R0,CONTROL \n\t MOV R1  , #0x05 \n\t AND R0,R0,R1 \n\t MSR CONTROL,R0")


void MYRTOS_HW_Init(void);
void Trigger_OS_PendSV(void);
void MYRTOS_Start_Ticker(void);


#endif /* INC_CORTEXMX_OS_PORTING_H_ */
