#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>

class Cell;
class TextDisplay;

class Grid {
	int w, h, base, goal, current, numEmpty;
	TextDisplay * td;
	Cell **theGrid;
	void newNum();
	void clearGrid();
	int getNext(int, int, int, bool);
public:
	Grid(int, int, int, int);
	~Grid();
	void init(int, int, int, int);
	bool valid(int);
	void move(int);
	int status();
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif