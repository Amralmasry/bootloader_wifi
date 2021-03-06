/*
 * Speical_Timer.h
 *
 *  Created on: 8 Feb 2019
 *      Author: root
 */

#ifndef SERVICESpecialTimerLAYERSpecialTimerSPEICAL_TIMER_H_
#define SERVICESpecialTimerLAYERSpecialTimerSPEICAL_TIMER_H_

#include "stdint.h"
typedef enum sp_timer
{
BOOT_TIMEOUT,
SP_UART_WIFI_LOCAL_TIMEOUT,
SP_UART_WIFI_MQTT_TIMEOUT,
ATCOMMANDER_TIMEOUT,
LOCAL_ATCOMMANDER_TIMEOUT,
 WIFI_ATCOMMANDER_TIMEOUT,
	TIMER0_COUNTER_NUMBER
}SPTIMER_T;


void SpecialTimer_Init();
void SpecialTimer_Reset(SPTIMER_T index);
void SpecialTimer_Start(SPTIMER_T index);
void SpecialTimer_Stop(SPTIMER_T index );
char SpecialTimer_Check(SPTIMER_T index , unsigned long compare);
unsigned char SpecialTimer_IsActive(SPTIMER_T index);

uint32_t SpecialTimer_VALUE(SPTIMER_T index );


#endif /* SERVICESpecialTimerLAYERSpecialTimerSPEICAL_TIMER_H_ */
