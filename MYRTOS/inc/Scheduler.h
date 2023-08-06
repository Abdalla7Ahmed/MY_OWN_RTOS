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
	enum
	{
		Waiting_Disable,
		Waiting_Enable
	}Waiting;
	uint32_t Event_Number;
}WaitingForEvent_t;
typedef struct
{
	// =================== User  Layer =================
	uint32_t Task_Size        		  ;
	uint8_t  Task_Priority    		  ;
	void (*P_Task_Entry)(void)		  ; // pointer to Task C function
	uint8_t  Task_Name[30]      	  ;
	uint8_t Task_AutoStart	  		  ;
	// ================================================
	uint32_t Task_S_PSP       		  ; // not entered by the user
	uint32_t Task_E_PSP       		  ; // not entered by the user
	uint32_t* Task_Current_PSP		  ; // not entered by the user
	Task_StateID Task_State   		  ; // not entered by the user
	Timing_Waiting T_Waiting  		  ;	// not entered by the user
	WaitingForEvent_t T_WaitForEvent  ; // not entered by the user
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

typedef enum
{
	MYRTOS_NO_ERROR,
	Ready_Queue_Init_Error,
	Task_Exceeded_StackSize_Error,
	MutexIsReceivedMaxNumberOfTasks
}MYRTOS_Error_Source;



/* Event Group */
typedef struct
{
	uint8_t Event_Group_Name[30]; // Set by the user
	// ============ not entered by the user===========
	uint8_t Number_Of_Waiting_Task;
	uint32_t Event_Group_Value;
}Event_Group_ref;

#define EV_0 					        0X0
#define EV_1 							0X1
#define EV_2 							0X2
#define EV_3                            0X4
#define EV_4                            0X8
#define EV_5                            0X10
#define EV_6                            0X20
#define EV_7                            0X40
#define EV_8                            0X80
#define EV_9                            0X100
#define EV_10                           0X200
#define EV_11                           0X400
#define EV_12                           0X800
#define EV_13                           0X1000
#define EV_14                           0X2000
#define EV_15                           0X4000
#define EV_16                           0X8000
#define EV_17                           0X10000
#define EV_18                           0X20000
#define EV_19                           0X40000
#define EV_20                           0X80000
#define EV_21                           0X100000
#define EV_22                           0X200000
#define EV_23                           0X400000
#define EV_24                           0X800000
#define EV_25                           0X1000000
#define EV_26                           0X2000000
#define EV_27                           0X4000000
#define EV_28                           0X8000000
#define EV_29                           0X10000000
#define EV_30                           0X20000000
#define EV_31                           0X40000000
#define EV_32                           0X80000000





MYRTOS_Error_Source MYRTOS_init(void);
MYRTOS_Error_Source MYRTOS_Creat_Task(Task_ref *Task_x);
void MYRTOS_Activate_Task(Task_ref *Task_x);
void MYRTOS_Terminate_Task(Task_ref *Task_x);
void MYRTOS_Start(void);
void MYRTOS_Task_Wait(uint32_t NoOfTicks,Task_ref *WaitTask);
MYRTOS_Error_Source MYRTOS_Acquire_Mutex(Mutex_ref *Acquired_Mutex , Task_ref *Task);
void MYRTOS_Release_Mutex(Mutex_ref *Released_Mutex, Task_ref *Task);
void MYRTOS_create_Event_Group(Event_Group_ref *Event_Group);
void MYRTOS_Set_Event(Event_Group_ref *Event_Group ,uint32_t Event_no);
void MYRTOS_Clear_Event(Event_Group_ref *Event_Group ,uint32_t Event_no);
void MYRTOS_Wait_Event(Event_Group_ref *Event_Group ,uint32_t Event_no,Task_ref *Task_x);
void MYRTOS_Delete_Task(Task_ref *Task_x);



#endif /* SCHEDULER_H_ */
