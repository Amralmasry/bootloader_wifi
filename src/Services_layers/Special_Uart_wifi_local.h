/*
 * Special_Uart.h
 *
 *  Created on: 9 Feb 2019
 *      Author: root
 */

#ifndef SERVICES_LAYERS_SPECIAL_UART_H_
#define SERVICES_LAYERS_SPECIAL_UART_H_

#define UART_TIMEOUT_READ_LOCAL	30


void SpecialUart_Init_WIFI_LOCAL(void);
int SpecialUart_wifi_local_array(unsigned char *arr);
int SpecialUart_wifi_local_getsize(void);
int SpecialUart_wifi_local_array_DATA_ONLY(unsigned char *arr);
int SpecialUart_wifi_local_getsize_DATA_ONLY(void);

#endif /* SERVICES_LAYERS_SPECIAL_UART_H_ */
