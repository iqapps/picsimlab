/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2015  Luis Claudio Gambôa Lopes

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

#ifndef PART_LEDS_H
#define	PART_LEDS_H

#include<lxrad/lxrad.h>
#include"part.h"


class cpart_leds:public part
{
   public:
      String GetName(void){return wxT("LEDs");};
      cpart_leds(unsigned x, unsigned y);
      ~cpart_leds(void);
      void Draw(void);
      String GetPictureFileName(void){return wxT("parts/LEDs.png");};
      String GetInputMapFile(void){return wxT("parts/LEDs_i.map");};
      String GetOutputMapFile(void){return wxT("parts/LEDs_o.map");};
      String GetPropiertiesWindowFile(void){return wxT("parts/LEDs.lxrad");};
      void ConfigurePropiertsWindow(CPWindow *  wprop);
      void ReadPropiertsWindow(void);
      String WritePreferences(void);
      void ReadPreferences(String value);
      unsigned short get_in_id(char * name);
      unsigned short get_out_id(char * name);
      void PropButton (CControl * control, uint button, uint x, uint y, uint state);
    private:
      unsigned char input_pins[8];    
};




#endif	/* PART_LEDS */

