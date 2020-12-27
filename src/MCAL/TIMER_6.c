
#include "stm32f4xx.h"
#include "TIMER_6.h"
#include "GPIO.h"
#include "../Services_layers/debug.h"
void (*timer_6_ptr) (void);
static volatile uint64_t millies = 0 ;

void timer_6_init(void)
{
	RCC->APB1ENR |= (1<<4)|(1<<5);
	TIM6->CR1 = 0 ;

	TIM6->CR1 |= (1<<2) ;
	TIM6->PSC = 3;
	TIM6->CR1 = (1<<2) ;
	TIM6->DIER |= (1<<0) ;
	TIM6->ARR = (3999*(90/16)) ;
	TIM6->CR1 |= (1<<0) ;
//	NVIC_SetPriority(TIM6_DAC_IRQn,2);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);


}


void timer_6_setcallback (void (*ptr) (void))
{

	timer_6_ptr = ptr ;

}


uint64_t millis (void)
{
	return millies ;
}
void TIM6_DAC_IRQHandler(void)
{
	millies++ ;
	if (timer_6_ptr)
	{
		timer_6_ptr();
	}

	TIM6->SR = 0 ;
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);


}
