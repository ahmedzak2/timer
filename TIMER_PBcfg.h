/*
 * ADC_PBcfg.h
 *
 *  Created on: Mar 31, 2021
 *      Author: Ahmed
 */

#ifndef TIMER_PBCFG_H_
#define TIMER_PBCFG_H_
#define Pre_scaler 2 // TO GET PRESCALER
#if(timer1==1)
#define force_output_channelA 1  // channel a
#define force_output_channelB 1  // channel b
#define input_caputr_noise 1 // to make  unit work or not
#define intial_value 0 // value to timer
#endif
#if(timer0==1)
#define timer0_force_output 0

#endif
#endif /* TIMER_PBCFG_H_ */
