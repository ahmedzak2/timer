/*
 * t1.h
 *
 *   Description: Header file for the timer 1 driver
 *      Author: Ahmed zakria
 */

#ifndef T1_H_
#define T1_H_
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "TIMER_PBcfg.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* timer 1 configurations for  */

#define timer1 0
#define timer0 1


#define NULL (void*)0
typedef enum  // Select bite
{
	no_clock,no_prscaling,clock_8,clock_64,clock_256,clock_1024,externalclok_fallingedge,externalclok_risingedge
}clock_select; // for clock source

#if (timer1 ==1)
typedef enum  // Select bite
{
	Normal_PIN,Comapre1A_PIN,Comapre1B_PIN,Caputre_PIN
}Mode_pin;

typedef enum  // Select bite
{
	Normal,PWM_8bit,PWM_9bit,Comapre_mode,Caputre_unit,fast_PWM_IC,/* by use capture unit*/
	fast_PWM__compare/* by use compare mode*/
}Mode_operation;
typedef enum  // Select bite
{
	Normal_port,toggle,set_output_low,set_output_high
}Mode_compare; // for channel a or b
typedef enum  // Select bite
{
	falling_dge , rising_edge
}Input_capture_edge; // for edge select

typedef enum  // Select bite
{
	over_flow, compareA, compareB, caputre
}tmier1_flag; // for clock source
typedef struct
{
	/* Member contains the voltage channel belongs to */
	Mode_operation Mode;

	/* Member contains the result of the Channel is  to where*/
	Mode_compare compare;
	/* Member contains the trigger timer to work on positive edge the Channel is  to where*/
	Input_capture_edge edge;
	clock_select clock;
	tmier1_flag flag;
	uint16 max; // MAX VALUE
	uint16 Dutycycle; // VALUE TO MAKE COMPARE OR DUTY
	uint8 start ; // Initial VALUETO START COUNTING
	Mode_pin PIN;
}timer1_Config_type;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* */
void timer1_init(timer1_Config_type * config);

/* to select mode of timer*/

/*
 * Description: Function to set the Call Back function address.
 */
void Icu_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(const Input_capture_edge edgeType);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void);
/* Extern ADC structures to be used by to initlize adc */

extern const timer1_Config_type T1_config;
#endif

#if(timer0 ==1)
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define timer0_counter 0
#define timer0_comapre 0
#define timer0_PWMMODE 0
typedef enum  // Select bite
{
	timer0_COUNTER_PIN,timer0_Comapre
}Mode_timer0_pin;

typedef enum  // Select bite
{
	TIMER0_Normal,TIMER0_PWM_PHASECORRECT,TIMER0_Comapre_mode,TIMER0_fast_PWM

}Mode_timer0_operation;
typedef enum  // Select bite
{
	TIMER0_Normal_port,TIMER0_toggle,TIMER0_CLEAR,TIMER0_set
}Mode_TIMER0_compare_NONPWM; // for non PWM
typedef enum  // Select bite
{
	TIMER0_Normal_Operation,TIMER0_RESERVED,CLEAR,set
}Mode_TIMER0_compare_PWM; // for PWM
typedef enum  // Select bite
{
	tmier0_over_flow, tmier0_compare
}tmier0_flag; // for clock source
typedef enum  // Select bite
{
	tmier0_nonpwm, tmier0_pwm
}tmier0_PWM; // for clock source
typedef struct
{
	/* Member contains the voltage channel belongs to */
	Mode_timer0_operation OPERATION;

	/* Member contains the result of the Channel is  to where*/
	Mode_TIMER0_compare_NONPWM compare;
	/* Member contains the trigger timer to work on positive edge the Channel is  to where*/
	Mode_TIMER0_compare_PWM pwm;
	clock_select clock;
	tmier0_flag flag;
	uint16 max; // MAX VALUE
	uint16 Dutycycle; // VALUE TO MAKE COMPARE OR DUTY
	uint8 start ; // Initial VALUETO START COUNTING
	Mode_timer0_pin PIN;
	tmier0_PWM mode;
}timer0_Config_type;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void timer0_init(timer0_Config_type * timer0_config);
extern const timer0_Config_type T0_config;
 void TIMER0_setCallBack(void(*a_ptr)(void));


#endif
/* Extern ADC structures to be used by to initlize adc */


#endif /* T1_H_ */
