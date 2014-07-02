#ifndef HAVE_TERM_SH_HDR
#define HAVE_TERM_SH_HDR

#include "gterm.hpp"

class Fl_Term : public GTerm {
public:
	Fl_Term(int w, int h) : GTerm(w, h) { }

	void DrawText(int fg_color, int bg_color, int flags,
	        int x, int y, int len, unsigned char *string);

	void DrawCursor(int fg_color, int bg_color, int flags,
	        int x, int y, unsigned char c);

	void MoveChars(int sx, int sy, int dx, int dy, int w, int h);
	void ClearChars(int bg_color, int x, int y, int w, int h);
	void SendBack(char *data);
	void Bell();
	void RequestSizeChange(int w, int h);
};

typedef struct {
        int keysym;
        char *str;
} keyseq;

extern keyseq cursorkeys[];
extern keyseq cursorappkeys[];
extern keyseq keypadkeys[];
extern keyseq keypadappkeys[];
extern keyseq otherkeys[];

char *find_key(int keysym, keyseq *table);

#endif // HAVE_TERM_SH_HDR

/* End of File */
