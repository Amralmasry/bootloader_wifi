/*
 * debug.h
 *
 *  Created on: Jan 30, 2020
 *      Author: amd
 */

#ifndef SERVICES_LAYERS_DEBUG_H_
#define SERVICES_LAYERS_DEBUG_H_
void debug_init(void);
void debug_write(char *massage);
void debug_values(int size ,int value,...);
void debug_massege(unsigned char *massage,int size);
void debug_massege_INT(char *massage,int size);

#endif /* SERVICES_LAYERS_DEBUG_H_ */
