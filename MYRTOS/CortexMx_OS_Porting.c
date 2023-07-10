/*
|========================================================================|
|File             |:- CortexMx_OS_Porting.c				-:|
|Author           |:- Abdallah Ahmed Mohammed   		-:|
|Created on       |:- 3/7/2023     `					-:|
|========================================================================|
*/

#include "CortexMx_OS_Porting.h"



void HardFault_Handler(void)
{

	while(1);
}
void MemManage_Handler(void)
{

	while(1);
}
void BusFault_Handler(void)
{

	while(1);
}
void UsageFault_Handler(void)
{

	while(1);
}




__attribute ((naked)) void SVC_Handler()
{
	__asm("TST LR,#4");
	__asm("ITE EQ"); 		/*if then equal*/
	__asm("MRSEQ R0,MSP");	/*Main stack pointer*/
	__asm("MRSNE R0,PSP");  /*Process stack pointer*/
	__asm("B OS_SVC");
}



void MYRTOS_HW_Init(void)
{





	// decrease PendSV interrupt priority to be smaller than or equal systiK timer
	__NVIC_SetPriority(PendSV_IRQn,15);

}


void Trigger_OS_PendSV(void)
{
	// Set PendSV
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;

}

void MYRTOS_Start_Ticker(void)
{
	// CPU frequency = 8MHZ
	// every tick = 1 / 8M = .125us
	// 1ms = 1/.125m = 8000 ticks
	SysTick_Config(8000);

}

