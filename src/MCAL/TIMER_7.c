
#include "stm32f4xx.h"
#include "TIMER_7.h"
void (*timer_7_ptr) (void);
void (*timer_77_ptr) (void);
void (*timer_777_ptr) (void);


void timer_7_init(void)
{
	TIM7->CR1 = (1<<2) ;
	TIM7->DIER |= (1<<0) ;
	TIM7->PSC = 4;
	TIM7->ARR = (3999*(90/16))*2 ;
	TIM7->CR1 |= (1<<0) ;
	NVIC_SetPriority(TIM7_IRQn,3);
	NVIC_EnableIRQ(TIM7_IRQn);

}

void timer_7_setcallback  (void (*ptr) (void))
{
	timer_7_ptr = ptr ;
}
void timer_77_setcallback (void (*ptr) (void))
{
	timer_77_ptr = ptr ;
}
void timer_777_setcallback (void (*ptr) (void))
{
	timer_777_ptr = ptr ;
}



void TIM7_IRQHandler(void)
{
	if (timer_7_ptr)
		timer_7_ptr();
	if (timer_77_ptr)
		timer_77_ptr();
	if (timer_777_ptr)
		timer_777_ptr();

	TIM7->SR = 0 ;
	NVIC_ClearPendingIRQ(TIM7_IRQn);

}
