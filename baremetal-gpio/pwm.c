/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "timer.h"
#include "pwm.h"
#include "uart.h"

void pwmMode( void )
{
    *GPFSEL1 = (*GPFSEL1 & ~(0x7 << 9)) | (0x4 << 9);    // select PWM1
    *CM_PWM_CNTL = CM_PASSWORD | PWMCTL_KILL;
    udelay( 10 );
    *CM_PWM_DIV = CM_PASSWORD | (270 << 12);   // 54 MHz / 270 = 200 KHz
    *CM_PWM_CNTL = CM_PASSWORD | PWMCTL_ENABLE | PWMCTL_SRC_OSC;
    *PWM_CONTROL = CTL_REG_RESET_STATE;  // Turn off PWM - reset state.
    udelay( 50 );
    *PWM1_RANGE = 4000;           // Range of 20 msec -> 4000 counts at 5 usec PWM resolution
    *PWM_CONTROL = CTL_REG_PWM2_MS_MODE;
}

void pwmWrite( int value )
{
    int range;

    if ( value == 0 ) {
        *PWM1_DATA = 0;
    } else {
        range = *PWM1_RANGE;
        *PWM_CONTROL &= ~(1<<8);        // Disable PWM
        *PWM1_DATA = range - value;     // Set duty
        *PWM_CONTROL |= (1<<8);         // Enable PWM
    }
}

void pwmToneWrite( int freq )
{
    int pwm_clock;
    int range;
    int rangediv2;

    if (freq == 0)
        pwmWrite( 0 );
    else {
        pwm_clock = 200000;  // 54 MHz / 270 = 200 KHz
        range = 0;
        while( pwm_clock > freq){
           pwm_clock -= freq;
           range += 1;
        }
        *PWM1_RANGE = range;
        rangediv2 = range >> 1;
        pwmWrite ( rangediv2 );
    }
}

void pwm_led_test( void )
{
    int i;
    int bright;

    pwmMode();
    for (i=0; i< 10; i++) {
        for (bright = 0; bright < 4000; bright=bright+16)
        {
          pwmWrite ( bright );
          udelay( 5000 );
        }

        for (bright = 3999; bright >= 0; bright=bright-16)
        {
          pwmWrite ( bright );
          udelay( 5000 );
        }
    }
}

void tone( int melody, int duration, int duration2 ) 
{
    if ( melody == 0 ) {
       pwmWrite( 0 );
       udelay( duration );
    } else {
       pwmToneWrite( melody );
       udelay( duration );
       pwmWrite( 0 );
    }
    udelay( duration2 ); // * 0.8 );
}

void tongsong( void )
{
    int thisNote;
    int duration;
    int duration2;
    int tmp;

    int melody[] = {
      262, 196, 196, 220, 196, 0, 247, 262
    };

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = {
      4, 8, 8, 4, 4, 4, 4, 4
    };

    pwmMode();
    for ( thisNote = 0; thisNote < 8; thisNote++ ) {
       tmp = noteDurations[thisNote];
       //duration = 1000000 / tmp;
       if ( tmp == 4 ) {
           duration  = 250000;
           duration2 = 200000;
       } else if ( tmp == 8 ) {
           duration  = 125000;
           duration2 = 100000;
       }
       tone( melody[thisNote], duration, duration2 );
    }
}

void servo ( void )
{
    int i;

    *GPFSEL1 = (*GPFSEL1 & ~(0x7 << 9)) | (0x4 << 9);    // select PWM1
    *CM_PWM_CNTL = CM_PASSWORD | PWMCTL_KILL;
    udelay( 10 );
    *CM_PWM_DIV = CM_PASSWORD | (270 << 12);   // 54 MHz / 270 = 200 KHz
    *CM_PWM_CNTL = CM_PASSWORD | PWMCTL_ENABLE | PWMCTL_SRC_OSC;
    *PWM_CONTROL = CTL_REG_RESET_STATE;  // Turn off PWM - reset state.
    udelay( 50 );
    *PWM1_RANGE = 1500;                  // 200 KHz / 1500 = 133 Hz
    *PWM_CONTROL = CTL_REG_PWM2_MS_MODE;

    pwmWrite( 1110 );        // min 1000 = 0 degree, max 1220 = 90 degree
    udelay( 1000000 );

    for (i=0; i< 3; i++) {
      pwmWrite( 1000 );
      printf( "0 degree\r\n" );
      udelay( 1000000 );
      pwmWrite( 1110 );
      printf( "45 degree\r\n" );
      udelay( 1000000 );
      pwmWrite( 1220 );
      printf( "90 degree\r\n" );
      udelay( 1000000 );
      pwmWrite( 1110 );
      printf( "45 degree\r\n" );
      udelay( 1000000 );
    }
    pwmWrite( 0 );
}
