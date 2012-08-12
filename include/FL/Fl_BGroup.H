// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.

#ifndef FL_BGROUP_H
#define FL_BGROUP_H

#include <FL/Fl_Group.H>

class Fl_BGroup: public Fl_Group
{
   public:

   Fl_BGroup(int X, int Y, int W, int H,const char* L=""):Fl_Group(X,Y,W,H,L) {}

   void resize(int X, int Y, int W, int H)
   {  // Don't permit dimensions below a certain point.
      int width; int height; if (W < 5) {
        width = 5;
      } else {
        width = W;
      }
      if (H < 5) {
        height = 5;
      } else {
        height = H;
      }
      Fl_Group::resize(X,Y,width,height);
   }
};

#endif
