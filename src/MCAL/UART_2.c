#include "UART.h"

#include <stm32f4xx.h>
#include "GPIO.h"

void uart2_pin_conf(void)
{
	GPIOA->AFR[0] &= ~0x0F00;
	GPIOA->AFR[0] |=  0x0700;   /* alt7 for USART2 */
	GPIOA->MODER  &= ~0x0030;
	GPIOA->MODER  |=  0x0020;   /* enable alternate function for PA2 */

}
	void UART_INIT_2(void )
	{

		RCC->AHB1ENR |=0xf;
		RCC->APB1ENR |=(1<<17);
		USART2->CR1= 0;
		USART2->BRR = 7|(24<<4);
		USART2->CR3 |= (1<<7);
		USART2->CR1 |= (1<<13);
		USART2->CR1 |= (1<<2);
		USART2->CR1 |= (1<<3);
		USART2->CR1 |= (1<<5);

		uart2_pin_conf();
	}

