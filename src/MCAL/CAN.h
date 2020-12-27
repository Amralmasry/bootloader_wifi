/*
 * CAN.h
 *
 *  Created on: Mar 9, 2020
 *      Author: amd
 */

#ifndef CAN_H_
#define CAN_H_
#define GPIO_AFRH_AFRH11                     ((uint32_t) 0x0000F000)
#define GPIO_AFRH_AFRH11_AF9                ((uint32_t) 0x00009000)
#define GPIO_AFRH_AFRH12                     ((uint32_t) 0x000F0000)
#define GPIO_AFRH_AFRH12_AF9                 ((uint32_t) 0x00090000)



#include <stm32f4xx.h>
#include "CAN.h"



void CAN1_Init(void);
void CAN1_Transmit(uint32_t data);
uint32_t CAN1_Receive(void);

#endif /* CAN_H_ */
