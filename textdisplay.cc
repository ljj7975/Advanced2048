#include "textdisplay.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(int w, int h) : w(w), h(h) {
	theDisplay = new int*[h];
	for (int i = 0; i < h; i++) {
		theDisplay[i] = new int[w];
		for (int j = 0; j < w; j++) {
		  theDisplay[i][j] = 0; // initializing each field as ' '
		}
	}
}

TextDisplay::~TextDisplay() { // dtor
  for (int i = 0; i < h; i++) {
    delete [] theDisplay[i];
  }
  delete[] theDisplay;
}

bool TextDisplay::valid(int m) {
	bool output = false;
	int temp;
	int comp;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			temp = theDisplay[i][j];
			comp = compare(i,j,m);
			/*
			if (temp != ' ') {
				cout <<"i = " <<i << " j = " << j <<endl;
				cout << "temp is " << temp << endl;	
				cout << "comp is " << comp << endl;
			}
			*/
			if (temp != 0 && (comp == temp || comp == 0)) {
				output = true;
			}
		}
	}
	return output;
}

char TextDisplay::compare(int i, int j, int d) {
	int output;
	int c, r;
	if (d == 0) {
		c = i-1;
		r = j;
	} else if (d == 1) {
		c = i+1;
		r = j;
	} else if (d == 2) {
		c = i;
		r = j-1;
	} else if (d == 3) {
		c = i;
		r = j+1;
	}
	/*
	cout << "c = " << c << endl;
	cout << "r = " << r << endl; 
	
	cout << "i = " << i << "j = " << j << endl;
	cout << "c = " << c << "r = " << r << endl;
	*/
	if (c < 0 || c >= h || r < 0 || r >= w) {
		output = -1;
	} else {
		output = theDisplay[c][r];
		/*
		if (output != ' ') {
			output = comp(c,r,d);
		}
		*/
	}
	return output;
}

int TextDisplay::getCurrent(int current = 0) {
	int highest = current;
	int curr;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			curr = static_cast<int>(theDisplay[i][j]);
			if (curr > highest) {
				highest = curr;
			}
		}
	}
	return highest;
}

void TextDisplay::notify(int c, int r, int state) {
	//cout <<state << endl;
	//cout <<"td notify called " << state << endl;

	//cout << c << "  " << r << endl;
	//cout << theDisplay[c][r] << endl;
	theDisplay[c][r] = state;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	int temp;
	for (int i = 0; i < td.h; ++i){
		for (int k = 0; k < td.w; k++) {
			out << "----";	
		}
		out << "-";
		out << endl << "| ";
		for (int j = 0; j < td.w; ++j){
			temp = td.theDisplay[i][j];
			if (temp != 0) {
				out << temp; 
			} else {
				out << " ";
			}
			out << " | ";
		}
		out<<endl;
	}
	for (int k = 0; k < td.w; k++) {
		out << "----";	
	}
	out << "-" << endl;
	return out;
}
