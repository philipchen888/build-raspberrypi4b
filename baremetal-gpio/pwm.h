/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __PWM_H__
#define __PWM_H__

#include "registers.h"

#define     CTL_REG_RESET_STATE  0
#define     CTL_REG_PWM1_ENABLE  1
#define     CTL_REG_MSEN1        0x80
#define     CTL_REG_PWM1_MS_MODE (CTL_REG_PWM1_ENABLE | CTL_REG_MSEN1)
#define     CTL_REG_PWM2_ENABLE  0x100
#define     CTL_REG_MSEN2        0x8000
#define     CTL_REG_PWM2_MS_MODE (CTL_REG_PWM2_ENABLE | CTL_REG_MSEN2)

#define    PWMCTL_BUSY     0x80     // Read only
#define    PWMCTL_KILL     0x20
#define    PWMCTL_ENABLE   0x10
#define    PWMCTL_SRC_OSC  0x1
#define    PWMDIV_DIVI(divi) (divi << 12)   // bits 23-12, max 4095

void pwmSetRange( int period );
void pwmSetClock( int value );
void pwmMode( void );
void pwmWrite( int value );
void pwm_led_test( void );
void pwmToneWrite( int freq );
void tone( int melody, int duration, int duration2 );
void tongsong( void );
void servo ( void );

#endif
