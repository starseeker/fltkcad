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

#include <FL/Fl_BGroup.H>
#include <FL/Fl_GTree.H>
#include <FL/Fl_Tile.H>

class Fl_BLayout: public Fl_Tile
{
   public:

   Fl_BLayout(int X, int Y, int W, int H,const char* L=""):Fl_Tile(X,Y,W,H,L) {}
   Fl_GTree *tree;
   Fl_BGroup *viewer_g;
   Fl_BGroup *panel_g;
   Fl_BGroup *console_g;

   void resize(int X, int Y, int W, int H)
   {  
      //Fl_Group::resize(X,Y,W,H);
      // If for some reason we couldn't ID one of the panel_gs, just do
      // the default resize
      if (! tree || !viewer_g || !panel_g || !console_g) {
         Fl_Group::resize(X,Y,W,H);
         return;
      }

      // If the proposed width is smaller than the combined width of the 
      // tree and the panel_g, fall back on default.
      int new_width;
      if (W < tree->w() + panel_g->w() + 15) {
         Fl_Group::resize(X,Y,W,H);
         return;
      } 

      // If the proposed height is smaller than the height of the 
      // command prompt, fall back on default.
      int new_height;
      if (H < console_g->h() + 15) {
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
      panel_g->resize(panel_g->x() + dx + dw, panel_g->y() + dy, panel_g->w(), panel_g->h() + dh);
      console_g->resize(console_g->x() + dx, console_g->y() + dy + dh, console_g->w() + dw, console_g->h());
      viewer_g->resize(viewer_g->x() + dx, viewer_g->y() + dy, viewer_g->w() + dw, viewer_g->h() + dh);
   }
};

#endif
