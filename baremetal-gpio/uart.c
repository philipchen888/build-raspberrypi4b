/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "uart.h"
#include "timer.h"

void uart_init ( void )
{
    // set uart clock
    *CM_UART_CNTL = CM_PASSWORD | UARTCTL_KILL;
    udelay( 10 );
    *CM_UART_DIV = CM_PASSWORD | (15 << 12) | 0xa00;  // 500 MHz / 2.51465 = 198835
    *CM_UART_CNTL = CM_PASSWORD | UARTCTL_ENABLE | UARTCTL_SRC_PLLD | 1 << 9;
    udelay( 10 );

    // set uart gpio 14, 15
    *GPFSEL1 = (*GPFSEL1 & ~(0x3f << 12)) | (0x12 << 12);

    *AUX_ENABLES |= 1;                  //Enable mini uart (this also enables access to it registers)
    *AUX_MU_CNTL_REG = 0;               //Disable auto flow control and disable receiver and transmitter (for now)
    *AUX_MU_LCR_REG = 3;                //Enable 8 bit mode
    *AUX_MU_IER_REG = 0;                //Disable receive and transmit interrupts
    *AUX_MU_MCR_REG = 0;                //Set RTS line to be always high
    *AUX_MU_BAUD_REG = 216;             //Set baud rate to 115200

    *AUX_MU_CNTL_REG = 3;               //Finally, enable transmitter and receiver
}

void uart_putc ( char c )
{
    while(1) {
        if(*AUX_MU_LSR_REG & 0x20) 
            break;
    }
    *AUX_MU_IO_REG = c;
}

char uart_getc ( void )
{
    while(1) {
        if(*AUX_MU_LSR_REG & 0x01) 
            break;
    }
    return(*AUX_MU_IO_REG & 0xFF);
}

void uart_clear( void )
{
    char ch[5];

    ch[0] = 27;
    ch[1] = '[';
    ch[2] = '2';
    ch[3] = 'J';
    ch[4] = '\0';
    printf( ch );
}

void uart_test( void )
{
    char ch;

    printf( "Hello ! Type a sentence and press enter.\r\n" );
    ch = '\0';
    while( ch != '\r') {
        ch = uart_getc();
        uart_putc( ch );
    }
    printf( "\r\n" );
}
