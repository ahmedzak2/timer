/*
 * ADC_PBcfg.c
 *
 *  Created on: Mar 31, 2021
 *      Author: Ahmed
 */

#include "TIMER.h"
#if(timer1==1)
const timer1_Config_type T0_config =
{
		Normal,
		set_output_high,
		rising_edge,
		no_prscaling,
		caputre,
		0,
		0,
		0,
		Caputre_PIN
};
#endif
#if(timer0==1)
 const timer0_Config_type T0_config =
{
		TIMER0_Normal,
		TIMER0_Normal_port,
		TIMER0_Normal_Operation,
		tmier0_over_flow,
		clock_256,
		0,
		0,
		0,
		tmier0_nonpwm,
};

#endif
