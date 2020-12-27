
#include "Queue.h"


char Queue_isEmpty(Queue_t *me)
{
	return (me->head == me->tail) && (me->conut == 0);
}

char Queue_isFull(Queue_t *me)
{
	return (me->head == me->tail) && (me->conut >= BUFFER_SIZE-1);
}

int Queue_getSize(Queue_t *me)
{
	return me->conut;
}

void Queue_Enqueue(Queue_t *me , unsigned char incomingdata)
{
	if(Queue_isFull(me) == 0)
	{
		me->Buffer[me->head++] = incomingdata;
		me->conut++;

		me->head %= BUFFER_SIZE;
	}

}

void Queue_Dequeue(Queue_t *me , unsigned char *Data)
{
	if(Queue_isEmpty(me) == 0)
	{
		*Data = me->Buffer[me->tail++];
		me->conut--;
		me->tail %= BUFFER_SIZE;
	}
}
































char Queue_isEmpty_16(Queue_16_t *me)
{
	return (me->head == me->tail) && (me->conut == 0);
}

char Queue_isFull_16(Queue_16_t *me)
{
	return (me->head == me->tail) && (me->conut >= BUFFER_SIZE-1);
}

int Queue_getSize_16(Queue_16_t *me)
{
	return me->conut;
}

void Queue_Enqueue_16(Queue_16_t *me , uint16_t incomingdata)
{
	if(Queue_isFull_16(me) == 0)
	{
		me->Buffer[me->head++] = incomingdata;
		me->conut++;
		me->head %= BUFFER_SIZE_16;
	}
}

void Queue_Dequeue_16(Queue_16_t *me , uint16_t *Data)
{
	if(Queue_isEmpty_16(me) == 0)
	{
		*Data = me->Buffer[me->tail++];
		me->conut--;
		me->tail %= BUFFER_SIZE_16;
	}
}
