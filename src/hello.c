/*
 * Copyright (c) 2023 Rumbledethumps
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "rp6502.h"



// i just started editing the brot32.c file 

// This version optimized for fixed point math on 8-bit processors
typedef int32_t fint32_t;

#define WIDTH 320
#define HEIGHT 180 // 180 or 240

static void vmode(uint16_t data)
{
    xreg(data, 0, 1);
}

static void erase()
{
    // Partially unrolled loop is FAST
    unsigned i = 0;
    RIA_ADDR0 = 0;
    RIA_STEP0 = 1;
    for (i = 0x1300; --i;)
    {
        RIA_RW0 = 255;
        RIA_RW0 = 255;
        RIA_RW0 = 255;
        RIA_RW0 = 255;
        RIA_RW0 = 255;
        RIA_RW0 = 255;
        RIA_RW0 = 255;
        RIA_RW0 = 255;
    }
    RIA_ADDR0 = 0;
    for (i = 0x1300; --i;)
    {
        RIA_RW0  = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
        RIA_RW0 = 0;
    }
    RIA_ADDR0 = 0;
}

static void wait()
{
    FILE *input;
    uint8_t discard;
    discard = RIA_RX;
    while (RIA_RX_READY)
        discard = RIA_RX;
    while (!(RIA_RX_READY))
        ;
    discard = RIA_RX;
}

void main()
{
FILE * input;
int8_t pixel;
#if (HEIGHT == 180)
   vmode(2);
#else
  //  vmode(1);
#endif
   // wait();
    erase();
    RIA_ADDR0 = 0;
    RIA_STEP0 = 1;

    input = fopen("image.bin","rb");
    while (!feof(input)) 
    {
     fread(&pixel,1,1,input);
     RIA_RW0 = pixel;
     }
 while(1){};
}