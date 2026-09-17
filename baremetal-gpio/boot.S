/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#define PAGE_SHIFT                      12
#define TABLE_SHIFT                     9
#define SECTION_SHIFT                   (PAGE_SHIFT + TABLE_SHIFT)
#define SECTION_SIZE                    (1 << SECTION_SHIFT)
#define LOW_MEMORY                      (2 * SECTION_SIZE)

.section ".text.boot"

.globl _start
_start:
    mrs    x0, mpidr_el1        
    and    x0, x0,#0xFF        // Check processor id
    cbz    x0, master        // Hang for all non-primary CPU
    b    proc_hang

proc_hang: 
    b proc_hang

master:
    adr    x0, bss_begin
    adr    x1, bss_end
    sub    x1, x1, x0
    bl     memzero

    mov    sp, #LOW_MEMORY
    bl     main

memzero:
	str xzr, [x0], #8
	subs x1, x1, #8
	b.gt memzero
	ret
