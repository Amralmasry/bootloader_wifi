

#include "../MCAL/UART.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx.h"

void debug_init(void)
{
	UART_INIT_2();
 }

void debug_write(char *massage)
{

	UART_Write_Array(USART2,(uint8_t *)massage,strlen(massage));

}
void debug_massege(unsigned char *massage,int size)
{
 	UART_Write_Array(USART2,massage,size);

}
void debug_massege_INT(char *massage,int size)
{
	UART_Write_Array(USART2,(uint8_t *)massage,size);

}

void debug_values(int size ,int value,...)
{

	char data[30];
	int counter = 1 ;
	for (; counter <= size ;counter++)
	{
		int sizee= 	 sprintf(data,"value %d = %d \n",counter,*((&value)+counter-1));
		UART_Write_Array(USART2,(uint8_t *)data,sizee);
	}
 }
