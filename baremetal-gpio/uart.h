/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef	_MINI_UART_H
#define	_MINI_UART_H

#include "registers.h"

#define    UARTCTL_KILL     0x20
#define    UARTCTL_ENABLE   0x10
#define    UARTCTL_SRC_OSC  0x1
#define    UARTCTL_SRC_PLLD 0x6

void uart_init ( void );
char uart_getc ( void );
void uart_putc ( char c );
void uart_clear( void );
void uart_test( void );

#endif  /*_MINI_UART_H */
