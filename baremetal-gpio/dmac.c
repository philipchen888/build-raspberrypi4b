/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "dmac.h"
#include "timer.h"
#include "uart.h"

unsigned int randomized( unsigned int i )
{
    unsigned int j;
    int k;
    int m;

    k = (i >> 28) + (i >> 2) & 0xf;
    if ( k < 5 )
        k = 5;
    j = i + 3;
    for (m = 0; m < k; m++) {
       if ( j & 0x80000000 ) {
           j = ((j ^ 0x00000062) << 1) + 1;
       } else {
           j = (j << 1);
       }
    }
    return j;
}

void dmac_test( void )
{
    struct DMA_CB cbp1, cbp2;
    unsigned long long i;
    unsigned long long src;
    unsigned long long dest;
    int k;

    for ( i = 0x10000000; i < 0x10004000; i = i + 4 ) {
        *(volatile unsigned int *)i = randomized( i );
        if ( i < 0x10000040 )
            printf( "0x%x\r\n", *(volatile unsigned int *)i);
        if ( (i & 0xfffff) == 0x0 )
            printf( ".");
    }

    //---- sram to ddr then ddr to ddr -----------------------------
    for ( k = 0; k < 2; k++ ) {
        *DMA0_CS |= 0x80000000;           // reset DMAC
        if ( k == 0 ) {
            cbp1.ti = DMA_CB_SRC_INC | DMA_CB_DEST_INC;
            cbp1.srce_ad = 0x10000000;
            cbp1.dest_ad = 0x20000000;
            cbp1.tfr_len = 0x4000;
            cbp1.stride = 0x0;
            cbp1.next_cb = 0x0;
            cbp1.debug = 0x0;
            cbp1.unused = 0x0;
            *DMA0_CONBLK_AD = (unsigned long long)&cbp1;
            // init first dest
            *(volatile unsigned int *)0x20000000 = 0x12345678;
        } else {
            cbp2.ti = DMA_CB_SRC_INC | DMA_CB_DEST_INC;
            cbp2.srce_ad = 0x20000000;
            cbp2.dest_ad = 0x30000000;
            cbp2.tfr_len = 0x4000;
            cbp2.stride = 0x0;
            cbp2.next_cb = 0x0;
            cbp2.debug = 0x0;
            cbp2.unused = 0x0;
            *DMA0_CONBLK_AD = (unsigned long long)&cbp2;
            // init first dest
            *(volatile unsigned int *)0x30000000 = 0x9abcdef0;
        }
        *DMA0_CS |= 1;                    // start DMA
        printf("DMAC started\r\n");
        udelay( 10 );
        // wait done
        while( !(*DMA0_CS & 0x2) );
        *DMA0_CS |= 0x2;                  // clear done

        if ( k == 0 ) {
            src  = 0x10000000;
            dest = 0x20000000;
        } else {
            src  = 0x20000000;
            dest = 0x30000000;
        }
        for (i=0x0; i<0x4000; i = i + 4) {
            if (i < 0x40 )
                printf( "0x%x\r\n", *(volatile unsigned int *)dest );
            if ( *(volatile unsigned int *)dest != *(volatile unsigned int *)src ) {
                printf( "Error ! dest addr = 0x%x, dest data = 0x%x, src data = 0x%x,\r\n", dest, *(volatile unsigned int *)dest, *(volatile unsigned int *)src );
                break;
            }
            src += 4;
            dest += 4;
        }
        // registers changed after dma
        printf( "DMA0_CS = 0x%x\r\n", *DMA0_CS );
        printf( "DMA0_SOURCE_AD = 0x%x\r\n", *DMA0_SOURCE_AD );
        printf( "DMA0_DEST_AD = 0x%x\r\n", *DMA0_DEST_AD );
    }
}
