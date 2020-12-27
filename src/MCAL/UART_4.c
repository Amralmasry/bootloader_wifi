#include "UART.h"

#include <stm32f4xx.h>

#include "GPIO.h"
#include "../Services_layers/Queue.h"
#include "../Services_layers/Speical_Timer.h"
//#include "Services_layers/debug.h"

//Queue_t uart_gsm ;



void uart4_pin_conf(void)
{

	RCC->AHB1ENR |= 1;          /* Enable GPIOA clock */
	RCC->APB1ENR |= 0x80000;    /* Enable UART4 clock */

	/* Configure PA0, PA1 for UART4 TX, RX */
	GPIOA->AFR[0] &= ~0x00FF;
	GPIOA->AFR[0] |=  0x0088;   /* alt8 for UART4 */
	GPIOA->MODER  &= ~0x000F;
	GPIOA->MODER  |=  0x000A;   /* enable alternate function for PA0, PA1 */
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0|GPIO_PUPDR_PUPDR1_0;
}
void UART_INIT_4(void )
{
	RCC->APB1ENR |=RCC_APB1ENR_UART4EN;
	UART4->CR1= 0;
	UART4->CR1 |= (1<<13);
	UART4->CR1 |= (1<<2);
	UART4->CR1 |= (1<<3);
	UART4->CR1 |= (1<<5);
	UART4->BRR = 0x10|(0x124<<4);
	NVIC_EnableIRQ(UART4_IRQn);
//	NVIC_SetPriority(UART4_IRQn, 0 );
	uart4_pin_conf();
}



//void UART4_IRQHandler (void)
//{
//	char data = UART4->DR ;
//#if DEBUGGING
//	UART_SEND(USART2,data);
//	//UART_Write_Array(USART2,"amr\n",4);
//#endif
//	Queue_Enqueue(&uart_gsm,data);
//	NVIC_ClearPendingIRQ(UART4_IRQn);
//	SpecialTimer_Reset(UART_1);
//}
//
//
//int Uart_Queue_GetSize(void)
//{
//	return Queue_getSize(&uart_gsm);
//}
//
//
//
//
//char  uart_read_queue (void)
//{
//	unsigned char data = 0;
//	Queue_Dequeue(&uart_gsm,&data);
//	return data ;
//}



