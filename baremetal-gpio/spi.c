/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "spi.h"
#include "timer.h"

static const unsigned char font7x14[] = {
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,  // space
  0X00,0X00,0X00,0XFC,0X00,0X00,0X00,0X00,0X00,0X0D,0X00,0X00,  // exclam
  0X00,0X00,0X1E,0X00,0X1E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,  // quotedbl
  0X00,0X20,0XFC,0X20,0XFC,0X20,0X00,0X01,0X0F,0X01,0X0F,0X01,  // numbersign
  0X30,0X48,0X88,0XFC,0X88,0X30,0X06,0X08,0X08,0X1F,0X08,0X07,  // dollar
  0X18,0X24,0XA4,0X78,0X10,0X0C,0X0C,0X02,0X07,0X09,0X09,0X06,  // percent
  0X00,0XB8,0XC4,0X44,0X38,0X80,0X07,0X08,0X08,0X05,0X06,0X09,  // ampersand
  0X00,0X00,0X00,0X1E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,  // quotesingle
  0X00,0X00,0XE0,0X18,0X04,0X02,0X00,0X00,0X03,0X0C,0X10,0X20,  // parenleft
  0X00,0X02,0X04,0X18,0XE0,0X00,0X00,0X20,0X10,0X0C,0X03,0X00,  // parenright
  0X00,0X20,0X40,0XF0,0X40,0X20,0X00,0X02,0X01,0X07,0X01,0X02,  // asterisk
  0X00,0X80,0X80,0XF0,0X80,0X80,0X00,0X00,0X00,0X07,0X00,0X00,  // plus
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X24,0X1C,0X00,0X00,  // comma
  0X00,0X80,0X80,0X80,0X80,0X80,0X00,0X00,0X00,0X00,0X00,0X00,  // hyphen
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X08,0X1C,0X08,0X00,  // period
  0X00,0X00,0X00,0XE0,0X18,0X06,0X30,0X0C,0X03,0X00,0X00,0X00,  // slash
  0XF0,0X08,0X04,0X04,0X08,0XF0,0X03,0X04,0X08,0X08,0X04,0X03,  // zero
  0X00,0X10,0X08,0XFC,0X00,0X00,0X00,0X08,0X08,0X0F,0X08,0X08,  // one
  0X18,0X04,0X04,0X04,0XC4,0X38,0X08,0X0C,0X0A,0X09,0X08,0X08,  // two
  0X04,0X04,0X44,0X64,0X54,0X8C,0X06,0X08,0X08,0X08,0X08,0X07,  // three
  0X00,0XC0,0X30,0X08,0XFC,0X00,0X03,0X02,0X02,0X02,0X0F,0X02,  // four
  0X7C,0X24,0X24,0X24,0X24,0XC4,0X06,0X08,0X08,0X08,0X08,0X07,  // five
  0XF0,0X88,0X44,0X44,0X44,0X80,0X07,0X08,0X08,0X08,0X08,0X07,  // six
  0X04,0X04,0X04,0XC4,0X34,0X0C,0X00,0X0C,0X03,0X00,0X00,0X00,  // seven
  0X18,0XA4,0X44,0X44,0XA4,0X18,0X07,0X08,0X08,0X08,0X08,0X07,  // eight
  0X78,0X84,0X84,0X84,0X44,0XF8,0X06,0X08,0X08,0X08,0X04,0X03,  // nine
  0X00,0X00,0X20,0X70,0X20,0X00,0X00,0X00,0X04,0X0E,0X04,0X00,  // colon
  0X00,0X00,0X60,0X60,0X00,0X00,0X00,0X00,0X12,0X0E,0X00,0X00,  // semicolon
  0X00,0X80,0X40,0X20,0X10,0X08,0X00,0X00,0X01,0X02,0X04,0X08,  // less
  0X20,0X20,0X20,0X20,0X20,0X20,0X01,0X01,0X01,0X01,0X01,0X01,  // equal
  0X00,0X08,0X10,0X20,0X40,0X80,0X00,0X08,0X04,0X02,0X01,0X00,  // greater
  0X18,0X04,0X04,0XC4,0X24,0X18,0X00,0X00,0X00,0X0D,0X00,0X00,  // question
  0XF0,0X08,0XE4,0X14,0X14,0XF8,0X03,0X04,0X09,0X0A,0X0A,0X0B,  // at
  0XF0,0X88,0X84,0X84,0X88,0XF0,0X0F,0X00,0X00,0X00,0X00,0X0F,  // A
  0XFC,0X44,0X44,0X44,0XA8,0X10,0X0F,0X08,0X08,0X08,0X04,0X03,  // B
  0XF8,0X04,0X04,0X04,0X04,0X18,0X07,0X08,0X08,0X08,0X08,0X06,  // C
  0XFC,0X04,0X04,0X04,0X08,0XF0,0X0F,0X08,0X08,0X08,0X04,0X03,  // D
  0XFC,0X44,0X44,0X44,0X04,0X04,0X0F,0X08,0X08,0X08,0X08,0X08,  // E
  0XFC,0X44,0X44,0X44,0X04,0X04,0X0F,0X00,0X00,0X00,0X00,0X00,  // F
  0XF8,0X04,0X04,0X84,0X84,0X98,0X07,0X08,0X08,0X08,0X04,0X0F,  // G
  0XFC,0X40,0X40,0X40,0X40,0XFC,0X0F,0X00,0X00,0X00,0X00,0X0F,  // H
  0X00,0X04,0X04,0XFC,0X04,0X04,0X00,0X08,0X08,0X0F,0X08,0X08,  // I
  0X00,0X00,0X00,0X04,0XFC,0X04,0X06,0X08,0X08,0X08,0X07,0X00,  // J
  0XFC,0X40,0XA0,0X10,0X08,0X04,0X0F,0X00,0X00,0X01,0X02,0X0C,  // K
  0XFC,0X00,0X00,0X00,0X00,0X00,0X0F,0X08,0X08,0X08,0X08,0X08,  // L
  0XFC,0X18,0X60,0X60,0X18,0XFC,0X0F,0X00,0X00,0X00,0X00,0X0F,  // M
  0XFC,0X30,0X40,0X80,0X00,0XFC,0X0F,0X00,0X00,0X00,0X03,0X0F,  // N
  0XF8,0X04,0X04,0X04,0X04,0XF8,0X07,0X08,0X08,0X08,0X08,0X07,  // O
  0XFC,0X84,0X84,0X84,0X84,0X78,0X0F,0X00,0X00,0X00,0X00,0X00,  // P
  0XF8,0X04,0X04,0X04,0X04,0XF8,0X07,0X09,0X09,0X0A,0X1C,0X27,  // Q
  0XFC,0X84,0X84,0X84,0X84,0X78,0X0F,0X00,0X00,0X01,0X02,0X0C,  // R
  0X38,0X44,0X44,0X84,0X84,0X18,0X06,0X08,0X08,0X08,0X08,0X07,  // S
  0X04,0X04,0X04,0XFC,0X04,0X04,0X00,0X00,0X00,0X0F,0X00,0X00,  // T
  0XFC,0X00,0X00,0X00,0X00,0XFC,0X07,0X08,0X08,0X08,0X08,0X07,  // U
  0X3C,0XC0,0X00,0X00,0XC0,0X3C,0X00,0X01,0X0E,0X0E,0X01,0X00,  // V
  0X00,0XFC,0X00,0X00,0X00,0XFC,0X00,0X07,0X08,0X07,0X08,0X07,  // W
  0X0C,0X30,0XC0,0XC0,0X30,0X0C,0X0C,0X03,0X00,0X00,0X03,0X0C,  // X
  0X00,0X1C,0X60,0X80,0X60,0X1C,0X00,0X00,0X00,0X0F,0X00,0X00,  // Y
  0X04,0X04,0X84,0X64,0X14,0X0C,0X0C,0X0B,0X08,0X08,0X08,0X08,  // Z
  0X00,0X00,0XFE,0X02,0X02,0X02,0X00,0X00,0X3F,0X20,0X20,0X20,  // bracketleft
  0X06,0X18,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X0C,0X30,  // backslash
  0X00,0X02,0X02,0X02,0XFE,0X00,0X00,0X20,0X20,0X20,0X3F,0X00,  // bracketright
  0X08,0X04,0X02,0X02,0X04,0X08,0X00,0X00,0X00,0X00,0X00,0X00,  // asciicircum
  0X00,0X00,0X00,0X00,0X00,0X00,0X20,0X20,0X20,0X20,0X20,0X20,  // underscore
  0X00,0X00,0X02,0X04,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,  // grave
  0X40,0X20,0X20,0X20,0X20,0XC0,0X06,0X09,0X09,0X09,0X09,0X0F,  // a
  0XFC,0X40,0X20,0X20,0X20,0XC0,0X0F,0X04,0X08,0X08,0X08,0X07,  // b
  0XC0,0X20,0X20,0X20,0X20,0X40,0X07,0X08,0X08,0X08,0X08,0X04,  // c
  0XC0,0X20,0X20,0X20,0X40,0XFC,0X07,0X08,0X08,0X08,0X04,0X0F,  // d
  0XC0,0X20,0X20,0X20,0X20,0XC0,0X07,0X09,0X09,0X09,0X09,0X05,  // e
  0X40,0X40,0XF8,0X44,0X44,0X08,0X00,0X00,0X0F,0X00,0X00,0X00,  // f
  0XC0,0X20,0X20,0X20,0XC0,0X20,0X19,0X26,0X2A,0X2A,0X29,0X10,  // g
  0XFC,0X40,0X20,0X20,0X20,0XC0,0X0F,0X00,0X00,0X00,0X00,0X0F,  // h
  0X00,0X00,0X20,0XEC,0X00,0X00,0X00,0X08,0X08,0X0F,0X08,0X08,  // i
  0X00,0X00,0X00,0X00,0X20,0XEC,0X00,0X18,0X20,0X20,0X20,0X1F,  // j
  0XFC,0X00,0X80,0X40,0X20,0X00,0X0F,0X01,0X01,0X02,0X04,0X08,  // k
  0X00,0X00,0X04,0XFC,0X00,0X00,0X00,0X08,0X08,0X0F,0X08,0X08,  // l
  0X00,0XE0,0X20,0XC0,0X20,0XC0,0X00,0X0F,0X00,0X07,0X00,0X0F,  // m
  0XE0,0X40,0X20,0X20,0X20,0XC0,0X0F,0X00,0X00,0X00,0X00,0X0F,  // n
  0XC0,0X20,0X20,0X20,0X20,0XC0,0X07,0X08,0X08,0X08,0X08,0X07,  // o
  0XE0,0X40,0X20,0X20,0X20,0XC0,0X3F,0X04,0X08,0X08,0X08,0X07,  // p
  0XC0,0X20,0X20,0X20,0X40,0XE0,0X07,0X08,0X08,0X08,0X04,0X3F,  // q
  0XE0,0X40,0X20,0X20,0X20,0XC0,0X0F,0X00,0X00,0X00,0X00,0X00,  // r
  0X40,0XA0,0X20,0X20,0X20,0X40,0X04,0X08,0X09,0X09,0X0A,0X04,  // s
  0X20,0X20,0XFC,0X20,0X20,0X00,0X00,0X00,0X07,0X08,0X08,0X04,  // t
  0XE0,0X00,0X00,0X00,0X00,0XE0,0X07,0X08,0X08,0X08,0X04,0X0F,  // u
  0X00,0XE0,0X00,0X00,0X00,0XE0,0X00,0X00,0X03,0X0C,0X03,0X00,  // v
  0X00,0XE0,0X00,0X80,0X00,0XE0,0X00,0X07,0X08,0X07,0X08,0X07,  // w
  0X60,0X80,0X00,0X00,0X80,0X60,0X0C,0X02,0X01,0X01,0X02,0X0C,  // x
  0XE0,0X00,0X00,0X00,0X00,0XE0,0X13,0X24,0X24,0X24,0X22,0X1F,  // y
  0X20,0X20,0X20,0XA0,0X60,0X20,0X08,0X0C,0X0B,0X08,0X08,0X08,  // z
  0X00,0X00,0X80,0X7C,0X02,0X02,0X00,0X00,0X00,0X1F,0X20,0X20,  // braceleft
  0X00,0X00,0X00,0XFE,0X00,0X00,0X00,0X00,0X00,0X3F,0X00,0X00,  // bar
  0X00,0X02,0X02,0X7C,0X80,0X00,0X00,0X20,0X20,0X1F,0X00,0X00,  // braceright
  0X0C,0X02,0X04,0X08,0X10,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,  // asciitilde
  0XFE,0XFE,0XFE,0XFE,0XFE,0XFE,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F   // del
};

void spi_write( unsigned char *dout, int len )
{
    unsigned char *out = dout;
    int towrite;

    /* Assert CS before transfer */
    *AUX_SPI0_CS = 0xB0;  // cs0 low, clear TX RX fifo
    udelay( 1 );

    towrite = len;
    while (towrite) {
        // wait for fifo has space
	if (towrite && (*AUX_SPI0_CS & (1 << 18))) {
	    *AUX_SPI0_FIFO = out ? *out++ : 0;
	    towrite--;
	}
    }
    // wait done
    while ( !(*AUX_SPI0_CS & (1 << 16))) {
        udelay( 1 );
    }

    /* Deassert CS after transfer */
    udelay( 1 );
    *AUX_SPI0_CS = 0x0;   // cs0 high
    udelay( 1 );
}

void ssd1306_init( void )
{
    unsigned char myData[] = {0xa8, 0x3f, 0xd3, 0x0, 0x40, 0xa0, 0xc0, 0xda, 0x2, 0x81, 0x7f, 0xa4, 0xa6, 0xd5, 0x80, 0x8d, 0x14, 0xaf};

    //digitalWrite (DC, 0);
    *GPCLR0 = 0x800000;
    spi_write( myData, 18 );
}

void set_col_addr( int col_start, int col_end )
{
    unsigned char myData[3];

    //digitalWrite (DC, 0) ;
    *GPCLR0 = 0x800000;

    myData[0] = 0x21;
    myData[1] = col_start & 0x7f;
    myData[2] = col_end & 0x7f;
    spi_write( myData, 3 );
}

void set_page_addr( int page_start, int page_end )
{
    unsigned char myData[3];

    //digitalWrite (DC, 0) ;
    *GPCLR0 = 0x800000;

    myData[0] = 0x22;
    myData[1] = page_start & 0x3;
    myData[2] = page_end & 0x3;
    spi_write( myData, 3 );
}

void set_horizontal_mode( void )
{
    unsigned char myData[2];

    //digitalWrite (DC, 0) ;
    *GPCLR0 = 0x800000;

    myData[0] = 0x20;
    myData[1] = 0x00;
    spi_write( myData, 2 );
}

void set_start_page( int page )
{
    unsigned char myData[1];

    //digitalWrite (DC, 0) ;
    *GPCLR0 = 0x800000;

    myData[0] = 0xB0 | (page & 0x3);
    spi_write( myData, 1 );
}

void set_start_col( int col )
{
    unsigned char myData[2];

    //digitalWrite (DC, 0) ;
    *GPCLR0 = 0x800000;

    myData[0] = 0xf & col;
    myData[1] = (0xf & (col >> 4)) | 0x10;
    spi_write( myData, 2 );
}

void clearDisplay( void )
{
  int i;
  int j;
  int k;

  set_col_addr( 0, 127 );
  set_page_addr( 0, 3 );
  //digitalWrite(DC, 1);
  *GPSET0 = 0x800000;
  for (j=0; j<4; j++) {
      for (k=0; k<8; k++) {
          unsigned char myData[16];
          for (i=0; i < 16; i++) {
              myData[i] = 0;
          }
          spi_write( myData, 16 );
      }
  }
}

void oledprintf( unsigned char *ch )
{
  int i;
  int j;
  int start_col;
  int end_col;
  int tmp;
  int tmp1;
  int page2_3;

  start_col = 0;
  page2_3 = 0;

  for (j=0; ch[j] != '\0'; j++) {
      if (ch[j] != '\n' && ch[j] != '\r') {
          unsigned char mychar[12];
          tmp = ch[j] - ' ';
          tmp1 = (tmp << 3) + (tmp << 2);  // tmp x 12
          for (i=0; i< 12; i++) {
              mychar[i] = font7x14[tmp1];
              tmp1++;
          }
          end_col = start_col + 5;
          set_col_addr( start_col, end_col );
          if (page2_3 == 0) {
              set_page_addr( 0, 1 );
          } else {
              set_page_addr( 2, 3 );
          }
          *GPSET0 = 0x800000;
          spi_write( mychar, 12 );
          start_col += 7;
      } else {
          page2_3 = 1;
          start_col = 0;
      }
  }
}

void oledascii( void )
{
  int i;
  int j;
  int k;
  int start_col;
  int end_col;
  int tmp;
  int tmp1;

  for (k=0; k < 3; k++) {
      start_col = 0;
      for (j=0; j < 32; j++) {             // 16 characters per two pages
          unsigned char mychar[12];
          tmp = j + (k << 5);
          tmp1 = (tmp << 3) + (tmp << 2);  // tmp x 12
          for (i=0; i< 12; i++) {
              mychar[i] = font7x14[tmp1];
              tmp1++;
          }
          end_col = start_col + 5;
          set_col_addr( start_col, end_col );
          if (j < 16) {
              set_page_addr( 0, 1 );
          } else {
              set_page_addr( 2, 3 );
          }
          *GPSET0 = 0x800000;
          spi_write( mychar, 12 );
          start_col += 7;
          if ( start_col >= 112 ) {
              start_col = 0;
          }
      }
      udelay( 5000000 );
      clearDisplay();
  }
}

void ssd1306_test ( void )
{
  int i;
  int j;
  unsigned char myData[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};

  *AUX_ENABLES |= 2;                                       // enable SPI0
  *GPFSEL0 = (*GPFSEL0 & ~(0x1ff << 21)) | (0x124 << 21);  // select SPI0
  *GPFSEL1 = (*GPFSEL1 & ~(0x3f << 0)) | (0x24 << 0);      // select SPI0
  *AUX_SPI0_CS = 0x30;      // clear TX RX fifo, CS is 0
  *AUX_SPI0_CLK = 16;       // spi clk is 500 MHz / 16 = 31.25 MHz
  // GPIO23 as output for DC
  *GPFSEL2 = (*GPFSEL2 & ~(0x7 << 9)) | (0x1 << 9);
  ssd1306_init();

  //set_page_mode();
  set_horizontal_mode();
  set_col_addr( 0, 127 );
  set_page_addr( 0, 3 );

  //digitalWrite(DC, 1);
  *GPSET0 = 0x800000;
  for (j=0; j < 4; j++) {
      for (i=0; i < 128; i=i+8) {
          spi_write( myData, 8 );
      }
  }

  udelay( 2000000 );
  clearDisplay();
  oledascii();
  udelay( 2000000 );
  clearDisplay();
  oledprintf( "This is a test !\nIt works !\n");
}
