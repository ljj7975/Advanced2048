#include "cell.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;


//Cell::Cell(int c, int r) : c(c), r(r), state(0) {}

void Cell::setCoord(int c, int r) {
	this->c = c;
	this->r = r;
	state = 0;
	td->notify(c, r, state);
}

void Cell::setState(int state) {
	//cout << "set state called  "<< state <<endl;
	//cout << r << "  " << c << endl;
	this->state = state;
	td->notify(c, r, state);
}
void Cell::setDisplay(TextDisplay * t) {
	td = t;
}
int Cell::getState() {
	return state;
}

void Cell::getCoord() {
	cout << "c/i is " << c << endl;
	cout << "r/j is " << r << endl;
}