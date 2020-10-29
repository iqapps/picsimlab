/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2018  Luis Claudio Gambôa Lopes

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

#include"lcd_hd44780.h"
#include<stdio.h>

//#define _DEBUG

const unsigned char LCDfont[224][5] = {
 {0x00, 0x00, 0x00, 0x00, 0x00}, // (space) 
 {0x00, 0x00, 0x5F, 0x00, 0x00}, // ! 
 {0x00, 0x07, 0x00, 0x07, 0x00}, // " 
 {0x14, 0x7F, 0x14, 0x7F, 0x14}, // # 
 {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $ 
 {0x23, 0x13, 0x08, 0x64, 0x62}, // % 
 {0x36, 0x49, 0x55, 0x22, 0x50}, // & 
 {0x00, 0x05, 0x03, 0x00, 0x00}, // ' 
 {0x00, 0x1C, 0x22, 0x41, 0x00}, // ( 
 {0x00, 0x41, 0x22, 0x1C, 0x00}, // ) 
 {0x08, 0x2A, 0x1C, 0x2A, 0x08}, // * 
 {0x08, 0x08, 0x3E, 0x08, 0x08}, // + 
 {0x00, 0x50, 0x30, 0x00, 0x00}, // , 
 {0x08, 0x08, 0x08, 0x08, 0x08}, // - 
 {0x00, 0x30, 0x30, 0x00, 0x00}, // . 
 {0x20, 0x10, 0x08, 0x04, 0x02}, // / 
 {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0 
 {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1 
 {0x42, 0x61, 0x51, 0x49, 0x46}, // 2 
 {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3 
 {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4 
 {0x27, 0x45, 0x45, 0x45, 0x39}, // 5 
 {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6 
 {0x01, 0x71, 0x09, 0x05, 0x03}, // 7 
 {0x36, 0x49, 0x49, 0x49, 0x36}, // 8 
 {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9 
 {0x00, 0x36, 0x36, 0x00, 0x00}, // : 
 {0x00, 0x56, 0x36, 0x00, 0x00}, // ; 
 {0x00, 0x08, 0x14, 0x22, 0x41}, // < 
 {0x14, 0x14, 0x14, 0x14, 0x14}, // = 
 {0x41, 0x22, 0x14, 0x08, 0x00}, // > 
 {0x02, 0x01, 0x51, 0x09, 0x06}, // ? 
 {0x32, 0x49, 0x79, 0x41, 0x3E}, // @ 
 {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A 
 {0x7F, 0x49, 0x49, 0x49, 0x36}, // B 
 {0x3E, 0x41, 0x41, 0x41, 0x22}, // C 
 {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D 
 {0x7F, 0x49, 0x49, 0x49, 0x41}, // E 
 {0x7F, 0x09, 0x09, 0x01, 0x01}, // F 
 {0x3E, 0x41, 0x41, 0x51, 0x32}, // G 
 {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H 
 {0x00, 0x41, 0x7F, 0x41, 0x00}, // I 
 {0x20, 0x40, 0x41, 0x3F, 0x01}, // J 
 {0x7F, 0x08, 0x14, 0x22, 0x41}, // K 
 {0x7F, 0x40, 0x40, 0x40, 0x40}, // L 
 {0x7F, 0x02, 0x04, 0x02, 0x7F}, // M 
 {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N 
 {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O 
 {0x7F, 0x09, 0x09, 0x09, 0x06}, // P 
 {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q 
 {0x7F, 0x09, 0x19, 0x29, 0x46}, // R 
 {0x46, 0x49, 0x49, 0x49, 0x31}, // S 
 {0x01, 0x01, 0x7F, 0x01, 0x01}, // T 
 {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U 
 {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V 
 {0x7F, 0x20, 0x18, 0x20, 0x7F}, // W 
 {0x63, 0x14, 0x08, 0x14, 0x63}, // X 
 {0x03, 0x04, 0x78, 0x04, 0x03}, // Y 
 {0x61, 0x51, 0x49, 0x45, 0x43}, // Z 
 {0x00, 0x00, 0x7F, 0x41, 0x41}, // [
 {0x15, 0x16, 0x7C, 0x16, 0x15}, // Y_ 
 {0x41, 0x41, 0x7F, 0x00, 0x00}, // ] 
 {0x04, 0x02, 0x01, 0x02, 0x04}, // ^ 
 {0x40, 0x40, 0x40, 0x40, 0x40}, // _ 
 {0x00, 0x01, 0x02, 0x04, 0x00}, // ` 
 {0x20, 0x54, 0x54, 0x54, 0x78}, // a 
 {0x7F, 0x48, 0x44, 0x44, 0x38}, // b 
 {0x38, 0x44, 0x44, 0x44, 0x20}, // c 
 {0x38, 0x44, 0x44, 0x48, 0x7F}, // d 
 {0x38, 0x54, 0x54, 0x54, 0x18}, // e 
 {0x08, 0x7E, 0x09, 0x01, 0x02}, // f 
 {0x08, 0x14, 0x54, 0x54, 0x3C}, // g 
 {0x7F, 0x08, 0x04, 0x04, 0x78}, // h 
 {0x00, 0x44, 0x7D, 0x40, 0x00}, // i 
 {0x20, 0x40, 0x44, 0x3D, 0x00}, // j 
 {0x00, 0x7F, 0x10, 0x28, 0x44}, // k 
 {0x00, 0x41, 0x7F, 0x40, 0x00}, // l 
 {0x7C, 0x04, 0x18, 0x04, 0x78}, // m 
 {0x7C, 0x08, 0x04, 0x04, 0x78}, // n 
 {0x38, 0x44, 0x44, 0x44, 0x38}, // o 
 {0x7C, 0x14, 0x14, 0x14, 0x08}, // p 
 {0x08, 0x14, 0x14, 0x18, 0x7C}, // q 
 {0x7C, 0x08, 0x04, 0x04, 0x08}, // r 
 {0x48, 0x54, 0x54, 0x54, 0x20}, // s 
 {0x04, 0x3F, 0x44, 0x40, 0x20}, // t 
 {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u 
 {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v 
 {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w 
 {0x44, 0x28, 0x10, 0x28, 0x44}, // x 
 {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y 
 {0x44, 0x64, 0x54, 0x4C, 0x44}, // z 
 {0x00, 0x08, 0x36, 0x41, 0x00}, // { 
 {0x00, 0x00, 0x7F, 0x00, 0x00}, // | 
 {0x00, 0x41, 0x36, 0x08, 0x00}, // } 
 {0x08, 0x08, 0x2A, 0x1C, 0x08}, // -> 
 {0x08, 0x1C, 0x2A, 0x08, 0x08}, // <- 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty  first block
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty second block
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //empty 
 {0x00, 0x00, 0x00, 0x00, 0x00}, //kanji
 {0x70, 0x50, 0x70, 0x00, 0x00},
 {0x00, 0x00, 0x0F, 0x01, 0x01},
 {0x40, 0x40, 0x78, 0x00, 0x00},
 {0x10, 0x20, 0x40, 0x00, 0x00},
 {0x00, 0x18, 0x18, 0x00, 0x00},
 {0x0A, 0x0A, 0x4A, 0x2A, 0x1E},
 {0x04, 0x44, 0x34, 0x14, 0x0C},
 {0x20, 0x10, 0x78, 0x04, 0x00},
 {0x18, 0x08, 0x4C, 0x48, 0x38},
 {0x48, 0x48, 0x78, 0x48, 0x48},
 {0x48, 0x28, 0x18, 0x7C, 0x08},
 {0x08, 0x7C, 0x08, 0x28, 0x18},
 {0x40, 0x48, 0x48, 0x78, 0x40},
 {0x54, 0x54, 0x54, 0x7C, 0x00},
 {0x1C, 0x00, 0x5C, 0x40, 0x3C},
 {0x08, 0x08, 0x08, 0x08, 0x08},
 {0x01, 0x41, 0x3D, 0x09, 0x07},
 {0x10, 0x08, 0x7C, 0x02, 0x01},
 {0x0E, 0x02, 0x43, 0x22, 0x1E},
 {0x42, 0x42, 0x7E, 0x42, 0x42},
 {0x22, 0x12, 0x0A, 0x7F, 0x02},
 {0x42, 0x3F, 0x02, 0x42, 0x3E},
 {0x0A, 0x0A, 0x7F, 0x0A, 0x0A},
 {0x08, 0x46, 0x42, 0x22, 0x1E},
 {0x04, 0x03, 0x42, 0x3E, 0x02},
 {0x42, 0x42, 0x42, 0x42, 0x7E},
 {0x02, 0x4F, 0x22, 0x1F, 0x02},
 {0x4A, 0x4A, 0x40, 0x20, 0x1C},
 {0x42, 0x22, 0x12, 0x2A, 0x46},
 {0x02, 0x3F, 0x42, 0x4A, 0x46},
 {0x06, 0x48, 0x40, 0x20, 0x1E},
 {0x08, 0x46, 0x4A, 0x32, 0x1E},
 {0x0A, 0x4A, 0x3E, 0x09, 0x08},
 {0x0E, 0x00, 0x4E, 0x20, 0x1E},
 {0x04, 0x45, 0x3D, 0x05, 0x04},
 {0x00, 0x7F, 0x08, 0x10, 0x00},
 {0x44, 0x24, 0x1F, 0x04, 0x04},
 {0x40, 0x42, 0x42, 0x42, 0x40},
 {0x42, 0x2A, 0x12, 0x2A, 0x06},
 {0x22, 0x12, 0x7B, 0x16, 0x22},
 {0x00, 0x40, 0x20, 0x1F, 0x00},
 {0x78, 0x00, 0x02, 0x04, 0x78},
 {0x3F, 0x44, 0x44, 0x44, 0x44},
 {0x02, 0x42, 0x42, 0x22, 0x1E},
 {0x04, 0x02, 0x04, 0x08, 0x30},
 {0x32, 0x02, 0x7F, 0x02, 0x32},
 {0x02, 0x12, 0x22, 0x52, 0x0E},
 {0x00, 0x2A, 0x2A, 0x2A, 0x40},
 {0x38, 0x24, 0x22, 0x20, 0x70},
 {0x40, 0x28, 0x10, 0x28, 0x06},
 {0x0A, 0x3E, 0x4A, 0x4A, 0x4A},
 {0x04, 0x7F, 0x04, 0x14, 0x0C},
 {0x40, 0x42, 0x42, 0x7E, 0x40},
 {0x4A, 0x4A, 0x4A, 0x4A, 0x7E},
 {0x04, 0x05, 0x45, 0x25, 0x1C},
 {0x0F, 0x40, 0x20, 0x1F, 0x00},
 {0x7C, 0x00, 0x7E, 0x40, 0x30},
 {0x7E, 0x40, 0x20, 0x10, 0x08},
 {0x7E, 0x42, 0x42, 0x42, 0x7E},
 {0x0E, 0x02, 0x42, 0x22, 0x1E},
 {0x42, 0x42, 0x40, 0x20, 0x18},
 {0x02, 0x04, 0x01, 0x02, 0x00},
 {0x07, 0x05, 0x07, 0x00, 0x00},
 {0x38, 0x44, 0x48, 0x30, 0x48}, //gre
 {0x20, 0x55, 0x54, 0x55, 0x78},
 {0xF8, 0x54, 0x54, 0x54, 0x28},
 {0x28, 0x54, 0x54, 0x44, 0x20},
 {0xFC, 0x20, 0x20, 0x10, 0x3C},
 {0x38, 0x44, 0x4C, 0x54, 0x24},
 {0xF0, 0x48, 0x44, 0x44, 0x38},
 {0x38, 0x44, 0x44, 0x44, 0xFC},
 {0x20, 0x40, 0x3C, 0x04, 0x04},
 {0x04, 0x04, 0x00, 0x0E, 0x00},
 {0x00, 0x00, 0x04, 0xFD, 0x00},
 {0x0A, 0x04, 0x0A, 0x00, 0x00},
 {0x18, 0x24, 0x7E, 0x24, 0x10},
 {0x14, 0x7F, 0x54, 0x40, 0x40},
 {0x7C, 0x09, 0x05, 0x05, 0x78},
 {0x38, 0x45, 0x44, 0x45, 0x38},
 {0xFC, 0x28, 0x24, 0x24, 0x18},
 {0x38, 0x44, 0x44, 0x48, 0xFC},
 {0x3C, 0x4A, 0x4A, 0x4A, 0x3C},
 {0x30, 0x28, 0x10, 0x28, 0x18},
 {0x58, 0x64, 0x04, 0x64, 0x58},
 {0x3C, 0x41, 0x40, 0x21, 0x7C},
 {0x63, 0x55, 0x49, 0x41, 0x41},
 {0x24, 0x1C, 0x04, 0x3C, 0x24},
 {0x45, 0x29, 0x11, 0x29, 0x45},
 {0x3C, 0x40, 0x40, 0x40, 0xFC},
 {0x14, 0x14, 0x7C, 0x14, 0x12},
 {0x44, 0x3C, 0x14, 0x14, 0x74},
 {0x7C, 0x14, 0x1C, 0x14, 0x7C},
 {0x10, 0x10, 0x54, 0x10, 0x10},
 {0x00, 0x00, 0x00, 0x00, 0x00},
 {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};

void
lcd_cmd(lcd_t * lcd, char cmd)
{
 int i;


 //switch betwwen 8 ou 4 bits communication
 if (!(lcd->flags & L_DL))
  {
   if (lcd->bc)
    {
     lcd->bc = 0;
     cmd = lcd->buff | (((unsigned char) cmd) >> 4);
    }
   else
    {
     lcd->bc = 1;
     lcd->buff = cmd & 0xF0;
     return;
    }
  }
#ifdef _DEBUG
 printf ("LCD cmd=%#04X\n", (unsigned char) cmd);
#endif  

 //Set DDRAM address  
 if (cmd & 0x80)
  {

   i = cmd & 0x7F;

   if (i < 40)
    {
     lcd->addr_counter = i;
    }
   else
    {
     lcd->addr_counter = i - 24;
    }

   if (lcd->addr_counter >= DDRMAX)lcd->addr_counter = 0;
   lcd->addr_mode = LCD_ADDR_DDRAM;

   return;
  }

 //Set CGRAM address
 if (cmd & 0x40)
  {

   lcd->addr_counter = cmd & 0x3F;
   lcd->addr_mode = LCD_ADDR_CGRAM;
   return;
  }

 //Function set 
 if (cmd & 0x20)
  {

   //Sets interface data length
   if (cmd & 0x10)
    {
     lcd->flags |= L_DL;
    }
   else
    {
     lcd->flags &= ~L_DL;
    }

   //Sets number of display line
   if (cmd & 0x08)
    {
     lcd->flags |= L_NLI;
    }
   else
    {
     lcd->flags &= ~L_NLI;
    }

   //Sets character font
   if (cmd & 0x04)
    {
     lcd->flags |= L_FNT;
    }
   else
    {
     lcd->flags &= ~L_FNT;
    }

   return;
  }

 //Cursor/display shift
 if (cmd & 0x10)
  {

   //Sets shift direction  
   if (cmd & 0x04)
    {
     lcd->flags |= L_LR;
    }
   else
    {
     lcd->flags &= ~L_LR;
    }

   //Sets cursor-move or display-shift  
   if (cmd & 0x08)
    {
     //display shift   
     lcd->flags |= L_CD;

     if (lcd->flags & L_LR)
      {
       lcd->shift++;
       if (lcd->shift > 40)lcd->shift = lcd->shift - 40;
      }
     else
      {
       lcd->shift--;
       if (lcd->shift < -40)lcd->shift = lcd->shift + 40;
      }
    }
   else
    {
     //cursor move   
     lcd->flags &= ~L_CD;

     if (lcd->flags & L_LR)
      lcd->addr_counter++;
     else
      lcd->addr_counter--;
    }

   lcd->update = 1;
   return;
  }

 //Display On/Off control
 if (cmd & 0x08)
  {
   //Sets On/Off of all display
   if (cmd & 0x04)
    {
     lcd->flags |= L_DON;
    }
   else
    {
     lcd->flags &= ~L_DON;
    }

   //Sets cursor On/Off 
   if (cmd & 0x02)
    {
     lcd->flags |= L_CON;
    }
   else
    {
     lcd->flags &= ~L_CON;
    }

   //Set blink of cursor position character    
   if (cmd & 0x01)
    {
     lcd->flags |= L_CBL;
    }
   else
    {
     lcd->flags &= ~L_CBL;
    }

   lcd->update = 1;
   return;
  }


 //Entry mode set
 if (cmd & 0x04)
  {

   //Sets cursor move direction    
   if (cmd & 0x02)
    {
     lcd->flags |= L_DID;
    }
   else
    {
     lcd->flags &= ~L_DID;
    }

   //specifies to shift the display  
   if (cmd & 0x01)
    {
     lcd->flags |= L_DSH;
    }
   else
    {
     lcd->flags &= ~L_DSH;
    }

   return;
  }

 //Cursor home 
 if (cmd & 0x02)
  {
   lcd->addr_counter = 0;
   lcd->shift = 0;
   lcd->update = 1;
   return;
  }


 //Clear display
 if (cmd & 0x01)
  {
   memset (lcd->ddram_char, ' ', DDRMAX);
   lcd->addr_counter = 0;
   lcd->shift = 0;
   lcd->flags |= L_DID;
   lcd->update = 1;
   return;
  }

}

void
lcd_data(lcd_t * lcd, char data)
{
 int j;

 if (!(lcd->flags & L_DON))
  {
   lcd_cmd (lcd, data);
   return;
  }

 //switch betwwen 8 ou 4 bits communication
 if (!(lcd->flags & L_DL))
  {
   if (lcd->bc)
    {
     lcd->bc = 0;
     data = lcd->buff | (((unsigned char) data) >> 4);
    }
   else
    {
     lcd->bc = 1;
     lcd->buff = data & 0xF0;
     return;
    }
  }


 /*
 if(data < 0x20)
 {
   printf("LCD dat=ERROR!\n");
   return;
 }
  */

#ifdef _DEBUG
 printf ("LCD dat=%#04X  (%c)\n", (unsigned char) data, data);
#endif
 if (lcd->addr_mode == LCD_ADDR_DDRAM)
  {
   lcd->ddram_char[lcd->addr_counter] = data;

   if (lcd->flags & L_DID)
    {
     lcd->addr_counter++;
     if (lcd->addr_counter >= DDRMAX)lcd->addr_counter = 0;
     if (lcd->flags & L_DSH)
      {
       lcd->shift--;
       if (lcd->shift < -40)lcd->shift = lcd->shift + 40;
      }
    }
   else
    {
     lcd->addr_counter--;
     if (lcd->addr_counter >= DDRMAX)lcd->addr_counter = DDRMAX - 1;
     if (lcd->flags & L_DSH)
      {
       lcd->shift++;
       if (lcd->shift > 40)lcd->shift = lcd->shift - 40;
      }
    }


   lcd->update = 1;
  }
 else
  {
   lcd->cgram_char[lcd->addr_counter >> 3] = data;
   for (j = 0; j < 5; j++)
    {
     if ((data & (0x01 << (4 - j))) > 0)
      {
       lcd->cgram[lcd->addr_counter >> 3][j] |= (0x01 << (lcd->addr_counter & 0x07));
      }
     else
      {
       lcd->cgram[lcd->addr_counter >> 3][j] &= ~(0x01 << (lcd->addr_counter & 0x07));
      }
    }
   if (lcd->flags & L_DID)
    {
     lcd->addr_counter++;
     if (lcd->addr_counter >= 64)lcd->addr_counter = 0;
    }
   else
    {
     lcd->addr_counter--;
     if (lcd->addr_counter >= 64)lcd->addr_counter = 63;
    }
    lcd->update = 1;
  }

}

unsigned char
lcd_read_busyf_acounter(lcd_t * lcd)
{
 //busy flag aways 0
 return (0x7F & lcd->addr_counter);
}

char
lcd_read_data(lcd_t * lcd)
{
 char ret;

 if (lcd->addr_mode == LCD_ADDR_DDRAM)
  {
   ret = lcd->ddram_char[lcd->addr_counter];
   if (lcd->flags & L_DID)
    {
     lcd->addr_counter++;
     if (lcd->addr_counter >= DDRMAX)lcd->addr_counter = 0;
    }
   else
    {
     lcd->addr_counter--;
     if (lcd->addr_counter >= DDRMAX)lcd->addr_counter = DDRMAX - 1;
    }

  }
 else
  {
   ret = lcd->cgram_char[lcd->addr_counter];
   if (lcd->flags & L_DID)
    {
     lcd->addr_counter++;
     if (lcd->addr_counter >= 64)lcd->addr_counter = 0;
    }
   else
    {
     lcd->addr_counter--;
     if (lcd->addr_counter >= 64)lcd->addr_counter = 63;
    }
  }

 return ret;
}

void
lcd_rst(lcd_t * lcd)
{
 int i, j;

#ifdef _DEBUG
 printf ("LCD rst--------------------------\n");
#endif

 for (i = 0; i < 8; i++)
  {
   for (j = 0; j < 5; j++)
    {
     lcd->cgram[i][j] = 0;
    }
  }

 memset (lcd->ddram_char, ' ', DDRMAX);
 memset (lcd->cgram_char, 0, 64);

 lcd->addr_counter = 0;
 lcd->addr_mode = LCD_ADDR_DDRAM;
 lcd->update = 1;
 lcd->bc = 0;

 lcd->blink = 0;
 lcd->blinkc = 0;
 lcd->shift = 0;
 lcd->flags = L_DL | L_DID;
 return;
}

void
lcd_init(lcd_t * lcd, unsigned char cnum, unsigned char lnum)
{
 if ((cnum > 15)&&(cnum <= 20))
  lcd->cnum = cnum;
 else
  lcd->cnum = 16;

 if ((lnum > 0)&&(lnum <= 4))
  lcd->lnum = lnum;
 else
  lcd->lnum = 2;
 lcd->update = 1;
}

void
lcd_on(lcd_t * lcd, int onoff)
{
 if (onoff == 1)
  {
   lcd->flags = 0;
  };
 lcd_rst (lcd);
}

void
lcd_blink(lcd_t * lcd)
{
 if ((lcd->flags & L_CON)&&(lcd->flags & L_CBL))
  {
   lcd->blinkc++;
   if (lcd->blinkc > 4)
    {
     lcd->blinkc = 0;
     lcd->update = 1;
     lcd->blink ^= 1;
    }
  }
 else
  lcd->blink = 0;
}

void
lcd_draw(lcd_t * lcd, CCanvas * canvas, int x1, int y1, int w1, int h1, int picpwr)
{
 int l, c, x, y;
 int loff = 0;
 int w;

 if (lcd->cnum == 16)
  w = w1;
 else
  w = (int) (w1 * 1.25);

 if (lcd->lnum == 2)
  canvas->Rectangle (1, x1, y1, w, h1);
 else
  canvas->Rectangle (1, x1, y1, w, (h1 * 2) - 14);
 lcd->update = 0;


 for (l = 0; l < lcd->lnum; l++)
  {
   switch (l)
    {
    case 0:
     loff = 0;
     break;
    case 1:
     loff = 40;
     break;
    case 2:
     loff = lcd->cnum;
     break;
    case 3:
     loff = 40 + lcd->cnum;
     break;
    }
   for (c = 0; c < lcd->cnum; c++)
    {
     for (x = 0; x < 5; x++)
      {
       for (y = 0; y < 8; y++)
        {
         int cs = c - lcd->shift;
         if (cs < 0) cs = 40 + (cs % 40);
         if (cs >= 40)cs = cs % 40;
         char ram;
         int fp = ((unsigned char) lcd->ddram_char[(cs + loff) % DDRMAX]);

         if (fp >= 0x20)
          {
           ram=LCDfont[fp-0x20][x];
          }
         else
          {
           ram=lcd->cgram[fp & 0x07][x];
          }
         if ((ram & (0x01 << y))&& (lcd->flags & L_DON))
          {
           canvas->SetFgColor (0, 35, 0);
           canvas->SetColor (0, 35, 0);
          }
         else
          {
           canvas->SetFgColor (0, 90 * picpwr + 35, 0);
           canvas->SetColor (0, 90 * picpwr + 35, 0);
          }
         //          canvas.Rectangle (1, output[i].x1+12+(x*4)+(c*22), output[i].y1+8+(y*4)+(l*38), 4,4 );
         canvas->Rectangle (1, x1 + 2 + (x * 4)+(c * 23), y1 + 10 + (y * 4)+(l * 35), 4, 4);
        }
      }
    }
  }

 //cursor  
 if ((lcd->flags & L_DON)&&(lcd->flags & L_CON))
  {
   if (lcd->addr_counter < 40)
    {
     l = 0;
     c = (lcd->addr_counter + lcd->shift);
    }
   else
    {
     l = 1;
     c = lcd->addr_counter - 40 + lcd->shift;
    }

   if (c < 0) c = 40 + (c % 40);
   if (c >= 40)c = c % 40;


   if ((c >= 0)&& (c < lcd->cnum)) //draw only visible columns
    {
     canvas->SetFgColor (0, 35, 0);
     canvas->SetColor (0, 35, 0);

     if (lcd->blink)
      canvas->Rectangle (1, x1 + 2 + (c * 23), y1 + 10 + (l * 35), 20, 32);
     else
      canvas->Rectangle (1, x1 + 2 + (c * 23), y1 + 38 + (l * 35), 20, 4);
    }
  }

}
