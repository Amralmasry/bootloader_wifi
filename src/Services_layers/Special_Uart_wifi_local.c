
#include "Special_Uart_wifi_local.h"
#include "Speical_Timer.h"
#include "../MCAL/UART.h"
#include "Services_layers.h"
#include "String_Queue.h"
#include "../MCAL/TIMER_5.h"
#include "delay.h"
#include <string.h>

string_queue_t Uart_String_wifi_local ;
string_queue_t Uart_String_wifi_local_DATA_ONLY ;
char data[ELEMENT_SIZE];

void SpecialUart_Update_wifi_local(void)
{
	int counter = 0;
	int i = 0;
	if(queue_wifi_local_get_size())
	{
		SpecialTimer_Start(SP_UART_WIFI_LOCAL_TIMEOUT);
	}
	if(SpecialTimer_Check(SP_UART_WIFI_LOCAL_TIMEOUT , UART_TIMEOUT_READ_LOCAL/2))
	{
		while(queue_wifi_local_get_size())
		{
			for(counter = 0 ;queue_wifi_local_get_size()  && counter < ELEMENT_SIZE; counter ++)
			{
				data[counter] = queue_wifi_local_data_read();
				if (!memcmp(&data[counter-1], "\r\n",2) && memcmp(data,"+IPD",4) )
				{
					break ;
				}
			}

			if (!memcmp(data,"+IPD",4))
			{
				for ( i = 0 ; i < counter ;i++)
					if (data[i] == ':')
						break;
 				String_Queue_enqueue(&Uart_String_wifi_local_DATA_ONLY, &data[i+1] ,counter-(i+1));
			}
			else
				String_Queue_enqueue(&Uart_String_wifi_local, data , counter);
		}
		SpecialTimer_Reset(SP_UART_WIFI_LOCAL_TIMEOUT);
		SpecialTimer_Stop(SP_UART_WIFI_LOCAL_TIMEOUT);
	}
}


void SpecialUart_Init_WIFI_LOCAL()
{
	timer_5_init();
	timer_5_setcallback(SpecialUart_Update_wifi_local);
}





int SpecialUart_wifi_local_array(unsigned char *arr)
{
	int size = 0 ;
	if (String_Queue_getsize(&Uart_String_wifi_local))
	{
		String_Queue_dequeue(&Uart_String_wifi_local,(char *)arr , &size);
	}
	return size;
}

int SpecialUart_wifi_local_getsize(void)
{
	return String_Queue_getsize(&Uart_String_wifi_local);
}


int SpecialUart_wifi_local_array_DATA_ONLY(unsigned char *arr)
{
	int size = 0 ;
	if (String_Queue_getsize(&Uart_String_wifi_local_DATA_ONLY))
	{
		String_Queue_dequeue(&Uart_String_wifi_local_DATA_ONLY,(char *)arr , &size);
	}
	return size;
}

int SpecialUart_wifi_local_getsize_DATA_ONLY(void)
{
	return String_Queue_getsize(&Uart_String_wifi_local_DATA_ONLY);
}











