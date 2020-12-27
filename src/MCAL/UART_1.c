#include "UART.h"

#include <stm32f4xx.h>
#include "GPIO.h"
#include "../Services_layers/Queue.h"
#include "../Services_layers/Speical_Timer.h"

Queue_t wifi_local_connection ;

void uart1_pin_conf(void)
{
	gpio_init(GPIOA);
	gpio_pin_conf_mode(GPIOA,9,ALT_FUNC);
	gpio_output_speed(GPIOA,9,HIGH_gp);
	gpio_altrenate_func(GPIOA,9,7);
	gpio_pull_up_down(GPIOA,9,PULLUP);
	gpio_pin_conf_mode(GPIOA,10,ALT_FUNC);
	gpio_pull_up_down(GPIOA,10,PULLUP);
	gpio_altrenate_func(GPIOA,10,7);
}


void UART_INIT_1(void)
{

	RCC->APB2ENR |=(1<<4);


	USART1->CR1= 0;
	USART1->CR1 |= (1<<13);
	USART1->CR1 |= (1<<2);
	USART1->CR1 |= (1<<3);
	USART1->CR1 |= (1<<5);
	USART1->BRR = 0xf|(585<<4);
	NVIC_EnableIRQ(USART1_IRQn);
	uart1_pin_conf();
}

void UART_SEND (USART_TypeDef *usart, uint8_t data)
{
	while(!((usart->SR) & (1<<6)));
	usart->DR = data;
	while(!((usart->SR) & (1<<6)));
}


void UART_Write_Array(USART_TypeDef *usart,unsigned char *arr  ,int size)
{
	for(int index = 0 ; index < size ; index ++)
	{
		UART_SEND(usart,arr[index]);
	}
}



char queue_wifi_local_data_read (void)
{
	unsigned char data= 0 ;
	Queue_Dequeue(&wifi_local_connection,&data);
	return data ;
}

int queue_wifi_local_get_size (void)
{
	return Queue_getSize(&wifi_local_connection);
}

void USART1_IRQHandler(void)
{
	char data = USART1->DR;

//	UART_SEND(USART2,data);
	Queue_Enqueue(&wifi_local_connection,data);
	SpecialTimer_Reset(SP_UART_WIFI_LOCAL_TIMEOUT);
}



