
#include "../MCAL/UART.h"
#include "../Services_layers/Special_Uart_wifi_local.h"
#include "../Services_layers/Speical_Timer.h"
#include "../Services_layers/delay.h"

#include "../Services_layers/utility.h"

#include "stdio.h"
#include "string.h"
#include "WIFI_LOCAL.h"

#include "../Services_layers/debug.h"
#include "../Services_layers/Services_layers.h"

void WIFI_LOCAL_INIT (void)
{

	UART_INIT_1();

	SpecialTimer_Init();
	SpecialUart_Init_WIFI_LOCAL();
//	WIFI_LOCAL_SEND((unsigned char *)"ATE0\r\n",strlen("ATE0\r\n"));
//	_delay_ms(100);
// 	WIFI_LOCAL_SEND((unsigned char *)"AT+CWMODE_DEF=1\r\n",strlen("AT+CWMODE_DEF=1\r\n"));
// 	_delay_ms(100);
//	WIFI_LOCAL_SEND((unsigned char *)STATIC_IP  , strlen(STATIC_IP));
//	_delay_ms(100);
//	WIFI_LOCAL_SEND((unsigned char *)"AT+CWAUTOCON=0\r\n"  , strlen("AT+CWAUTOCON=0\r\n"));
//	_delay_ms(100);
//	WIFI_LOCAL_SEND((unsigned char *)"AT+RST\r\n"  , strlen("AT+RST\r\n"));
//	_delay_ms(3000);


}

void WIFI_START_SERVER(void)
{
	WIFI_LOCAL_SEND((unsigned char *)"AT+CIPMUX=1\r\n"  , strlen("AT+CIPMUX=1\r\n"));
	_delay_ms(100);
	WIFI_LOCAL_SEND((unsigned char *)"AT+CIPSERVER=1,80\r\n"  , strlen("AT+CIPSERVER=1,80\r\n"));
	_delay_ms(100);
	WIFI_LOCAL_SEND((unsigned char *)"AT+CIPSTO=0\r\n"  , strlen("AT+CIPSERVER=0\r\n"));
	_delay_ms(100);

}

uint8_t WIFI_LOCAL_JAP (void)
{

	WIFI_LOCAL_FLUSH();
	unsigned  char arr[80] ;
	memset(arr , 0 , sizeof(arr));
	int size = sprintf((char*)arr , "AT+CWJAP=\"%s\",\"%s\"\r\n","amr","amr00747");

 	WIFI_LOCAL_SEND(arr , size);
 return	WIFI_WAIT_RESPONSE(2,"WIFI GOT IP","OK");

}
//void WIFI_LOCAL_TCP_START (void)
//{
//	unsigned char arr[80];
//	int size ;
//	memset(arr , 0 , sizeof(arr));
////	size = sprintf((char*)arr , "AT+CIPSTART=\"TCP\",\"%s\",%d,7200\r\n" , "192.168.55.1" ,80);
////	size = sprintf((char*)arr , "AT+CIPSTART=\"TCP\",\"%s\",%d,7200\r\n" , "192.168.1.5" ,80);
//
//	WIFI_LOCAL_SEND(arr , size);
//}

void WIFI_LOCAL_RESET (void)
{
	unsigned char arr[30];
	int size = sprintf((char*)arr , "AT+RST\r\n");

	WIFI_LOCAL_SEND(arr,size);
}

void WIFI_LOCAL_TCP_CLOSE (void)
{
	unsigned char arr[30];
	int size = sprintf((char*)arr , "AT+CIPCLOSE\r\n");

	WIFI_LOCAL_SEND(arr,size);
}

void WIFI_LOCAL_CLOSE_ECHO (void)
{
	unsigned char arr[30];
	int size = sprintf((char*)arr , "ATE0\r\n");
	WIFI_LOCAL_SEND(arr,size);
	_delay_ms(100);
	WIFI_LOCAL_FLUSH();
}
void WIFI_LOCAL_FLUSH(void)
{
	unsigned char arr[1000];
	{
	while(	WIFI_LOCAL_QUEUE_GET_SIZE())
		WIFI_LOCAL_RAED(arr);
	}
}

void WIFI_LOCAL_SEND_IP (unsigned char *data,int size)
{
	WIFI_LOCAL_FLUSH();
	unsigned char arr[30];
	memset(arr , 0 , sizeof(arr));
	int size1 =  sprintf((char*)arr, "AT+CIPSEND=0,%d\r\n", size);
	WIFI_LOCAL_SEND(arr,size1);
	_delay_ms(100);
	WIFI_LOCAL_SEND(data,size);
}
//void WIFI_LOCAL_SEND_DATA (unsigned char *data,int size)
//{
//	unsigned char arr[30];
//	memset(arr , 0 , sizeof(arr));
//	int size1 =  sprintf((char*)arr, "AT+CIPSEND=%d\r\n", size);
//	WIFI_LOCAL_SEND(arr,size1);
//	_delay_ms(100);
//	WIFI_LOCAL_SEND(data,size);
//
//}
void WIFI_LOCAL_SEND (unsigned char *DATA, int size)
{
	UART_Write_Array(USART1,DATA,size);

}
int WIFI_LOCAL_QUEUE_GET_SIZE (void)
{
	return SpecialUart_wifi_local_getsize();
}
int WIFI_LOCAL_RAED (unsigned char*data)
{
	return SpecialUart_wifi_local_array(data);
}



uint8_t WIFI_WAIT_RESPONSE_data( uint8_t response_number , char * data ,...)
{
	uint8_t response_check = 0 ;
	uint8_t arr_response[1000] = {0} ;
	SpecialTimer_Start(WIFI_ATCOMMANDER_TIMEOUT);

	while (!SpecialTimer_Check(WIFI_ATCOMMANDER_TIMEOUT,10000))
	{
		 	SpecialUart_wifi_local_array_DATA_ONLY(arr_response);

		if (!memcmp((char *)arr_response,(char *)*((&data)+response_check),strlen((char *)*((&data)+response_check))))
		{
			response_check++;
			if (response_check == response_number)
			{
				SpecialTimer_Stop(WIFI_ATCOMMANDER_TIMEOUT);
				SpecialTimer_Reset(WIFI_ATCOMMANDER_TIMEOUT);
				return true ;
			}
		}
		else if (!memcmp((char *)arr_response,"ERROR",strlen("ERROR")))
		{
			SpecialTimer_Stop(WIFI_ATCOMMANDER_TIMEOUT);
			SpecialTimer_Reset(WIFI_ATCOMMANDER_TIMEOUT);
			_delay_ms(500);
			return false ;
		}

	}
	SpecialTimer_Stop(WIFI_ATCOMMANDER_TIMEOUT);
	SpecialTimer_Reset(WIFI_ATCOMMANDER_TIMEOUT);

	return false ;
}


uint8_t WIFI_WAIT_RESPONSE( uint8_t response_number , char * data ,...)
{
	uint8_t response_check = 0 ;
	uint8_t arr_response[1000] = {0} ;
	SpecialTimer_Start(WIFI_ATCOMMANDER_TIMEOUT);

	while (!SpecialTimer_Check(WIFI_ATCOMMANDER_TIMEOUT,10000))
	{
		 	WIFI_LOCAL_RAED(arr_response);

		if (!memcmp((char *)arr_response,(char *)*((&data)+response_check),strlen((char *)*((&data)+response_check))))
		{
			response_check++;
			if (response_check == response_number)
			{
				SpecialTimer_Stop(WIFI_ATCOMMANDER_TIMEOUT);
				SpecialTimer_Reset(WIFI_ATCOMMANDER_TIMEOUT);
				return true ;
			}
		}
		else if (!memcmp((char *)arr_response,"ERROR",strlen("ERROR")))
		{
			SpecialTimer_Stop(WIFI_ATCOMMANDER_TIMEOUT);
			SpecialTimer_Reset(WIFI_ATCOMMANDER_TIMEOUT);
			_delay_ms(500);
			return false ;
		}

	}
	SpecialTimer_Stop(WIFI_ATCOMMANDER_TIMEOUT);
	SpecialTimer_Reset(WIFI_ATCOMMANDER_TIMEOUT);

	return false ;
}

