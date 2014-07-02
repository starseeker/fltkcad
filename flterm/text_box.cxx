/************************************************************************/
// compile as:
// fltk-config --compile text_box.cxx

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
//#include <FL/fl_ask.H>

#include "gterm.hpp"

static char lines[GT_MAXHEIGHT][GT_MAXWIDTH]; // ASCII text
static char style[GT_MAXHEIGHT][GT_MAXWIDTH]; // char colour buffer

int col_table[] = 
{	FL_BLACK,
	FL_BLUE,
	FL_CYAN,
	FL_DARK_BLUE,
	FL_DARK_CYAN,
	FL_DARK_GREEN,
	FL_DARK_MAGENTA,
	FL_DARK_RED,
	FL_DARK_YELLOW,
	FL_GREEN,
	FL_MAGENTA,
	FL_RED,
	FL_YELLOW,
	FL_WHITE };

/************************************************************************/
class text_box : public Fl_Box
{
protected:
	void draw(void);

public:
     text_box(int X, int Y, int W, int H, const char *L=0) : Fl_Box(X,Y,W,H,L) { }
};
/************************************************************************/
void text_box::draw(void)
{
	int line = 0;
	int wd = w() - 4;
	int ht = h() - 4;

	int xo = x() + 2;
	int yo = y() + 2;

	Fl_Box::draw();
	fl_push_clip(xo, yo, wd, ht);

	fl_color(FL_WHITE);
	fl_rectf(xo, yo, wd, ht);

	fl_font(FL_COURIER, 15);
	int fh = fl_height();
	float cw = fl_width("MHW#i1l") / 7; // get an average char width, in case of Prop Fonts!
	int lx = xo + 2;
	int ly = yo + fh;

	char str[4]; str[1] = 0;
	while ((line < GT_MAXHEIGHT) && (ly < ht))
	{
		int pos = 0;
		float fpos = (float)lx;
		int px = lx;
		while((lines[line][pos] != 0) && (pos < GT_MAXWIDTH))
		{
			str[0] = lines[line][pos];
			fl_color(col_table[style[line][pos]]);
			fl_draw(str, px, ly);
			fpos = fpos + cw;
			px = (int)fpos;
			pos = pos + 1;
			if (px >= wd)
				break;
		}
		line = line + 1;
		ly = ly + fh;
	}
	
	fl_pop_clip();
} /* end of draw() method */

/************************************************************************/
Fl_Double_Window *main_win = NULL;
text_box *terminal;

/************************************************************************/
void quit_cb(Fl_Button *, void *)
{
	main_win->hide();
}

/************************************************************************/
int main(int argc, char **argv)
{
	int idx = 0;
	
	Fl::get_system_colors();

	memset(lines, 0, sizeof(lines));
	for(int i = 0; i < GT_MAXHEIGHT; i++)
	{
		for(int j = 0; j < GT_MAXWIDTH; j++)
		{
			style[i][j] = idx % 13;
			idx ++;
		}
		strncpy(lines[i], "This is the test text string!", GT_MAXWIDTH);
	}
	strncpy(lines[4], "This is the very very long line test text string! MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXXXXXXX", GT_MAXHEIGHT);
	
	
	main_win = new Fl_Double_Window(522, 470);
	main_win->begin();

	terminal = new text_box(5, 5, 512, 412);
	terminal->box(FL_DOWN_BOX);

	Fl_Group * but_grp = new Fl_Group(5, 420, 512, 40);
	but_grp->begin();
	but_grp->box(FL_ENGRAVED_BOX);

	Fl_Button *dummy = new Fl_Button(6, 422, 2, 2);
	dummy->box(FL_NO_BOX);
	dummy->clear_visible_focus();

	Fl_Button *quit = new Fl_Button(452, 425, 60, 30);
	quit->label("Quit");
	quit->box(FL_THIN_UP_BOX);
	quit->callback((Fl_Callback *)quit_cb);

	but_grp->end();
	but_grp->resizable(dummy);

	main_win->end();
	main_win->label("Terminal test");
	main_win->resizable(terminal);
	main_win->size_range(500, 200, 0, 0, 0, 0, 0);
	
	main_win->show();

	return Fl::run();
}

/* End of File */
