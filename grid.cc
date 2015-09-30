#include "grid.h"
#include "textdisplay.h"
#include "cell.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;
/*
class Grid {
	int w, h, base, goal, current;
	TextDisplay * td;
	Cell **theGrid;
	Cell *empty;
	
public:
	void setEmpty();
	Grid(int, int, int, int);
	~Grid();
	void init(int, int, int, int);
	bool valid(int);
	void move(int);
	int status(int);
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};
*/
void Grid::clearGrid() { // deallocate the memory for the grid
  for (int i = 0; i < h; i++) {
    delete [] theGrid[i];
  }
  delete [] theGrid;
}


Grid::Grid(int base, int h, int w, int goal) {
	init(base, h, w, goal);
}

void Grid::init(int base, int h, int w, int goal) {
	clearGrid();

	this->w = w;
	this->h = h;
	this->goal = goal;
	this->base = base;
	
	delete td;
	//TextDisplay k = TextDisplay(w,h);
	//td = &k;
	td = new TextDisplay(w,h);

	theGrid = new Cell*[h];
	for (int i = 0; i < h; i++) {
		theGrid[i] = new Cell[w];
		for (int j = 0; j < w; j++) {
			theGrid[i][j].setDisplay(td);		
			theGrid[i][j].setCoord(i,j);
		}
	}

	newNum();
	current = td->getCurrent(0);
	cout << *td;

	cout << "grid = " << this->w << " by " << this->h << endl;
	cout << "base = " << this->base << endl;
	cout << "goal = " << this->goal << endl;
	cout << "movement made = " << 0 << endl;

}

void Grid::newNum() {
	int index = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (theGrid[i][j].getState() == 0) {
				index++;
			}
		}
	}

	srand(time(NULL));
	int position = rand() % index;
	int exponent = rand() % 2 + 1;

	int temp = 0;
	bool off = false;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (theGrid[i][j].getState() == 0) {	
				if (temp == position) {
					int state = pow(base, exponent);
					theGrid[i][j].setState(state);
					off = true;
					break;
				} else {
					temp++;
				}
			}
		}
		if (off) {
			break;
		}
	}
	numEmpty = index-1;
}

Grid::~Grid() {
	clearGrid();
	delete td;
}

bool Grid::valid(int m) {
	return td->valid(m);
}

int Grid::status() {
	int output;
	bool status = numEmpty == 0 && !valid(0) && !valid(1) && !valid(2) && !valid(3);
	if (current == goal) {
		output = 1;
	} else if (status) {
		output = -1;
	} else {
		output = 0;
	}
	return output;
}

std::ostream &operator<<(std::ostream &out, const Grid &g) { // calls the TextDisplay for print out
	out << *g.td;
	return out;
}

void Grid::move(int d) {
	int value;
	int comp;
	if (d == 3) {
		for (int i = 0; i < w; i++) {
			for (int j = h-1; j >= 0; j--) {
				value = theGrid[i][j].getState();
				if (j != 0) {
					comp = getNext(i,j,d,false);
					if (comp == value) {
						comp = getNext(i,j,d,true);
						theGrid[i][j].setState(base*value);
						j--;
					}
				}
			}

			for (int j = h-1; j >= 0; j--) {
				value = theGrid[i][j].getState();
				if (value == 0) {
					theGrid[i][j].setState(getNext(i,j,d,true));
				}
			}
		}
	} else if (d == 2) {
		for (int i = 0; i <w; i++) {
			for (int j = 0; j < h; j++) {
				value = theGrid[i][j].getState();
				if (j != h-1) {
					comp = getNext(i,j,d,false);
					if (comp == value) {
						comp = getNext(i,j,d,true);
						theGrid[i][j].setState(base*value);
						j++;
					}
				}
			}
			for (int j = 0; j < h; j++) {
				value = theGrid[i][j].getState();
				if (value == 0) {
					theGrid[i][j].setState(getNext(i,j,d,true));
				}
			}
		}
	} else if (d == 1) {
		for (int j = 0; j < h; j++) {
			for (int i = w-1; i >= 0; i--) {
				value = theGrid[i][j].getState();
				if (i != 0) {
					comp = getNext(i,j,d,false);
					if (comp == value) {
						comp = getNext(i,j,d,true);
						theGrid[i][j].setState(base*value);
						i--;
					}
				}
			}

			for (int i = w-1; i >= 0; i--) {
				value = theGrid[i][j].getState();
				if (value == 0) {
					theGrid[i][j].setState(getNext(i,j,d,true));
				}
			}
		}
	} else if (d == 0) {
		for (int j = 0; j < h; j++) {
			for (int i = 0; i <w; i++) {
				value = theGrid[i][j].getState();
				if (i != w-1) {
					comp = getNext(i,j,d,false);
					if (comp == value) {
						comp = getNext(i,j,d,true);
						theGrid[i][j].setState(base*value);
						i++;
					}
				}
			}

			for (int i = 0; i < w; i++) {
				value = theGrid[i][j].getState();
				if (value == 0) {
					theGrid[i][j].setState(getNext(i,j,d,true));
				}
			}
		}
	}
	newNum();
	current = td->getCurrent(current);
	cout << *td;
}


int Grid::getNext(int i, int j, int d, bool reset) {
	int value;
	if (d == 0) {
		if (i == w-1) {
			value = 0;
		} else {
			value = theGrid[i+1][j].getState();
			if (value != 0) {
				if (reset) {
					theGrid[i+1][j].setState(0);
				}
			} else {
				value = getNext(i+1, j, d, reset);
			}
		}
	} else if (d == 1) {
		if (i == 0) {
			value = 0;
		} else {
			value = theGrid[i-1][j].getState();
			if (value != 0) {
				if (reset) {
					theGrid[i-1][j].setState(0);
				}
			} else {
				value = getNext(i-1, j, d, reset);
			}
		}
	} else if (d == 2) {
		if (j == h-1) {
			value = 0;
		} else {
			value = theGrid[i][j+1].getState();
			if (value != 0) {
				if (reset) {
					theGrid[i][j+1].setState(0);
				}
			} else {
				value = getNext(i, j+1, d, reset);
			}
		}
	} else if (d == 3) {
		if (j == 0) {
			value = 0;
		} else {
			value = theGrid[i][j-1].getState();
			if (value != 0) {
				if (reset) {
					theGrid[i][j-1].setState(0);
				}
			} else {
				value = getNext(i, j-1, d, reset);
			}
		}
	}
	return value;
}
