/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "registers.h"
#include "gpio.h"
#include "timer.h"

int digitalRead( void )
{
    if ((*GPLEV0 & 0x800) != 0x0) {
        return 1;
    } else {
        return 0;
    }
}

void digitalWrite( int state )
{
    if ( state == LOW ) {
        *GPCLR0 = 0x800000;
    } else if ( state == HIGH ) {
        *GPSET0 = 0x800000;
    }
}

void led_test( void )
{
    int i;

    // GPIO23 as output
    *GPFSEL2 = (*GPFSEL2 & ~(0x7 << 9)) | (0x1 << 9); 

    for (i=0; i< 5; i++) {
        digitalWrite( HIGH );
        udelay( 1000000 );
        digitalWrite( LOW );
        udelay( 1000000 );
    }
}

void button_test( void )
{
    int i;
    int old_state;
    int current_state;

    // GPIO23 as output
    *GPFSEL2 = (*GPFSEL2 & ~(0x7 << 9)) | (0x1 << 9);
    // GPIO11 as input
    *GPFSEL1 = (*GPFSEL1 & ~(0x7 << 3));

    printf("Push button 10 times\r\n");
    old_state = 0;
    for (i=0; i<10; ) {
        current_state = digitalRead();
        if ( old_state == 0 && current_state == 1 ) {
            digitalWrite( HIGH );  // On
            old_state = current_state;
        } else if ( old_state == 1 && current_state == 0 ) {
            digitalWrite( LOW );   // Off
            old_state = current_state;
            i++;
        }
        udelay( 50000 );
    }
}
