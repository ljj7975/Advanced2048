#include <iostream>
#include "cell.h"
#include "grid.h"
#include "textdisplay.h"

using namespace std;

// up = 0, down = 1, left = 2, right = 3

int base, h, w, goal;
int movement = 0;
int minimum = 0;
bool bestScore = true;

void setting() {
	cout << "enter the base" << endl;;
	cin >> base;
	while (base < 2) {
		cout << "base must be greater than 1" << endl;
		cout << "please re-enter the base" << endl;
		cin >> base;
	}
	cout << "enter the size of the grid you want" << endl;
	cout << "the grid will be n by n" << endl;;
	cin >> h;
	while (h < 1) {
		cout << "size must be greater than 0" << endl;
		cout << "please re-enter the size" << endl;
		cin >> h;
	}
	w = h;
	
	cout << "enter the goal, it must be power of " << base << endl;
	cin >> goal;
	int temp = base;
	while (temp < goal) {
		temp = temp * base;
	}
	if (temp == goal) {
		cout << "your goal is " << temp << endl;
	} else {
		cout << "your goal is not power of " << base << endl;
		cout << "your goal is automatically set to " << temp << endl;
		goal = temp;
	}
}


int main() {

	setting();
	//cout << "in the loop"<< endl;
	Grid *g = new Grid(base, h, w, goal); // create grid



	while (true) {

		// --- getting move ---------------------------------------------
		
		cout << "please make move." << endl;
		cout << "[up = 0, down = 1, left = 2, right = 3]" << endl;
		char move;
		int m;
		cin >> move;
		m = move-'0';
		


		while (!(g->valid(m))) {

			if (move == 'q' || move == 'p') {
				break;
			}

			cout << "your move of "<< m << " was invalid." << endl;
			cout << "please make move." << endl;
			cout << "[up = 0, down = 1, left = 2, right = 3]" << endl;
			cin >> move;
			m = move-'0';	
		}

		if (move == 'q') {
			break;
		} else if (move == 'p') {
			cout << *g << endl;
		}

		// --- getting move done ---------------------------------------------

		// --- changing the baord ---------------------------------------------


		g->move(m);
		movement++;
		// --- changing the baord done ---------------------------------------------

		// --- check the status ---------------------------------------------
		cout << "movement made = " << movement << endl;
		int playOn = g->status();
		if (playOn != 0) { // if game is finished, ask if the player want to stop, or play new game.
			if (playOn < 0) {
				cout << "you lost!" << endl;
			} else if (playOn > 0) {
				cout << "you Won!" << endl;
				if (move > minimum || bestScore) {
					cout << "you won with the lowest movement! congraturation!" << endl;
					cout << "your movement was " << movement << endl;
					minimum = movement;
				}
			}
			movement = 0;
			cout << "do you want to replay? y/n" << endl;
			char replay;
			cin >> replay;
			while (!(replay == 'y' || replay == 'n')) {
				cout << "command must be either y/n" << endl;
				cin >> replay;
			}
			if (replay == 'y') {
				bestScore = false;
				cout << "with same board? y/n" << endl;
				cin >> replay;
				while (!(replay == 'y' || replay == 'n')) {
					cout << "command must be either y/n" << endl;
					cin >> replay;
				}
				if (replay == 'y') {
					g->init(base, h, w, goal);
					cout << "lowest movement = " << minimum << endl;					
				} else if (replay == 'n') {
					setting();
					g->init(base, h, w, goal);
					cout << "lowest movement = " << minimum << endl;	
				}
			} else if (replay == 'n') {
				if (!bestScore) {
					cout << "lowest movement was " << minimum << endl;	
					cout << "good job~!" << endl;
				}
				cout << "Thank you for playing~!"<< endl;
				break;
			}
		} // playon?

		// --- check the status done ---------------------------------------------

	} // while

	delete g;
}