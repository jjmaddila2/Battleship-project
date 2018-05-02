#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "board.h"


using std::cin;
int height;
int width;

using std::string;
using std::map;
using std::cin;
using std::cout;
	
/*
defaut constucter sets the board dimensions as 10 by 10
*/
board::board() {
	height = 10;
	width = 10;
	//populates the board with 100 zeros
	std::vector<int> board_yup(100, 0);
	board_dim = board_yup;
};

/*
This allows for customization of the board itself
*/
board::board(int h, int w) {
	height = h;
	width = w;
	std::vector<int> board_yup(h * w, 0);
	board_dim = board_yup;
}

/*
method to set a point in the vecter to the correct value
*/
void board::set_point(int index, int value) {
	for (int i = 0; i < board_dim.size(); i++) {
		cout << board_dim[i] << "\n";
	}
	board_dim[index] = value;
}

/*
accesses the point in the vector
*/
int board::get_point(int index) {
	int value = board_dim[index];
	return value;
}

/*
simply returns the height of the board
*/
int board::get_height() {
	return height;
}

/*
simply returns the height of the board
*/
int board::get_width() {
	return width;
}

/*
simply returns the vector board
*/
std::vector<int> board::getMat() {
	return board_dim;
}

/*
goes through vector to see if any ones are there if so then return false
*/
bool board::is_winner() {
	for (int i = 0; i < board_dim.size(); i++) {
		//means that their are still ships alive
		if (board_dim[i] == 1) {
			return false;
		}
	}
	return true;
}

