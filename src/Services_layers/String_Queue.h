/*
 * String_Queue.h
 *
 *  Created on: 8 Feb 2019
 *      Author: root
 */

#ifndef SERVICES_LAYERS_STRING_QUEUE_H_
#define SERVICES_LAYERS_STRING_QUEUE_H_

#include "Queue.h"
#define STING_QUEUE_SIZE 	4
#define ELEMENT_SIZE 		BUFFER_SIZE

typedef struct string_queue string_queue_t;

struct string_queue
{
	char array[STING_QUEUE_SIZE][ELEMENT_SIZE];
	int element_size[STING_QUEUE_SIZE];
	int head;
	int tail;
	int size;
};

void String_Queue_enqueue(string_queue_t *me , char *ptr , int len);
void String_Queue_dequeue(string_queue_t *me , char *ptr , int *len);

char String_Queue_isfull(string_queue_t *me );
char String_Queue_isempty(string_queue_t *me );
int String_Queue_getsize(string_queue_t *me );


#endif /* SERVICES_LAYERS_STRING_QUEUE_H_ */
