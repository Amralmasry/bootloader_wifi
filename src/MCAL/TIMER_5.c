//
#include "stm32f4xx.h"
#include "TIMER_5.h"
void (*timer_5_ptr) (void);


void timer_5_init(void)
{
	RCC->APB1ENR |=RCC_APB1ENR_TIM5EN;
	TIM5->CR1 = (1<<2) ;
	TIM5->DIER |= (1<<0) ;
	TIM5->ARR = 16000*3 ;
	TIM5->CR1 |= (1<<0) ;
	NVIC_SetPriority(TIM5_IRQn,2);

	NVIC_EnableIRQ(TIM5_IRQn);


}

void timer_5_setcallback  (void (*ptr) (void))
{
	timer_5_ptr = ptr ;
}



void TIM5_IRQHandler(void)
{
	if (timer_5_ptr)
		timer_5_ptr();

	TIM5->SR = 0 ;
	NVIC_ClearPendingIRQ(TIM5_IRQn);

}
