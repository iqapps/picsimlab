/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */


#ifndef UART
#define UART

#include <stdio.h>
#include "../serial_port.h"


typedef struct {
    unsigned char connected;
    unsigned char arx;
    unsigned short insr;
    unsigned short outsr;
    unsigned int bcr;
    unsigned long tcountr;
    unsigned int bcw;
    unsigned long tcountw;
    serialfd_t serialfd;
    unsigned long speed;
    unsigned int count;
    unsigned int rxc;
    unsigned int leds;
} uart_t;


void uart_rst(uart_t *sr);
void uart_init(uart_t *sr);
void uart_end(uart_t *sr);
void uart_set_clk(uart_t *sr, unsigned long clk);
void uart_set_port(uart_t *sr,const char * port, unsigned int speed);

unsigned char uart_io(uart_t *sr, unsigned char rx);

#endif //UART

