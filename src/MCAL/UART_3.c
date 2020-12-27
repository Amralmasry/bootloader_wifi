#include "UART.h"

#include <stm32f4xx.h>

#include "GPIO.h"
#include "../Services_layers/Queue.h"
#include "../Services_layers/Speical_Timer.h"

Queue_t wifi_MQTT_connection ;



void uart3_pin_conf(void)
{

	gpio_init(GPIOC);
	gpio_pin_conf_mode(GPIOC,10,ALT_FUNC);
	gpio_output_speed(GPIOC,10,HIGH_gp);
	gpio_altrenate_func(GPIOC,10,7);
	gpio_pull_up_down(GPIOC,10,PULLUP);
	gpio_pin_conf_mode(GPIOC,11,ALT_FUNC);
	gpio_pull_up_down(GPIOC,11,PULLUP);
	gpio_altrenate_func(GPIOC,11,7);

}

void UART_INIT_3(void )
{


	RCC->APB1ENR |=RCC_APB1ENR_USART3EN;
	USART3->CR1= 0;
	USART3->CR1 |= (1<<13);
	USART3->CR1 |= (1<<2);
	USART3->CR1 |= (1<<3);
	USART3->CR1 |= (1<<5);
	USART3->BRR = 0x10|(0x124<<4);

	NVIC_EnableIRQ(USART3_IRQn);
	uart3_pin_conf();
}
char queue_wifi_MQTT_data_read (void)
{
	unsigned char data= 0 ;
	Queue_Dequeue(&wifi_MQTT_connection,&data);
	return data ;
}

int queue_wifi_MQTT_get_size (void)
{
	return Queue_getSize(&wifi_MQTT_connection);
}

void USART3_IRQHandler(void)
{
	char data = USART3->DR;
//	UART_SEND(USART2,'a');

//	UART_SEND(USART2,data);
	Queue_Enqueue(&wifi_MQTT_connection,data);
	SpecialTimer_Reset(SP_UART_WIFI_MQTT_TIMEOUT);
}





