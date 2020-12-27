

#include "String_Queue.h"
#include "string.h"
#include "stdio.h"

void String_Queue_enqueue(string_queue_t *me , char *ptr , int len)
{
	if(String_Queue_isfull(me) == 0)
	{
		memset(me->array[me->head] , 0 , ELEMENT_SIZE);
		memcpy(me->array[me->head] , ptr , len);
		me->element_size[me->head++] = len;
		me->head %= STING_QUEUE_SIZE;
		me->size++;
	}
}

void String_Queue_dequeue(string_queue_t *me , char *ptr , int *len)
{
	if(String_Queue_isempty(me) == 0)
	{
		memcpy(ptr , me->array[me->tail] , ELEMENT_SIZE);
		*len = me->element_size[me->tail++];
		me->tail %= STING_QUEUE_SIZE;
		me->size--;
	}
}

char String_Queue_isfull(string_queue_t *me )
{
	return (me->head == me->tail) && (me->size == STING_QUEUE_SIZE-1);
}
char String_Queue_isempty(string_queue_t *me )
{
	return (me->head == me->tail) && (me->size == 0);
}
int String_Queue_getsize(string_queue_t *me )
{
	return  me->size;
}


