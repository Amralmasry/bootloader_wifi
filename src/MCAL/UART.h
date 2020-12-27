#ifndef  uart
#define  uart

#include <stm32f4xx.h>

void UART_SEND (USART_TypeDef *usart, uint8_t data);

void UART_INIT_2(void);
char queue_wifi_local_data_read (void);
int queue_wifi_local_get_size (void);

void UART_INIT_1(void);

void UART_INIT_3(void);
char queue_wifi_MQTT_data_read (void);
int queue_wifi_MQTT_get_size (void);


void UART_Write_Array(USART_TypeDef *usart,unsigned char *arr  ,int size);

#endif
