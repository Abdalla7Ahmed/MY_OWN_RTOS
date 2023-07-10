/*
|========================================================================|
|File             |:- MY_RTOS_FIFO.h					-:|
|Author           |:- Abdallah Ahmed Mohammed   		-:|
|Created on       |:- 3/7/2023     `					-:|
|========================================================================|
*/

#ifndef INC_MY_RTOS_FIFO_H_
#define INC_MY_RTOS_FIFO_H_


#include "stdio.h"
#include"stdint.h"
#include "Scheduler.h"
/*customer can select element type */

typedef struct{
	unsigned int counter;
	element_type* head;
	element_type* tail;
	element_type* base;
	unsigned int  length;
}FIFO_Buf_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL,

}Buffer_status;

/*APIs*/

Buffer_status FIFO_init (FIFO_Buf_t* fifo,element_type* buff , unsigned int length);
Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo,element_type item);
Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo,element_type* item);
Buffer_status FIFO_is_full (FIFO_Buf_t* fifo);
void FIFO_print (FIFO_Buf_t* fifo);



#endif /* INC_MY_RTOS_FIFO_H_ */
