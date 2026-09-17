/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "timer.h"

void udelay( int usec )
{
    int i;
    unsigned long long tmp;
    unsigned long long tmp2;
    unsigned long long timebase_h;
    unsigned long long timebase_l;

    timebase_l = *TIMER_COUNTLO;
    timebase_h = *TIMER_COUNTHI;
    tmp = (timebase_h << 32) | timebase_l;
    tmp2 = tmp + usec;
    while( tmp < tmp2 ) {
        timebase_l = *TIMER_COUNTLO;
        timebase_h = *TIMER_COUNTHI;
        tmp = (timebase_h << 32) | timebase_l;
    }
}
