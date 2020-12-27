

#include <stm32f4xx.h>
#include "GPIO.h"
void TIMER_3_PWM_INIT (void)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN |  RCC_APB1ENR_TIM3EN |  RCC_APB1ENR_TIM4EN |  RCC_APB1ENR_TIM5EN;
	gpio_init(GPIOA);
	gpio_pin_conf_mode(GPIOA,6,ALT_FUNC);
	gpio_pin_conf_mode(GPIOA,7,ALT_FUNC);
	gpio_init(GPIOB);
	gpio_pin_conf_mode(GPIOB,0,ALT_FUNC);
	gpio_pin_conf_mode(GPIOB,1,ALT_FUNC);

	gpio_output_speed(GPIOA,6,HIGH_gp);
	gpio_output_speed(GPIOA,7,HIGH_gp);
	gpio_output_speed(GPIOB,0,HIGH_gp);
	gpio_output_speed(GPIOB,1,HIGH_gp);

	gpio_altrenate_func(GPIOA,6,2);
	gpio_altrenate_func(GPIOA,7,2);
	gpio_altrenate_func(GPIOB,0,2);
	gpio_altrenate_func(GPIOB,1,2);


	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM3 -> PSC = 1;
	TIM3 -> CCMR1 =  TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC1M_2;
	TIM3 -> CCMR2 =  TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
	TIM3 -> CCER =   TIM_CCER_CC1E |TIM_CCER_CC2E |TIM_CCER_CC3E |TIM_CCER_CC4E ;
	TIM3 -> ARR = 36000 ;
	TIM3 -> CCR1 = 0;
	TIM3 -> CCR2 = 0;
	TIM3 -> CCR3 = 0;
	TIM3 -> CCR4 = 0;
	TIM3 -> EGR = 1<<0;
	TIM3 -> CR1 = TIM_CR1_ARPE | TIM_CR1_CEN ;

}

void TIMER_3_CH1_ENABLE (void)
{
	TIM3 -> CCER |=   TIM_CCER_CC1E  ;

}
void TIMER_3_CH2_ENABLE (void)
{
	TIM3 -> CCER |=   TIM_CCER_CC2E  ;
}
void TIMER_3_CH3_ENABLE (void)
{
	TIM3 -> CCER |=   TIM_CCER_CC3E  ;
}
void TIMER_3_CH4_ENABLE (void)
{
	TIM3 -> CCER |=   TIM_CCER_CC4E  ;
}
void TIMER_3_CH1_DISABLE (void)
{
	TIM3 -> CCER &=~   TIM_CCER_CC1E  ;
}
void TIMER_3_CH2_DISABLE (void)
{
	TIM3 -> CCER &=~   TIM_CCER_CC2E  ;
}
void TIMER_3_CH3_DISABLE (void)
{
	TIM3 -> CCER &=~   TIM_CCER_CC3E  ;
}
void TIMER_3_CH4_DISABLE (void)
{
	TIM3 -> CCER &=~   TIM_CCER_CC4E  ;
}
void TIMER_3_CH1_SET_PWM (unsigned int PWM )
{
	TIM3 -> CCR1    = PWM;
}
void TIMER_3_CH2_SET_PWM (unsigned int PWM )
{
	TIM3 -> CCR2    = PWM;
}
void TIMER_3_CH3_SET_PWM (unsigned int PWM )
{
	TIM3 -> CCR3    = PWM;
}
void TIMER_3_CH4_SET_PWM (unsigned int PWM )
{
	TIM3 -> CCR4    = PWM;
}
