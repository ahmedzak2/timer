/*
 * t1.c
 *
 *  C Description: source file for thetimer 1 driver
 *      Author: Ahmed zakria
 */


#include "TIMER.h"

#if(timer1==1)
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) =NULL_PTR ;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{

}
ISR(TIMER1_COMPB_vect)
{

}
ISR(TIMER1_OVF_vect)
{

}
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL)
	{
		(*g_callBackPtr)();


	}
}
void timer1_init(timer1_Config_type * config)
{
	if( config->PIN == Caputre_PIN)
	{
		DDRD &=~(1<<PD6);

	}
	if(config->PIN ==Normal_PIN)
	{
		DDRB &=~(1<<PB1);

	}
	if(config->PIN == Comapre1A_PIN)
	{
		DDRD &=~(1<<PD5);

	}
	if(config->PIN == Comapre1B_PIN)
	{
		DDRD &=~(1<<PD4);

	}
	SREG|=(1<<7);
	//TCNT1 = 0;
	//ICR1 = 0;
	TCNT1 = config->start;
#if(force_output_channelA == 1)
	{
		OCR1A = config->Dutycycle;
		ICR1 =config->max;
		SET_BIT(TCCR1A,FOC1A);
	}
	if (force_output_channelB == 1)
	{
		OCR1A = config->Dutycycle;
		ICR1 =config->max;
		SET_BIT(TCCR1A,FOC1B);
	}


	if( config->compare ==	Normal_port)
	{

	}
	if( config->compare ==	toggle)
	{
		if(force_output_channelA == 1)
		{
			SET_BIT(TCCR1A,COM1A0);
		}
		if(force_output_channelB == 1)
		{
			SET_BIT(TCCR1A,COM1B0);
		}
	}
	if( config->compare ==	set_output_low)
	{
		if(force_output_channelA == 1)
		{
			SET_BIT(TCCR1A,COM1A1);
		}
		if(force_output_channelB == 1)
		{
			SET_BIT(TCCR1A,COM1B1);
		}
	}
	if( config->compare ==	set_output_high)
	{
		if(force_output_channelA == 1)
		{
			SET_BIT(TCCR1A,COM1A0);
			SET_BIT(TCCR1A,COM1A1);
		}
		if(force_output_channelB == 1)
		{
			SET_BIT(TCCR1A,COM1B0);
			SET_BIT(TCCR1A,COM1B1);
		}
	}

#endif
	if(config->Mode == Normal)
	{

	}
	if(config->Mode == PWM_8bit)
	{
		SET_BIT(TCCR1A,WGM10);
	}
	if( config->Mode == PWM_9bit)
	{
		SET_BIT(TCCR1A,WGM11);
	}
	if(config->Mode == Comapre_mode)
	{
		SET_BIT(TCCR1B,WGM12);
	}
	if( config->Mode == Caputre_unit)
	{
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);

	}
	if(config->Mode ==	fast_PWM_IC)
	{
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
	}
	if( config->Mode ==	fast_PWM__compare)
	{
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM12);
		SET_BIT(TCCR1A,WGM13);
	}
	if( config->edge ==	rising_edge)
	{
		SET_BIT(TCCR1B,ICES1);

	}
#if(input_caputr_noise==1)
	SET_BIT(TCCR1B,ICNC1);
#endif

	if( config->clock ==no_clock)
	{

	}
	if( config->clock == no_prscaling)
	{
		SET_BIT(TCCR1B,CS10);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS12);
	}
	else if( config->clock == clock_8)
	{
		SET_BIT(TCCR1B,CS11);
	}
	else if( config->clock == clock_64)
	{
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
	}
	else if( config->clock == clock_256)
	{
		SET_BIT(TCCR1B,CS12);
	}
	else if( config->clock == clock_1024)
	{
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS12);
	}
	else if( config->clock == externalclok_fallingedge)
	{
		SET_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
	}
	else if( config->clock == externalclok_risingedge)
	{
		SET_BIT(TCCR1B,CS10);
		SET_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS12);
	}
	if( config->flag ==over_flow)
	{
		SET_BIT(TIMSK,TOIE1);
	}
	else if( config->flag ==compareA)
	{
		SET_BIT(TIMSK,OCIE1A);
	}
	else if( config->flag ==compareB)
	{
		SET_BIT(TIMSK,OCIE1B);
	}
	else if( config->flag ==caputre)
	{
		SET_BIT(TIMSK,TICIE1);
	}
}
void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
void Icu_setEdgeDetectionType(const Input_capture_edge edgeType)
{
	if( edgeType ==	rising_edge)
	{
		SET_BIT(TCCR1B,ICES1);

	}
	else
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
}
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1 ;
}

void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}

void Icu_DeInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 0;
	ICR1 =0;
	TIMSK &= ~(1<<TICIE1);
}
#endif
#if(timer0==1)
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
ISR(TIMER0_OVF_vect)
{

	if(g_callBackPtr != NULL)
{
	(g_callBackPtr)();



}
	void TIMER0_setCallBack(void(*a_ptr)(void))
	{
		/* Save the address of the Call back function in a global variable */
		g_callBackPtr = a_ptr;
	}

}



ISR(TIMER0_COMP_vect)
{

}
void timer0_init(timer0_Config_type * timer0_config)
{
	SREG|=(1<<7);

		TCNT0 = timer0_config->start;
		//OCR0 = timer0_config->Dutycycle;
#if(timer0_counter==1)
	if(timer0_config->PIN == timer0_COUNTER_PIN)
	{
		DDRD &=~(1<<PB0);
	}
#endif
#if(timer0_comapre==1)
	 if(timer0_config->PIN == timer0_Comapre)
	{
		DDRD |=(1<<PB3);
	}
#endif
	 if(timer0_config->mode == tmier0_pwm)
	 	{
	 if(timer0_config ->pwm == 	TIMER0_Normal_Operation)
	 		{
	 			CLEAR_BIT(TCCR0,COM00);
	 			CLEAR_BIT(TCCR0,COM01);

	 		}
	 		else if(timer0_config ->pwm == 	TIMER0_RESERVED)
	 		{
	 			SET_BIT(TCCR0,COM00);
	 			CLEAR_BIT(TCCR0,COM01);


	 		}
	 		else if(timer0_config ->pwm == 	CLEAR)
	 		{
	 			CLEAR_BIT(TCCR0,COM00);
	 			SET_BIT(TCCR0,COM01);

	 		}
	 		else if(timer0_config ->pwm == 	set)
	 		{
	 			SET_BIT(TCCR0,COM00);
	 			SET_BIT(TCCR0,COM01);

	 		}
	 	}
	if(timer0_config->OPERATION == TIMER0_Normal)
	{
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,FOC0);

	}
	else if(timer0_config->OPERATION == TIMER0_PWM_PHASECORRECT)
	{
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);

	}
	else if(timer0_config->OPERATION == TIMER0_Comapre_mode)
	{
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
	}
	else  if(timer0_config->OPERATION == TIMER0_fast_PWM)
	{
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		CLEAR_BIT(TCCR0,FOC0);

	}
	 if(timer0_config->mode == tmier0_nonpwm)
	 {
		 SET_BIT(TCCR0,FOC0);

	if(timer0_config ->compare == 	TIMER0_Normal_port)
	{
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);


	}
	else if(timer0_config ->compare == 	TIMER0_toggle)
	{
		SET_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
	}
	else if(timer0_config ->compare == 	TIMER0_CLEAR)
	{
		CLEAR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
	}
	else if(timer0_config ->compare == 	TIMER0_set)
	{
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
	}
	 }
	if( timer0_config->flag ==tmier0_over_flow)
		{
			SET_BIT(TIMSK,TOIE0);
		}
	else if( timer0_config->flag ==tmier0_compare)
			{
				SET_BIT(TIMSK,OCIE0);
			}
	if( timer0_config->clock ==no_clock)
		{

		}
		if( timer0_config->clock == no_prscaling)
		{
			SET_BIT(TCCR0,CS00);
			CLEAR_BIT(TCCR0,CS01);
			CLEAR_BIT(TCCR0,CS02);
		}
		else if( timer0_config->clock == clock_8)
		{
			SET_BIT(TCCR0,CS01);
		}
		else if( timer0_config->clock == clock_64)
		{
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
		}
		else if( timer0_config->clock == clock_256)
		{
			SET_BIT(TCCR0,CS02);
		}
		else if( timer0_config->clock == clock_1024)
		{
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS02);
		}
		else if( timer0_config->clock == externalclok_fallingedge)
		{
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}
		else if( timer0_config->clock == externalclok_risingedge)
		{
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}
}

#endif
