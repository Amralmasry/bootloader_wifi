/*
 * Queue.h
 *
 *  Created on: 1 Feb 2019
 *      Author: root
 */

#ifndef SERVICES_LAYERS_QUEUE_H_
#define SERVICES_LAYERS_QUEUE_H_

#define BUFFER_SIZE 1000
#define BUFFER_SIZE_16 40
#include <stdint.h>
typedef struct Queue Queue_t;
struct Queue
{
	unsigned char Buffer[BUFFER_SIZE];
	int head;
	int tail;
	int conut;
};
typedef struct qQueue Queue_16_t;
struct qQueue
{
	uint16_t Buffer[BUFFER_SIZE_16];
	int head;
	int tail;
	int conut;
};
void Queue_Enqueue(Queue_t *me , unsigned char incomingdata);
void Queue_Dequeue(Queue_t *me , unsigned char *Data);
int Queue_getSize(Queue_t *me);
char Queue_isFull(Queue_t *me);
char Queue_isEmpty(Queue_t *me);

char Queue_isEmpty_16(Queue_16_t *me);
char Queue_isFull_16(Queue_16_t *me);
int Queue_getSize_16(Queue_16_t *me);
void Queue_Enqueue_16(Queue_16_t *me , uint16_t incomingdata);
void Queue_Dequeue_16(Queue_16_t *me , uint16_t *Data);

#endif /* SERVICES_LAYERS_QUEUE_H_ */
