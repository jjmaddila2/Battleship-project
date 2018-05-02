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

board primary_borad;
board secondary_board;

player::player(board prime,board second) {
	primary_borad = prime;
	secondary_board = second;
}

player::player() {}
bool fun = true;
board player::return_prime_board() {
	while (fun) {
		cout << "check" << "\n";
		fun = false;
	}
	
	return primary_borad;
}

board player::return_second_board() {
	return secondary_board;
}

bool player::place_ship(Ships ship_to_place, int x, int y, int direction) {
	if (direction == 0) {
		if (place_ship_north(ship_to_place, x, y)) {
			return true;
		}
		else {
			return false;
		}
	}
	if (direction == 1) {
		if (place_ship_south(ship_to_place, x, y)) { return true; }
		else {
			return false;
		}
	}
	if (direction == 2) {
		if (place_ship_east(ship_to_place, x, y)) { return true; }
	else {
		return false;
	}
	}
	if (direction == 3) {
		if (place_ship_west(ship_to_place, x, y)) { return true; }
		else {
			return false;
		}
	}
}

void player::get_point(int index, int value) {
	primary_borad.set_point(index, value);
}
	
void player::set_point(int index, int value) {
	secondary_board.set_point(index, value);
}

bool player::place_ship_north(Ships ship_to_place, int width, int height) {
	if (height - ship_to_place.getLength() < -1) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i >= ((height + 1 - ship_to_place.getLength()) * primary_borad.get_width() + width); i -= primary_borad.get_width()) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship";
			return false;
		}
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i >= ((height + 1 - ship_to_place.getLength()) * primary_borad.get_width() + width); i -= primary_borad.get_width()) {
		primary_borad.set_point(i, 1);
	}
	return true;
}

bool player::place_ship_south(Ships ship_to_place, int width, int height) {
	if (height + ship_to_place.getLength() > primary_borad.get_height()) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i <= ((height - 1 + ship_to_place.getLength()) * primary_borad.get_width() + width); i += primary_borad.get_width()) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship";
			return false;
		}
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i <= ((height - 1 + ship_to_place.getLength()) * primary_borad.get_width() + width); i += primary_borad.get_width()) {
		primary_borad.set_point(i, 1);
	}
	return true;
}

bool player::place_ship_east(Ships ship_to_place, int width, int height) {
	if (width + ship_to_place.getLength() > primary_borad.get_width()) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i <= (primary_borad.get_width() * height) + width + ship_to_place.getLength() - 1; i++) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship!!";
			return false;;
		}
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i <= (primary_borad.get_width() * height) + width + ship_to_place.getLength() - 1; i++) {
		primary_borad.set_point(i, 1);
	}
	return true;
}

bool player::place_ship_west(Ships ship_to_place, int width, int height) {
	if (width - ship_to_place.getLength() < -1) {
		cout << "Wrong input! Cannot place ship";
		return false;
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i >= (primary_borad.get_width() * height) + width - ship_to_place.getLength() + 1; i--) {
		if (primary_borad.get_point(i) != 0) {
			cout << "Wrong input! Cannot place ship";
			return false;
		}
	}
	for (int i = (primary_borad.get_width() * height) + width;
		i >= (primary_borad.get_width() * height) + width - ship_to_place.getLength() + 1; i--) {
		primary_borad.set_point(i, 1);
	}
	return true;
}
