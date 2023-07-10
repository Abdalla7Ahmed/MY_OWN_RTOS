/*
|========================================================================|
|File             |:- Scheduler.h						-:|
|Author           |:- Abdallah Ahmed Mohammed   		-:|
|Created on       |:- 3/7/2023     `					-:|
|========================================================================|
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_



#include "CortexMx_OS_Porting.h"

#define element_type Task_ref*
typedef enum
{
	Task_Suspend,
	Task_Waiting,
	Task_Ready,
	Task_Running
}Task_StateID;

typedef struct
{
	enum
	{
		Blocking_Disable,
		Blocking_Enable
	}Blocking;
	uint32_t Ticks_Count ; // 1000 Ticks mean 1ms
}Timing_Waiting;
typedef struct
{
	// =================== User  Layer =================
	uint32_t Task_Size        ;
	uint8_t  Task_Priority    ;
	void (*P_Task_Entry)(void); // pointer to Task C function
	uint8_t  Task_Name[30]    ;
	uint8_t Task_AutoStart	  ;
	// ================================================
	uint32_t Task_S_PSP       ; // not entered by the user
	uint32_t Task_E_PSP       ; // not entered by the user
	uint32_t* Task_Current_PSP; // not entered by the user
	Task_StateID Task_State   ; // not entered by the user
	Timing_Waiting T_Waiting  ;	// not entered by the user
}Task_ref;

typedef struct
{
	uint8_t *PayLoad;
	uint32_t PayLoadSize;
	Task_ref *Current_Task;
	Task_ref *Next_Task ;
	uint8_t Mutex_Name[30];
	struct
	{
		enum
		{
			PI_Disable,
			PI_Enable
		}Priority_Inheritance_State;
		uint8_t Saved_Pririty; // not entered by the user
	}Priority_Inheritance;
}Mutex_ref;

//Inheritance




typedef enum
{
	MYRTOS_NO_ERROR,
	Ready_Queue_Init_Error,
	Task_Exceeded_StackSize_Error,
	MutexIsReceivedMaxNumberOfTasks
}MYRTOS_Error_Source;




MYRTOS_Error_Source MYRTOS_init(void);
MYRTOS_Error_Source MYRTOS_Creat_Task(Task_ref *Task_x);
void MYRTOS_Activate_Task(Task_ref *Task_x);
void MYRTOS_Terminate_Task(Task_ref *Task_x);
void MYRTOS_Start(void);
void MYRTOS_Task_Wait(uint32_t NoOfTicks,Task_ref *WaitTask);
MYRTOS_Error_Source MYRTOS_Acquire_Mutex(Mutex_ref *Acquired_Mutex , Task_ref *Task);
void MYRTOS_Release_Mutex(Mutex_ref *Released_Mutex, Task_ref *Task);



#endif /* SCHEDULER_H_ */
