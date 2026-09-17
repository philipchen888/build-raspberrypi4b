/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef	_REGISTERS_H
#define	_REGISTERS_H

#define LOW     0
#define HIGH    1
#define INPUT   0
#define OUTPUT  1

#define CM_PASSWORD     0x5A000000
#define PBASE           0xFE000000

#define GPFSEL0         (volatile unsigned int *)(PBASE+0x00200000)
#define GPFSEL1         (volatile unsigned int *)(PBASE+0x00200004)
#define GPFSEL2         (volatile unsigned int *)(PBASE+0x00200008)
#define GPFSEL3         (volatile unsigned int *)(PBASE+0x0020000c)
#define GPFSEL4         (volatile unsigned int *)(PBASE+0x00200010)
#define GPFSEL5         (volatile unsigned int *)(PBASE+0x00200014)
#define GPSET0          (volatile unsigned int *)(PBASE+0x0020001c)
#define GPSET1          (volatile unsigned int *)(PBASE+0x00200020)
#define GPCLR0          (volatile unsigned int *)(PBASE+0x00200028)
#define GPCLR1          (volatile unsigned int *)(PBASE+0x0020002c)
#define GPLEV0          (volatile unsigned int *)(PBASE+0x00200034)
#define GPLEV1          (volatile unsigned int *)(PBASE+0x00200038)
#define GPEDS0          (volatile unsigned int *)(PBASE+0x00200040)
#define GPEDS1          (volatile unsigned int *)(PBASE+0x00200044)
#define GPHEN0          (volatile unsigned int *)(PBASE+0x00200064)
#define GPHEN1          (volatile unsigned int *)(PBASE+0x00200068)
#define GPPUD           (volatile unsigned int *)(PBASE+0x00200094)
#define GPPUDCLK0       (volatile unsigned int *)(PBASE+0x00200098)

#define AUX_ENABLES     (volatile unsigned int *)(PBASE+0x00215004)
#define AUX_MU_IO_REG   (volatile unsigned int *)(PBASE+0x00215040)
#define AUX_MU_IER_REG  (volatile unsigned int *)(PBASE+0x00215044)
#define AUX_MU_IIR_REG  (volatile unsigned int *)(PBASE+0x00215048)
#define AUX_MU_LCR_REG  (volatile unsigned int *)(PBASE+0x0021504C)
#define AUX_MU_MCR_REG  (volatile unsigned int *)(PBASE+0x00215050)
#define AUX_MU_LSR_REG  (volatile unsigned int *)(PBASE+0x00215054)
#define AUX_MU_MSR_REG  (volatile unsigned int *)(PBASE+0x00215058)
#define AUX_MU_SCRATCH  (volatile unsigned int *)(PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (volatile unsigned int *)(PBASE+0x00215060)
#define AUX_MU_STAT_REG (volatile unsigned int *)(PBASE+0x00215064)
#define AUX_MU_BAUD_REG (volatile unsigned int *)(PBASE+0x00215068)

#define TIMER_CTRLSTS   (volatile unsigned int *)(PBASE+0x00003000)
#define TIMER_COUNTLO   (volatile unsigned int *)(PBASE+0x00003004)
#define TIMER_COUNTHI   (volatile unsigned int *)(PBASE+0x00003008)
#define TIMER_MATCH0    (volatile unsigned int *)(PBASE+0x0000300c)
#define TIMER_MATCH1    (volatile unsigned int *)(PBASE+0x00003010)
#define TIMER_MATCH2    (volatile unsigned int *)(PBASE+0x00003014)
#define TIMER_MATCH3    (volatile unsigned int *)(PBASE+0x00003018)

#define PWM_CONTROL     (volatile unsigned int *)(PBASE+0x0020C000)
#define PWM_STATUS      (volatile unsigned int *)(PBASE+0x0020C004)
#define PWM0_RANGE      (volatile unsigned int *)(PBASE+0x0020C010)
#define PWM0_DATA       (volatile unsigned int *)(PBASE+0x0020C014)
#define PWM1_RANGE      (volatile unsigned int *)(PBASE+0x0020C020)
#define PWM1_DATA       (volatile unsigned int *)(PBASE+0x0020C024)

#define CM_PCM_CNTL  (volatile unsigned int *)(PBASE+0x00101098)
#define CM_PCM_DIV   (volatile unsigned int *)(PBASE+0x0010109c)
#define CM_PWM_CNTL  (volatile unsigned int *)(PBASE+0x001010A0)
#define CM_PWM_DIV   (volatile unsigned int *)(PBASE+0x001010A4)
#define CM_UART_CNTL (volatile unsigned int *)(PBASE+0x001010F0)
#define CM_UART_DIV  (volatile unsigned int *)(PBASE+0x001010F4)

#define BSC1_C          (volatile unsigned int *)(PBASE+0x00804000)
#define BSC1_S          (volatile unsigned int *)(PBASE+0x00804004)
#define BSC1_DLEN       (volatile unsigned int *)(PBASE+0x00804008)
#define BSC1_A          (volatile unsigned int *)(PBASE+0x0080400c)
#define BSC1_FIFO       (volatile unsigned int *)(PBASE+0x00804010)
#define BSC1_DIV        (volatile unsigned int *)(PBASE+0x00804014)

#define AUX_SPI0_CS     (volatile unsigned int *)(PBASE+0x00204000)
#define AUX_SPI0_FIFO   (volatile unsigned int *)(PBASE+0x00204004)
#define AUX_SPI0_CLK    (volatile unsigned int *)(PBASE+0x00204008)
#define AUX_SPI0_DLEN   (volatile unsigned int *)(PBASE+0x0020400C)
#define AUX_SPI0_LTOH   (volatile unsigned int *)(PBASE+0x00204010)
#define AUX_SPI0_DC     (volatile unsigned int *)(PBASE+0x00204014)

#define DMA0_CS             (volatile unsigned int *)(PBASE+0x00007000)
#define DMA0_CONBLK_AD      (volatile unsigned int *)(PBASE+0x00007004)
#define DMA0_TI             (volatile unsigned int *)(PBASE+0x00007008)
#define DMA0_SOURCE_AD      (volatile unsigned int *)(PBASE+0x0000700c)
#define DMA0_DEST_AD        (volatile unsigned int *)(PBASE+0x00007010)
#define DMA0_TXFR_LEN       (volatile unsigned int *)(PBASE+0x00007014)
#define DMA0_STRIDE         (volatile unsigned int *)(PBASE+0x00007018)
#define DMA0_NEXTCONBK      (volatile unsigned int *)(PBASE+0x0000701c)
#define DMA0_DEBUG          (volatile unsigned int *)(PBASE+0x00007020)

void printf(const char *fmt, ...);

#endif  /*_REGISTERS_H */
