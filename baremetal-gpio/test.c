/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "pwm.h"
#include "i2c.h"
#include "spi.h"
#include "dmac.h"

int current_el( void )
{
    int el;
    asm volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
    return el >> 2;
}

int getCpuId( void )
{
    asm volatile( "mrs x0, mpidr_el1\n"
                  "and x0, x0, #3\n"
                  "ret" );
}

void led_blink( void )
{
    // green led is GPIO42
    *GPFSEL4 = (*GPFSEL4 & ~(7 << 6)) | (1 << 6);
    while ( 1 ) {
        *GPSET1 = 1 << (42 - 32);
        udelay( 500000 );
        *GPCLR1 = 1 << (42 - 32);
        udelay( 500000 );
    }
}

void ddr_test( void )
{
    unsigned long long i;
    printf( "In ddr_test\r\n");

    printf( "Writing 4GB DDR with random data\r\n");
    for ( i = 0x10000000; i < 0x20000000; i = i + 4 ) {
        *(volatile unsigned int *)i = randomized( i );
        if ( i < 0x10000100 )
            printf( "0x%x\r\n", *(volatile unsigned int *)i);
        if ( (i & 0xfffff) == 0x0 )
            printf( ".");
    }
    printf( "Reading 4GB DDR\r\n");
    for ( i = 0x10000000; i < 0x20000000; i = i + 4 ) {
        if ( i < 0x10000100 )
            printf( "0x%x\r\n", *(volatile unsigned int *)i);
        if ( *(volatile unsigned int *)i != randomized( i ) )
            printf( "dram test failed !\r\n");
        if ( (i & 0xfffff) == 0x0 )
            printf( ".");
    }
}

void displaydst( char *dst )
{
    int i;
    unsigned int tmp;

    for (i=0; i<512; i++) {
        printf( "%02X ", dst[i] );
        if ( (i & 0xf) == 0xf ) {
            printf( "\r\n" );
        }
    }
}

char test_menu( void )
{
    char ch;

    uart_clear();
    printf( "--- select a test ---\r\n" );
    printf( "1. uart test\r\n2. led test\r\n3. button test\r\n4. pwm led test\r\n5. i2c lcd test\r\n6. tongsong\r\n7. servo\r\n8. spi oled test\r\n9. ddr test\r\na. dmac test\r\nq. quit\r\n");
    ch = uart_getc();
    if ( ch == 'q' )
        printf( "Goodbye !\r\n" );
    return ch;
}

void main( void )
{   
    char test_item;
    char ch;

    printf("Hello world ! Cpu is %d\r\n", getCpuId());

    test_item = '\0';
    while( test_item != 'q' ) {
        test_item = test_menu();
        if ( test_item == '1' ) {
            uart_test();
        }  else if ( test_item == '2' ) {
            led_test();
        } else if ( test_item == '3' ) {
            button_test();                // push button 10 times
        } else if ( test_item == '4' ) {
            pwm_led_test();
        } else if ( test_item == '5' ) {
            i2c_lcd_test();
            printf( "press x to exit i2c lcd test\r\n" );
            ch = uart_getc();
        } else if ( test_item == '6' ) {
            tongsong();
        } else if ( test_item == '7' ) {
            servo();
        } else if ( test_item == '8' ) {
            ssd1306_test();
        } else if ( test_item == '9' ) {
            ddr_test();
        } else if ( test_item == 'a' ) {
            dmac_test();
        }
    }

    led_blink();
    while( 1 );
}
