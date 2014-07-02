//
// "$Id: print_panel.h 10149 2014-05-17 20:46:25Z greg.ercolano $"
//
// FLUID print panel for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// generated by Fast Light User Interface Designer (fluid) version 1.0302

#ifndef print_panel_h
#define print_panel_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *print_panel;
#include <FL/Fl_Group.H>
extern Fl_Group *print_panel_controls;
#include <FL/Fl_Choice.H>
extern Fl_Choice *print_choice;
#include <FL/Fl_Button.H>
extern Fl_Button *print_properties;
#include <FL/Fl_Box.H>
extern Fl_Box *print_status;
#include <FL/Fl_Round_Button.H>
extern Fl_Round_Button *print_all;
extern Fl_Round_Button *print_pages;
extern Fl_Round_Button *print_selection;
#include <FL/Fl_Int_Input.H>
extern Fl_Int_Input *print_from;
extern Fl_Int_Input *print_to;
#include <FL/Fl_Spinner.H>
extern Fl_Spinner *print_copies;
#include <FL/Fl_Check_Button.H>
extern Fl_Check_Button *print_collate_button;
extern Fl_Group *print_collate_group[2];
#include <FL/Fl_Return_Button.H>
extern void print_cb(Fl_Return_Button*, void*);
#include <FL/Fl_Progress.H>
extern Fl_Progress *print_progress;
extern Fl_Double_Window *print_properties_panel;
extern Fl_Choice *print_page_size;
extern Fl_Button *print_output_mode[4];
Fl_Double_Window* make_print_panel();
extern Fl_Menu_Item menu_print_page_size[];
extern void print_cb(Fl_Return_Button *, void *); 
void print_load();
void print_update_status();
#endif

//
// End of "$Id: print_panel.h 10149 2014-05-17 20:46:25Z greg.ercolano $".
//
