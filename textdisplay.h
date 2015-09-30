#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>

class TextDisplay {
	int w, h;
	int ** theDisplay;
public:
	TextDisplay(int, int);
	~TextDisplay();
	bool valid(int);
	int getCurrent(int);
	void notify(int, int, int);
	char compare(int, int, int);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
