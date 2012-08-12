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

#ifndef FL_GTREE_H
#define FL_GTREE_H

#include <FL/Fl_Tree.H>

class Fl_GTree: public Fl_Tree
{
   public:

   Fl_GTree(int X, int Y, int W, int H,const char* L=""):Fl_Tree(X,Y,W,H,L) {}

   void resize(int X, int Y, int W, int H)
   {  // Don't permit dimensions below a certain point.
      int width;
      int height;
      int limit = 2;
      if (W < limit) {
        width = limit;
      } else {
        width = W;
      }
      if (H < limit) {
        height = limit;
      } else {
        height = H;
      }
      Fl_Tree::resize(X,Y,width,height);
   }
};

#endif
