void _delay_ms(int n)
{
	volatile int i;
	    for (; n > 0; n--)
	        for (i = 0; i < 3195; i++) ;
}
