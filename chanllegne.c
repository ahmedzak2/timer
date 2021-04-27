/*
 * chanllegne.c
 *
 *  Created on: Mar 6, 2021
 *      Author: Ahmed
 */


#include"TIMER.h"
unsigned char g_Flag =0;
/*
void tmier0_narmal_mode_init(void)
{
	/*
	 * 1:MAKE THE TIMER NORMAL FLOW BY CLEAR THE WGM00,WGM01
	 * 2:MAKE COM00 AND COM01 CLEAR TO ACTIVATE THE NORMAL
	 * 3:ACTIVATE THE PRESCALER BY  SET CS02

	TCCR0 = (1<<FOC0)|(1<<CS02);
	TCNT0=0;
	TIMSK =(1<<TOIE0);

}
ISR (TIMER0_OVF_vect)
{
	g_Flag++;

	}
	*/

void COUNT (void)
{
	g_Flag++;
}





int main()
{
	timer0_init(&T0_config);
	TIMER0_setCallBack(COUNT);

	//tmier0_narmal_mode_init();
SREG|=(1<<7);
	DDRC|= 0X0F; // configure pin 0,1,2,3 in port c as output led
	PORTC &= 0xF0;  // Analyze the 7 segment
	int i;
	while(1)
	{
	// CHECK FOR PORT D  IF HAVE NUMBER 9
		if (g_Flag == 123)
		{
					if ((PORTC & 0X0F)==9)
					{
						i=0;
						PORTC = (PORTC & 0xF0) | (i & 0x0F);

					}
					else
					{
						i++;
						PORTC=(PORTC & 0XF0)|(i & 0X0F);
					}
					g_Flag =0;
				}
	}
}

