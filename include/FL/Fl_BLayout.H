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

#ifndef FL_BLAYOUT_H
#define FL_BLAYOUT_H

#include <FL/Fl_Tile.H>

class Fl_BLayout: public Fl_Tile
{
   public:

   Fl_BLayout(int X, int Y, int W, int H,const char* L=""):Fl_Tile(X,Y,W,H,L) {}
   Fl_Widget *tree;
   Fl_Widget *viewer;
   Fl_Widget *utility;
   Fl_Widget *command_prompt;

   void resize(int X, int Y, int W, int H)
   {  
      //Fl_Group::resize(X,Y,W,H);
      // If for some reason we couldn't ID one of the panels, just do
      // the default resize
      if (! tree || !viewer || !utility || !command_prompt) {
         Fl_Group::resize(X,Y,W,H);
         return;
      }

      // If the proposed width is smaller than the combined width of the 
      // tree and the utility panel, fall back on default.
      int new_width;
      if (W < tree->w() + utility->w() + 15) {
         Fl_Group::resize(X,Y,W,H);
         return;
      } 

      // If the proposed height is smaller than the height of the 
      // command prompt, fall back on default.
      int new_height;
      if (H < command_prompt->h() + 15) {
         Fl_Group::resize(X,Y,W,H);
         return;
      }

      // Find out what deltas we need to deal with
      int dx = X-x();
      int dy = Y-y();
      int dw = W-w();
      int dh = H-h();

      // resize this (skip the Fl_Group resize):
      Fl_Widget::resize(X,Y,W,H);

      // Viewer takes resize
      tree->resize(tree->x() + dx, tree->y() + dy, tree->w(), tree->h() + dh);
      utility->resize(utility->x() + dx + dw, utility->y() + dy, utility->w(), utility->h() + dh);
      command_prompt->resize(command_prompt->x() + dx, command_prompt->y() + dy + dh, command_prompt->w() + dw, command_prompt->h());
      viewer->resize(viewer->x() + dx, viewer->y() + dy, viewer->w() + dw, viewer->h() + dh);
   }
};

#endif
