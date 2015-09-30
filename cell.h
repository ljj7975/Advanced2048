#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>

class TextDisplay;

class Cell {
	int r, c, state;
	TextDisplay * td;
public:
	void setCoord(int, int);
	void setState(int); // notify
	void setDisplay(TextDisplay * t);
	int getState();
	void getCoord();
};

#endif