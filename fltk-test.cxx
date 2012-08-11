//
// "$Id: menubar.cxx 7903 2010-11-28 21:06:39Z matt $"
//
// Menubar test program for the Fast Light Tool Kit (FLTK).
//
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
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
//#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>


static const char *x_xpm[] = {                       // this is a .xpm file
"14 14 2 1",
"       c None",
"x      c #585858",
"              ",
"    xxxxx     ",
"  xxxxxxxxx   ",
"  xxxxxxxxx   ",
" xx  xxx  xx  ",
" xxx  x  xxx  ",
" xxxx   xxxx  ",
" xxxx   xxxx  ",
" xxx  x  xxx  ",
" xx  xxx  xx  ",
"  xxxxxxxxx   ",
"  xxxxxxxxx   ",
"    xxxxx     ",
"              "};

class MinSizeGroup: public Fl_Group
{
   public:

   MinSizeGroup(int X, int Y, int W, int H,const char* L=""):Fl_Group(X,Y,W,H,L) {}

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

class MinSizeTree: public Fl_Tree
{
   public:

   MinSizeTree(int X, int Y, int W, int H,const char* L=""):Fl_Tree(X,Y,W,H,L) {}

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


// Because we're using a particular window structure in our custom tile, we
// use some tricks to resize in a manner specific to our GUI layout.
class ResizeAllTile: public Fl_Tile
{
   public:

   ResizeAllTile(int X, int Y, int W, int H,const char* L=""):Fl_Tile(X,Y,W,H,L) {}
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


Fl_Menu_Item menuitems[] = {
  {"&File",0,0,0,FL_SUBMENU},
  {"New",       FL_ALT+'n'},
  {0},
  {0}
};

Fl_Menu_Item helpitems[] = {
  {"&Help",0,0,0,FL_SUBMENU},
  {"About",       FL_ALT+'a'},
  {0},
  {0}
};

Fl_Menu_Item opbox_menu[] = {
  {"Az/El/T"},
  {"dx/dy/dz"},
  {"Tx/Ty/Tz"},
  {0},
  {0}
};

void PopulateTree(Fl_Tree& tree) {
    tree.add("Aaa/Bbb/Ccc/Ddd/Eeeeeeeeeeee/Fff/0001");
    tree.add("Aaa/Bbb/Ccc/Ddd/Eeeeeeeeeeee/Fff/0002");
    tree.add("Aaa/Bbb/Ccc/Ddd/Eeeeeeeeeeee/Fff/0003");
}

int main(int argc, char **argv) {

  int window_default_width = 800;
  int window_default_height = 700;

  int menu_height = fl_height(FL_HELVETICA, 14) + 10;
  fl_font(FL_HELVETICA, 14);

  int tree_width = (int)(menu_height * 6);
  int panel_width = (int)(menu_height * 6);
  int help_width = (int)(fl_width("Help") * 1.8);

  int console_height = (int)(menu_height * 5);
  
  Fl_Window window(window_default_width, window_default_height);
    Fl_Group *menugrp = new Fl_Group(0, 0, window_default_width, menu_height);           
      Fl_Box *menu_resize_limit = new Fl_Box(FL_NO_BOX, menu_height, 0, menu_height, 100, 0);
      Fl_Menu_Bar *mbar = new Fl_Menu_Bar(0,0,window_default_width-help_width, menu_height); 
      mbar->menu(menuitems);
      Fl_Menu_Bar *hbar = new Fl_Menu_Bar(window_default_width-help_width,0,window_default_width, menu_height); 
      hbar->menu(helpitems);
      menugrp->resizable(menu_resize_limit);
    menugrp->end();

    Fl_Group *buttongrp = new Fl_Group(0, menu_height, window_default_width, menu_height);           
      Fl_Box *button_resize_limit = new Fl_Box(FL_NO_BOX, menu_height*2, 0, menu_height*2, 100, 0);
      Fl_Box *button_container = new Fl_Box(FL_FRAME_BOX, 0, menu_height, window_default_width, menu_height, 0);
      Fl_Button b1(5, menu_height + 1, menu_height -2, menu_height - 2);
      Fl_Pixmap x(x_xpm);
      b1.image(x);
      b1.align(FL_ALIGN_INSIDE|FL_ALIGN_CENTER); 
      buttongrp->resizable(button_resize_limit);
    buttongrp->end();


    ResizeAllTile tile(0, menu_height*2 ,window_default_width,window_default_height - menu_height*2);                        

      MinSizeTree tree(0, menu_height*2 ,tree_width,window_default_height-menu_height*2-console_height);
        PopulateTree(tree);
      tree.end();
      tile.tree = &tree;

      MinSizeGroup panel_wrap(window_default_width - panel_width,menu_height*2,panel_width,window_default_height-menu_height*2-console_height);
      Fl_Group panel(window_default_width - panel_width,menu_height*2,window_default_width,window_default_height-menu_height*2-console_height);
        panel.box(FL_DOWN_BOX);
        panel.color(FL_WHITE);

        Fl_Choice *opbox = new Fl_Choice(window_default_width -panel_width+3,menu_height*2+20,panel_width-3,23, "Operation:");
        opbox->down_box(FL_BORDER_BOX);
        opbox->align(Fl_Align(FL_ALIGN_TOP_LEFT));
        opbox->menu(opbox_menu);

      panel.end();
      panel_wrap.end();
      tile.utility = &panel_wrap; 

      MinSizeGroup view_wrap(tree_width,menu_height*2,window_default_width-tree_width-panel_width,window_default_height-menu_height*2-console_height);
      Fl_Group viewer(tree_width,menu_height*2,window_default_width-tree_width-panel_width,window_default_height-menu_height*2-console_height);
        viewer.box(FL_DOWN_BOX);
        viewer.color(FL_GRAY);
      viewer.end();
      view_wrap.end();
      tile.viewer = &view_wrap;

      MinSizeGroup console_wrap(0,window_default_height - console_height,window_default_width,console_height, 0);
      Fl_Group console(0,window_default_height - console_height,window_default_width,console_height, 0);
        console.box(FL_DOWN_BOX);
        console.color(FL_GRAY);
        Fl_Text_Buffer *textbuf = new Fl_Text_Buffer(20);
        Fl_Text_Editor *editor = new Fl_Text_Editor(0,window_default_height - console_height,window_default_width,console_height);
        editor->textfont(FL_COURIER); 
        editor->textsize(14);
        editor->buffer(textbuf);
        console.resizable(editor);
      console.end();
      console_wrap.end();
      tile.command_prompt = &console_wrap;
      //Fl_Box *tile_resize_limit = new Fl_Box(FL_NO_BOX, 5, 5, WIDTH-5, window_default_height-5, 0);
    tile.resizable(tile);
    tile.end();
  window.resizable(tile);
  window.end();
  window.size_range(300,300);
  window.show(argc, argv);
  return Fl::run();
}

//
// End of "$Id: menubar.cxx 7903 2010-11-28 21:06:39Z matt $".
//
