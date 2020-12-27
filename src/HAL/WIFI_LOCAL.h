/*
 * WIFI_MQTT.h
 *
 *  Created on: Jan 30, 2020
 *      Author: amd
 */

#ifndef HAL_WIFI_MQTT_H_
#define HAL_WIFI_MQTT_H_


#define   STATIC_IP  "AT+CIPSTA_DEF=\"192.168.1.160\",\"192.168.1.1\",\"255.255.255.0\"\r\n"

uint8_t WIFI_WAIT_RESPONSE( uint8_t response_number , char * data ,...);
void WIFI_LOCAL_INIT (void);
uint8_t WIFI_LOCAL_JAP (void);
void WIFI_LOCAL_TCP_START (void);
void WIFI_LOCAL_RESET (void);
void WIFI_LOCAL_TCP_CLOSE (void);
void WIFI_LOCAL_CLOSE_ECHO (void);
void WIFI_LOCAL_FLUSH(void);
void WIFI_LOCAL_SEND_IP (unsigned char *data,int size);
void WIFI_LOCAL_SEND (unsigned char *DATA, int size);
int WIFI_LOCAL_QUEUE_GET_SIZE (void);
int WIFI_LOCAL_RAED (unsigned char*data);
void WIFI_LOCAL_SEND_DATA (unsigned char *data,int size);
uint8_t WIFI_WAIT_RESPONSE( uint8_t response_number , char * data ,...);
#endif /* HAL_WIFI_MQTT_H_ */
