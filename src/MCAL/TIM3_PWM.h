/*
 * TIM2_PWM.h
 *
 *  Created on: Feb 2, 2020
 *      Author: amd
 */

#ifndef MCAL_TIM3_PWM_H_
#define MCAL_TIM3_PWM_H_

void TIMER_3_PWM_INIT (void);
void TIMER_3_CH1_ENABLE (void);
void TIMER_3_CH2_ENABLE (void);
void TIMER_3_CH3_ENABLE (void);
void TIMER_3_CH4_ENABLE (void);
void TIMER_3_CH1_DISABLE (void);
void TIMER_3_CH2_DISABLE (void);
void TIMER_3_CH3_DISABLE (void);
void TIMER_3_CH4_DISABLE (void);
void TIMER_3_CH1_SET_PWM (unsigned int PWM );
void TIMER_3_CH2_SET_PWM (unsigned int PWM );
void TIMER_3_CH3_SET_PWM (unsigned int PWM );
void TIMER_3_CH4_SET_PWM (unsigned int PWM );

#endif /* MCAL_TIM3_PWM_H_ */
