

#include <stm32f4xx.h>


void sys_init (void)
{
	RCC->CFGR &=~((1<<4)|(1<<5)|(1<<6)|(1<<7));
	RCC->CFGR &=~((1<<10)|(1<<11)|(1<<12)|(1<<13));
	RCC->CFGR &=~((1<<14)|(1<<15));
	RCC->CFGR |= (1<<15)|(1<<10)|(1<<12);
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;

}
