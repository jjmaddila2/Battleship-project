#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "player.h"
#include "Ships.h"

using std::string;
using std::map;
using std::cin;
using std::cout;

//the players first and second board
board primary_borad;
board secondary_board;

//constucter that sets the player's first and second board
player::player(board prime,board second) {
	primary_borad = prime;
	secondary_board = second;
}

//default constucter for the player
player::player() {}

//simply returns the players primary board
board player::return_prime_board() {	
	return primary_borad;
}

//returns the players second board
board player::return_second_board() {
	return secondary_board;
}

//called from ofApp class and places the ship for the player
//x is width, y is height, direction is players choice
bool player::place_ship(Ships ship_to_place, int x, int y, int direction) {
	//0 represents north
	//bool since if the ship cannot be placed than method will return false
	if (direction == 0) {
		if (place_ship_north(ship_to_place, x, y)) {
			return true;
		}
		else {
			return false;
		}
	}
	//1 represents south
	if (direction == 1) {
		if (place_ship_south(ship_to_place, x, y)) { return true; }
		else {
			return false;
		}
	}
	//2 reprents east
	if (direction == 2) {
		if (place_ship_east(ship_to_place, x, y)) { return true; }
	else {
		return false;
	}
	}
	//3 represents west
	if (direction == 3) {
		if (place_ship_west(ship_to_place, x, y)) { return true; }
		else {
			return false;
		}
	}
}

//just a method that call sets point in board class for primary board
void player::get_point(int index, int value) {
	primary_borad.set_point(index, value);
}

//same method as above excpet for secondary board
void player::set_point(int index, int value) {
	secondary_board.set_point(index, value);
}

//places ship north if it can, otherwise returns false
bool player::place_ship_north(Ships ship_to_place, int width, int height) {
	//if the ship would go offscreen at this index than return false
	if (height - ship_to_place.getLength() < -1) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	//if placing this ship at this location would cause overlap than will return false
	for (int i = (primary_borad.get_width() * height) + width;
		i >= ((height + 1 - ship_to_place.getLength()) * primary_borad.get_width() + width); i -= primary_borad.get_width()) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship";
			return false;
		}
	}
	//if ship can be placed than it will be placed
	for (int i = (primary_borad.get_width() * height) + width;
		i >= ((height + 1 - ship_to_place.getLength()) * primary_borad.get_width() + width); i -= primary_borad.get_width()) {
		primary_borad.set_point(i, 1);
	}
	return true;
}

//places ship south if it can, otherwise returns false
bool player::place_ship_south(Ships ship_to_place, int width, int height) {
	//if the ship would go offscreen at this index than return false
	if (height + ship_to_place.getLength() > primary_borad.get_height()) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	//if placing this ship at this location would cause overlap than will return false
	for (int i = (primary_borad.get_width() * height) + width;
		i <= ((height - 1 + ship_to_place.getLength()) * primary_borad.get_width() + width); i += primary_borad.get_width()) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship";
			return false;
		}
	}
	//if ship can be placed than it will be placed
	for (int i = (primary_borad.get_width() * height) + width;
		i <= ((height - 1 + ship_to_place.getLength()) * primary_borad.get_width() + width); i += primary_borad.get_width()) {
		primary_borad.set_point(i, 1);
	}
	return true;
}

//places ship east if it can, otherwise returns false
bool player::place_ship_east(Ships ship_to_place, int width, int height) {
	//if the ship would go offscreen at this index than return false
	if (width + ship_to_place.getLength() > primary_borad.get_width()) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	//if placing this ship at this location would cause overlap than will return false
	for (int i = (primary_borad.get_width() * height) + width;
		i <= (primary_borad.get_width() * height) + width + ship_to_place.getLength() - 1; i++) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship!!";
			return false;;
		}
	}
	//if ship can be placed than it will be placed
	for (int i = (primary_borad.get_width() * height) + width;
		i <= (primary_borad.get_width() * height) + width + ship_to_place.getLength() - 1; i++) {
		primary_borad.set_point(i, 1);
	}
	return true;
}

//places ship west if it can, otherwise returns false
bool player::place_ship_west(Ships ship_to_place, int width, int height) {
	//if the ship would go offscreen at this index than return false
	if (width - ship_to_place.getLength() < -1) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	//if placing this ship at this location would cause overlap than will return false
	for (int i = (primary_borad.get_width() * height) + width;
		i >= (primary_borad.get_width() * height) + width - ship_to_place.getLength() + 1; i--) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship";
			return false;
		}
	}
	//if ship can be placed than it will be placed
	for (int i = (primary_borad.get_width() * height) + width;
		i >= (primary_borad.get_width() * height) + width - ship_to_place.getLength() + 1; i--) {
		primary_borad.set_point(i, 1);
	}
	return true;
}
