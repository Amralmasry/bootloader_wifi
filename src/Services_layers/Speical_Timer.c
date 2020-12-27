
#include "Services_layers.h"
#include "Speical_Timer.h"
#include "../MCAL/TIMER_6.h"

volatile unsigned long Counter_S_Timer[TIMER0_COUNTER_NUMBER];
unsigned char Counter_S_Timer_flag[TIMER0_COUNTER_NUMBER];

static void SpecialTimer_update(void)
{
	for(int index = 0 ; index < TIMER0_COUNTER_NUMBER ; index ++)
	{
		if(Counter_S_Timer_flag [index] )
			Counter_S_Timer[index]++;
	}
}

void SpecialTimer_Init()
{
	timer_6_init();
	timer_6_setcallback(SpecialTimer_update);
}




void SpecialTimer_Reset(SPTIMER_T index)
{
	if(index < TIMER0_COUNTER_NUMBER)
		Counter_S_Timer[index] = 0;
}

unsigned char SpecialTimer_IsActive(SPTIMER_T index)
{
	return Counter_S_Timer_flag[index];
}
void SpecialTimer_Start(SPTIMER_T index)
{
	if(index < TIMER0_COUNTER_NUMBER)
		Counter_S_Timer_flag[index] = true;
}

void SpecialTimer_Stop(SPTIMER_T index )
{
	if(index < TIMER0_COUNTER_NUMBER)
		Counter_S_Timer_flag[index] = false;
}

char SpecialTimer_Check(SPTIMER_T index ,unsigned long compare)
{
	if(index < TIMER0_COUNTER_NUMBER)
		return !(compare > Counter_S_Timer[index]);
	else
		return error;
}
uint32_t SpecialTimer_VALUE(SPTIMER_T index )
{

		return ( Counter_S_Timer[index]);

}
