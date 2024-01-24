/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "i2c.h"
#include "timer.h"

void wiringPiI2CWriteReg8( char chip, int reg, int bufi )
{
    char buf[1] = {bufi};

    *BSC1_A = chip;
    *BSC1_DLEN = 2;
    *BSC1_FIFO = reg;
    *BSC1_FIFO = buf[0];

    *BSC1_S = CLEAR_STATUS;   // Reset status bits (see #define)
    *BSC1_C = START_WRITE;    // Start Write (see #define)
    while( !(*BSC1_S & BSC_S_DONE) );
}

void set_backlight( int r, int g, int b )
{
    wiringPiI2CWriteReg8( 0x62, 0, 0 );
    wiringPiI2CWriteReg8( 0x62, 1, 0 );
    wiringPiI2CWriteReg8( 0x62, 8, 0xaa );
    wiringPiI2CWriteReg8( 0x62, 4, r );
    wiringPiI2CWriteReg8( 0x62, 3, g );
    wiringPiI2CWriteReg8( 0x62, 2, b );
}

void textCommand( int cmd )
{
    wiringPiI2CWriteReg8( 0x3e, 0x80, cmd);
}

void setText( char * text )
{
    int i;
    textCommand( 0x01 );        // clear display
    udelay( 50000 );
    textCommand( 0x08 | 0x04 ); // display on, no cursor
    textCommand( 0x28 );        // 2 lines
    udelay( 50000 );
    for (i=0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            textCommand( 0xc0 );
        } else {
            wiringPiI2CWriteReg8( 0x3e, 0x40, text[i]);
        }
    }
}

void i2c_lcd_test( void )
{
    int j;

    *GPFSEL0 = (*GPFSEL0 & ~(0x3f << 6)) | (0x24 << 6); // select I2C1
    *BSC1_DIV = 1500;           // 500 MHz / 1500 = 333 KHz
    textCommand( 0x01 );        // clear display
    udelay( 50000 );
    textCommand( 0x08 | 0x04 ); // display on, no cursor
    textCommand( 0x28 );        // 2 lines
    udelay( 50000 );

    set_backlight( 255, 0, 0 );
    for (j=0; j< 5; j++)
    {
      set_backlight( 255, 0, 0 );
      udelay( 1000000 );
      set_backlight( 255, 255, 0 );
      udelay( 1000000 );
      set_backlight( 0, 255, 0 );
      udelay( 1000000 );
      set_backlight( 0, 255, 255 );
      udelay( 1000000 );
      set_backlight( 0, 0, 255 );
      udelay( 1000000 );
      set_backlight( 255, 0, 255 );
      udelay( 1000000 );
    }
    set_backlight( 128, 255, 0 );
    setText( "Hello world !\nIt works !\n" );
}
