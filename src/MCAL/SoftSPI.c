#include "stm32f4xx.h"
#include "../Services_layers/delay.h"
void SOFT_SPI_INIT (void)
{
	GPIOB -> MODER &=~((3<<26)|(3<<28)|(3<<30));
	GPIOB -> MODER|=(1<<28)|(1<<30);
	GPIOB -> OSPEEDR |=(0xf<<28);
	GPIOB -> ODR |= (1<<14);
}

unsigned char SOFT_SPI_READ (void)
{
	int counter = 0 ;
	unsigned char  data = 0 ;
	for (counter = 7 ; counter >= 0 ;counter--)
	{
		GPIOB -> ODR |=(1<<15);
		_delay_ms(2);
		if ((1<<13 ) & (GPIOB->IDR))
			data|= (1<<counter);
		GPIOB -> ODR &=~(1<<15);
		_delay_ms(2);
	}

return data ;
}
