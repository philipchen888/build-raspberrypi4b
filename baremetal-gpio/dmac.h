/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _DMAC_H
#define _DMAC_H

#include "registers.h"

#define DMA_CB_DEST_INC (1<<4)
#define DMA_CB_SRC_INC  (1<<8)

struct DMA_CB {
    unsigned int ti;         // Transfer info
    unsigned int srce_ad;    // Source address
    unsigned int dest_ad;    // Destination address
    unsigned int tfr_len;    // Transfer length
    unsigned int stride;     // Transfer stride
    unsigned int next_cb;    // Next control block
    unsigned int debug;      // Debug register
    unsigned int unused;
} __attribute__((aligned(64)));

unsigned int randomized( unsigned int i );
void dmac_test( void );

#endif
