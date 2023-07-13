/*
|========================================================================|
|File             |:- Scheduler.c						-:|
|Author           |:- Abdallah Ahmed Mohammed   		-:|
|Created on       |:- 3/7/2023     `					-:|
|========================================================================|
 */
#include "Scheduler.h"
#include "MY_RTOS_FIFO.h"


struct
{
	Task_ref *OS_Tasks[100]   ;
	uint32_t _S_MSP 	      ;
	uint32_t _E_MSP	          ;
	uint32_t PSP_Task_Locator ;
	uint32_t NoOfActiveTask   ;
	Task_ref *Current_Task	  ;
	Task_ref *Next_Task		  ;
	uint8_t NoOfBlockedTask   ;
	enum
	{
		OSModeSuspend,
		OSModeRunning
	}OSModeID;

}OS_Control;


struct
{
	Task_ref *OS_Tasks[100] ;
	uint32_t NoOfCreatingTasks  ;
}Create_Task_t;


#define IDLE_Task_Size			300
FIFO_Buf_t Ready_Queue ;
Task_ref *Ready_Queue_FIFO[100] ;
Task_ref MYRTOS_IDLE_Task  ;


typedef enum
{
	SVC_Activate_Task,
	SVC_Terminate_Task,
	SVC_Task_Waiting_Time,
	SCV_Acquire_Mutex,
	SVC_Release_Mutex
}SVC_ID;

void MYRTOS_Creat_Main_Stack();
void MYRTOS_Idle_Task(void);
void MYRTOS_Creat_Task_Stack(Task_ref *Task_x);
void MYRTOS_OS_SVC_Set(SVC_ID ID);
void OS_SVC(uint32_t *StackFram);
void MYRTOS_Update_scheduler_Table(void);
void MYRTOS_OS_Bauble_Sort();
void MYRTOS_Decide_What_Next(void);
void MYRTOS_Update_Task_Waiting_Time();

__attribute ((naked)) PendSV_Handler(void)
{
	// ===================================
	// Save the context of the current task
	// =================================
	// 1- Get the current task PSP
	OS_GET_PSP(OS_Control.Current_Task->Task_Current_PSP);

	// 2- using this PSP to store R4 --> R11 in the stack of the current task
	/*PUSH R4 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R4 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R5 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R5 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R6 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R6 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R7 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R7 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R8 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R8 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R9 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile ("MOV %0 , R9 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R10 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R10 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));
	/*PUSH R11 in the stack of the current task*/
	OS_Control.Current_Task->Task_Current_PSP -- ;
	__asm volatile("MOV %0 , R11 " : "=r" (*(OS_Control.Current_Task->Task_Current_PSP)));



	// ===================================
	// Restore the context of the Next task
	// =================================
	if(OS_Control.Next_Task != NULL)
	{
		OS_Control.Current_Task = OS_Control.Next_Task;
		OS_Control.Next_Task = NULL;
	}


	// 1-Restore Registers (R11 to R4 )


	/*POP R11 from the stack of the next task*/
	__asm volatile("MOV R11 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R10 from the stack of the next task*/
	__asm volatile("MOV R10 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R9 from the stack of the next task*/
	__asm volatile("MOV R9 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R8 from the stack of the next task*/
	__asm volatile("MOV R8 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R7 from the stack of the next task*/
	__asm volatile("MOV R7 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R6 from the stack of the next task*/
	__asm volatile("MOV R6 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R5 from the stack of the next task*/
	__asm volatile("MOV R5 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/*POP R4 from the stack of the next task*/
	__asm volatile("MOV R4 , %0 ": : "r"(*(OS_Control.Current_Task->Task_Current_PSP)));
	OS_Control.Current_Task->Task_Current_PSP ++ ;
	/* now the PSP is point to R0 , the CPU Default unstacks (R0 , R1 , R2 ,R3,R12 ,LR , PC , xPSP ) */
	// 2-Update the PSP and exit
	OS_SET_PSP(OS_Control.Current_Task->Task_Current_PSP);
	__asm volatile("BX LR");
}

int systickLED;
void SysTick_Handler(void)
{
	systickLED ^=1;
	if(OS_Control.NoOfBlockedTask)
	{
		MYRTOS_Update_Task_Waiting_Time();
	}
	//decide what is the next task should be executed
	MYRTOS_Decide_What_Next();
	// trigger to the next task
	Trigger_OS_PendSV();

}

MYRTOS_Error_Source MYRTOS_init(void)
{
	MYRTOS_Error_Source error;

	error = MYRTOS_NO_ERROR;
	// Update OS mode (Suspend)
	OS_Control.OSModeID = OSModeSuspend;

	// Specify the Main Stack for OS
	MYRTOS_Creat_Main_Stack();
	//Create OS Ready Queue
	if(FIFO_init(&Ready_Queue,Ready_Queue_FIFO,100) != FIFO_NO_ERROR)
	{
		error += Ready_Queue_Init_Error;
	}
	// Configure Idle Task
	MYRTOS_IDLE_Task.Task_Priority = 255 ;
	MYRTOS_IDLE_Task.P_Task_Entry = MYRTOS_Idle_Task ;
	strcpy(MYRTOS_IDLE_Task.Task_Name , "IDLE_Task");
	MYRTOS_IDLE_Task.Task_Size = IDLE_Task_Size;
	MYRTOS_Creat_Task(&MYRTOS_IDLE_Task);

	return error;
}

void MYRTOS_Creat_Main_Stack()
{
	OS_Control._S_MSP = (uint32_t)&_estack ;
	OS_Control._E_MSP = (OS_Control._S_MSP - Main_Stack_Size);
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP - 0x8 ) ;
}



int IdletaskLED;

void MYRTOS_Idle_Task(void)
{
	while (1)
	{
		IdletaskLED ^=1;
		__asm("WFE");
		// WFE --> Wait for event --> the processor will be in sleep mode until any event happened
		// (exception interrupt or physical interrupt)
		// WFI --> Wait for interrupt --> Wait until physical interrupt only

		// if we use __asm("NOP") the utilization will be very high when no tasks execute except idle
		// because this instruction will executed in one cycle
		// the solution is used WFE or WFI (WFE is the best one )
	}

}



MYRTOS_Error_Source MYRTOS_Creat_Task(Task_ref *Task_x)
{
	MYRTOS_Error_Source error;

	error = MYRTOS_NO_ERROR;
	// Check Task size exceed the PSP stack
	Task_x->Task_S_PSP = OS_Control.PSP_Task_Locator ;
	Task_x->Task_E_PSP = (Task_x->Task_S_PSP - Task_x->Task_Size );
	//Task_x->Task_Current_PSP = OS_Control->PSP_Task_Locator ;
	if(Task_x->Task_E_PSP <  (uint32_t)&_eheap)
	{
		return Task_Exceeded_StackSize_Error;
	}
	else
	{
		/* Misra */
	}

	// Aligned 8 byte between PSP_Task_x and PSP_Task_y
	OS_Control.PSP_Task_Locator = Task_x->Task_E_PSP - 8 ;

	// Initialize PSP Task Stack
	MYRTOS_Creat_Task_Stack(Task_x);

	// update scheduler table
	Create_Task_t.OS_Tasks[Create_Task_t.NoOfCreatingTasks] = Task_x;
	Create_Task_t.NoOfCreatingTasks ++ ;

	// Update task status (Suspend)
	Task_x->Task_State = Task_Suspend;
	return error;

}


void MYRTOS_Creat_Task_Stack(Task_ref *Task_x)
{
	//Task_Frame Task ;


	Task_x->Task_Current_PSP = Task_x->Task_S_PSP ;

	Task_x->Task_Current_PSP -- ;
	*(Task_x->Task_Current_PSP) = 0x01000000;  // xPSR --> T should = 1 to avoid Bus Fault

	Task_x->Task_Current_PSP -- ;
	*(Task_x->Task_Current_PSP) = (uint32_t)Task_x->P_Task_Entry;  // PC

	Task_x->Task_Current_PSP -- ;
	*(Task_x->Task_Current_PSP) = 0xFFFFFFFD; // LR(Execution Return ) Thread - PSP


	for(int i=0 ; i<13 ; i++)
	{
		Task_x->Task_Current_PSP -- ;
		*(Task_x->Task_Current_PSP) = 0x0;  // R0 --> R12
	}
}



void MYRTOS_Activate_Task(Task_ref *Task_x)
{
	Task_x->Task_State = Task_Waiting;
	MYRTOS_OS_SVC_Set(SVC_Activate_Task);

}
void MYRTOS_Terminate_Task(Task_ref *Task_x)
{
	Task_x->Task_State = Task_Suspend;
	MYRTOS_OS_SVC_Set(SVC_Terminate_Task);
}

// Thread Mode
void MYRTOS_OS_SVC_Set(SVC_ID ID)
{
	switch (ID)
	{
	case SVC_Activate_Task:      __asm("SVC #0x00");           break;
	case SVC_Terminate_Task:     __asm("SVC #0x01");           break ;
	case SVC_Task_Waiting_Time:  __asm("SVC #0x02");           break ;
	case SCV_Acquire_Mutex :     __asm("SVC #0x03");           break ;
	case SVC_Release_Mutex:      __asm("SVC #0x04");           break ;
	}
}



// =============================================================================
// Handler mode (Privileged    ,  SP is shadow of  MSP )
void OS_SVC(uint32_t *StackFram)
{
	unsigned char SVC_Number;
	SVC_Number = *((unsigned char *)(((unsigned char *)StackFram[6])-2));
	switch (SVC_Number)
	{
	case SVC_Activate_Task		 :
	case SVC_Terminate_Task		 :
	case SCV_Acquire_Mutex       :
	case SVC_Release_Mutex       :
		// Update scheduler table & Ready Queue
		MYRTOS_Update_scheduler_Table();
		// Check OS is in Running state
		if(OS_Control.OSModeID == OSModeRunning)
		{
			if(strcmp(OS_Control.Current_Task->Task_Name , "IDLE_Task") != 0)
			{
				// the current task is not the idle task
				// Decide which task should be next
				MYRTOS_Decide_What_Next();
				// Trigger OS_PendSV (Switch context / switch Restore)
				Trigger_OS_PendSV();
			}
		}
		break;
	case SVC_Task_Waiting_Time   :
		MYRTOS_Update_scheduler_Table();
		break;
	}

}



void MYRTOS_Update_scheduler_Table(void)
{
	Task_ref *temp = NULL;
	int i=0;
	Task_ref *Ptask = NULL ;
	Task_ref *PnextTask = NULL;
	// 1- Bauble sort to scheduler table based on priority
	MYRTOS_OS_Bauble_Sort();
	// 2- free Ready Queue
	while(FIFO_EMPTY != FIFO_dequeue(&Ready_Queue,&temp));
	// 3- Update Ready Queue with the new task
	while(i < OS_Control.NoOfActiveTask)
	{
		Task_ref *Ptask = OS_Control.OS_Tasks[i] ;
		Task_ref *PnextTask = OS_Control.OS_Tasks[i+1] ;
		if(OS_Control.NoOfActiveTask ==1)
		{
			FIFO_enqueue(&Ready_Queue, Ptask);
			Ptask->Task_State = Task_Ready;
			break;
		}
		if((OS_Control.NoOfActiveTask -1) == i)
		{
			FIFO_enqueue(&Ready_Queue, Ptask);
			// update PTask state
			Ptask->Task_State = Task_Ready;
			break; 
		}
		if(Ptask->Task_Priority > PnextTask->Task_Priority)
		{
			// not allowed happened because we reordered it by bauble sort
			break;
		}
		if(Ptask->Task_Priority < PnextTask->Task_Priority)
		{
			FIFO_enqueue(&Ready_Queue, Ptask);
			// update PTask state
			Ptask->Task_State = Task_Ready;
			break;
		}
		else if(Ptask->Task_Priority == PnextTask->Task_Priority)
		{
			FIFO_enqueue(&Ready_Queue, Ptask);
			// update PTask state
			Ptask->Task_State = Task_Ready;
		}
		i++ ;
	}
}



void MYRTOS_OS_Bauble_Sort(void)
{
	int i=0, j = 0 ,n = Create_Task_t.NoOfCreatingTasks;
	Task_ref *temp	;
	// make sure that OS_Control contain 0 task
	while(i<OS_Control.NoOfActiveTask)
	{
		OS_Control.OS_Tasks[i] = NULL;
		i++;
	}


	for(i=0;i<n;i++)
	{
		if(Create_Task_t.OS_Tasks[i]->Task_State !=Task_Suspend)
		{
			OS_Control.OS_Tasks[j]= Create_Task_t.OS_Tasks[i];
			j++;
		}
		else
		{
			
		}
	}

	OS_Control.NoOfActiveTask  = j;

	n = OS_Control.NoOfActiveTask;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++)
		{
			if(OS_Control.OS_Tasks[j]->Task_Priority > OS_Control.OS_Tasks[j+1]->Task_Priority)
			{
				temp  = OS_Control.OS_Tasks[j] ;
				OS_Control.OS_Tasks[j]   =  OS_Control.OS_Tasks[j+1] ;
				OS_Control.OS_Tasks[j+1]= temp ;
			}
		}
	}

}


void MYRTOS_Decide_What_Next(void)
{

	// if ready QUEUE is empty & current task is not suspend
	// there is only one task in activated , this task should execute until it terminate
	if((Ready_Queue.counter == 0 )&&(OS_Control.Current_Task->Task_State != Task_Suspend) )
	{
		OS_Control.Current_Task->Task_State = Task_Running ;
		// add the current task again
		FIFO_enqueue(&Ready_Queue,OS_Control.Current_Task);
		OS_Control.Next_Task = OS_Control.Current_Task;
	}
	else
	{
		// there is more than one task should execute (round robin)
		FIFO_dequeue(&Ready_Queue, &OS_Control.Next_Task);
		OS_Control.Next_Task->Task_State = Task_Running;
		// Update ready Queue
		if((OS_Control.Current_Task->Task_Priority == OS_Control.Next_Task->Task_Priority)
				&& (OS_Control.Current_Task-> Task_State != Task_Suspend))
		{
			FIFO_enqueue(&Ready_Queue,OS_Control.Current_Task);
			OS_Control.Current_Task->Task_State = Task_Ready;
		}
	}

}


void MYRTOS_Start(void)
{
	OS_Control.OSModeID = OSModeRunning ;
	// Set default task (Idle task)
	OS_Control.Current_Task = &MYRTOS_IDLE_Task;
	// Activate Idle task
	MYRTOS_Activate_Task(&MYRTOS_IDLE_Task);
	// start ticker
	MYRTOS_Start_Ticker();
	// set PSP to PSP of idle task
	OS_SET_PSP(OS_Control.Current_Task->Task_Current_PSP);
	// switch from MSP to PSP
	OS_Switch_SP_to_PSP;
	// switch to UnPrivileged access level
	Switch_To_UnPrivileged_Access_Level;
	// update idle task to running state
	//OS_Control.Current_Task->Task_State = Task_Running;
	OS_Control.Current_Task->P_Task_Entry();
}


void MYRTOS_Task_Wait(uint32_t NoOfTicks,Task_ref *WaitTask)
{
	OS_Control.NoOfBlockedTask ++;
	WaitTask->T_Waiting.Blocking = Blocking_Enable;
	WaitTask->T_Waiting.Ticks_Count = NoOfTicks;

	// update state
	WaitTask->Task_State = Task_Suspend;
	MYRTOS_OS_SVC_Set(SVC_Terminate_Task);

}


void MYRTOS_Update_Task_Waiting_Time()
{
	uint32_t i=0;
	for(;i<Create_Task_t.NoOfCreatingTasks;i++)
	{
		if(Create_Task_t.OS_Tasks[i]->Task_State == Task_Suspend)
		{
			if(Create_Task_t.OS_Tasks[i]->T_Waiting.Blocking == Blocking_Enable)
			{
				Create_Task_t.OS_Tasks[i]->T_Waiting.Ticks_Count --;
				if(Create_Task_t.OS_Tasks[i]->T_Waiting.Ticks_Count == 0 )
				{
					OS_Control.NoOfBlockedTask --;
					Create_Task_t.OS_Tasks[i]->T_Waiting.Blocking = Blocking_Disable;
					Create_Task_t.OS_Tasks[i]->Task_State = Task_Waiting;
					MYRTOS_OS_SVC_Set(SVC_Task_Waiting_Time);
				}
				else
				{

				}

			}
			else
			{

			}
		}
		else {

		}

	}
}




MYRTOS_Error_Source MYRTOS_Acquire_Mutex(Mutex_ref *Acquired_Mutex , Task_ref *Task)
{
	if(Acquired_Mutex->Current_Task == NULL) // Mutex is valid
	{
		Acquired_Mutex->Current_Task = Task;
	}
	else
	{
		if(Acquired_Mutex->Next_Task == NULL) // not pending by any other task
		{
			Acquired_Mutex->Next_Task = Task ;
			Acquired_Mutex->Next_Task->Task_State = Task_Suspend;
			if(Acquired_Mutex->Priority_Inheritance.Priority_Inheritance_State== PI_Enable)
			{
				Acquired_Mutex->Priority_Inheritance.Saved_Pririty = Acquired_Mutex->Current_Task->Task_Priority;
				Acquired_Mutex->Current_Task->Task_Priority = Acquired_Mutex->Next_Task->Task_Priority;
			}
			else
			{

			}
			MYRTOS_OS_SVC_Set(SCV_Acquire_Mutex);
		}
		else
		{
			return MutexIsReceivedMaxNumberOfTasks;
		}
	}

	return MYRTOS_NO_ERROR;

}
void MYRTOS_Release_Mutex(Mutex_ref *Released_Mutex, Task_ref *Task)
{
	if(Released_Mutex ->Current_Task != NULL)
	{
		if(Released_Mutex->Current_Task == Task)
		{
			if(Released_Mutex->Priority_Inheritance.Priority_Inheritance_State== PI_Enable)
			{
				Released_Mutex->Current_Task->Task_Priority = Released_Mutex->Priority_Inheritance.Saved_Pririty;
				Released_Mutex->Priority_Inheritance.Saved_Pririty = Released_Mutex->Next_Task->Task_Priority;
			}
			if(Released_Mutex ->Next_Task == NULL)
			{
				// there is no task Acquired Mutex
				Released_Mutex->Current_Task = NULL ;
			}
			else
			{
				Released_Mutex->Current_Task = Released_Mutex->Next_Task;
				Released_Mutex->Next_Task = NULL ;
				Released_Mutex->Current_Task->Task_State = Task_Waiting;
				MYRTOS_OS_SVC_Set(SVC_Release_Mutex);
			}
		}
		else
		{
			// Mutex can only released by the current task
		}
	}
	else
	{
		// the mutex is already Released

	}

}


