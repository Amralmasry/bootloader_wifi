/*
 * utility.h
 *
 *  Created on: Oct 16, 2019
 *      Author: amd
 */

#ifndef SERVICES_LAYERS_UTILITY_H_
#define SERVICES_LAYERS_UTILITY_H_


#include <stdint.h>

int Integer_To_String (char*arr,long integer);
int Sprint_int(char *arr ,char *temp,int integer,... );
int Sprint_str(char *arr ,char *temp,char* str,... );
int sprint(char*arr,char*temp,char* str,...);



void string_to_int (unsigned char *num,uint32_t*data,int number);

#endif /* SERVICES_LAYERS_UTILITY_H_ */
