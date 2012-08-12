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
#include "FL/Fl_BGroup.H"
#include "FL/Fl_GTree.H"
#include "FL/Fl_BLayout.H"

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

void PopulateTree(Fl_Tree *tree) {
    tree->add("Aaa/Bbb/Ccc/Ddd/Eeeeeeeeeeee/Fff/0001");
    tree->add("Aaa/Bbb/Ccc/Ddd/Eeeeeeeeeeee/Fff/0002");
    tree->add("Aaa/Bbb/Ccc/Ddd/Eeeeeeeeeeee/Fff/0003");
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


    Fl_BLayout layout_manager(0, menu_height*2 ,window_default_width,window_default_height - menu_height*2);             layout_manager.tree = new Fl_GTree(0, menu_height*2 ,tree_width,window_default_height-menu_height*2-console_height);
      layout_manager.tree->begin();
        PopulateTree(layout_manager.tree);
      layout_manager.tree->end();

      layout_manager.panel_g = new Fl_BGroup(window_default_width - panel_width,menu_height*2,panel_width,window_default_height-menu_height*2-console_height);
      layout_manager.panel_g->begin();
        Fl_Group p_panel(window_default_width - panel_width,menu_height*2,window_default_width,window_default_height-menu_height*2-console_height);
          p_panel.box(FL_DOWN_BOX);
          p_panel.color(FL_GRAY);

          Fl_Choice *opbox = new Fl_Choice(window_default_width -panel_width+3,menu_height*2+20,panel_width-3,23, "Operation:");
          opbox->down_box(FL_BORDER_BOX);
          opbox->align(Fl_Align(FL_ALIGN_TOP_LEFT));
          opbox->menu(opbox_menu);

        p_panel.end();
      layout_manager.panel_g->end();

      layout_manager.viewer_g = new Fl_BGroup(tree_width,menu_height*2,window_default_width-tree_width-panel_width,window_default_height-menu_height*2-console_height);
      layout_manager.viewer_g->begin();
        Fl_Group v_box(tree_width,menu_height*2,window_default_width-tree_width-panel_width,window_default_height-menu_height*2-console_height);
          v_box.box(FL_DOWN_BOX);
          v_box.color(FL_BLACK);
        v_box.end();
      layout_manager.viewer_g->end();

      layout_manager.console_g = new Fl_BGroup(0,window_default_height - console_height,window_default_width,console_height, 0);
      layout_manager.console_g->begin();
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
      layout_manager.console_g->end();
      //Fl_Box *layout_manager_resize_limit = new Fl_Box(FL_NO_BOX, 5, 5, WIDTH-5, window_default_height-5, 0);
    layout_manager.resizable(layout_manager);
    layout_manager.end();
  window.resizable(layout_manager);
  window.end();
  window.size_range(300,300);
  window.show(argc, argv);
  return Fl::run();
}

//
// End of "$Id: menubar.cxx 7903 2010-11-28 21:06:39Z matt $".
//
