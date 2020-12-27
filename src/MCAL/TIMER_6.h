

#ifndef _timer6_
#define _timer6_

#include "stdint.h"

void timer_6_setcallback (void (*ptr) (void));



void timer_6_init(void);

uint64_t millis (void);


#endif
