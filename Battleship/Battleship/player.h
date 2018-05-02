#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "board.h"
#include "Ships.h"


using std::string;
using std::map;
using std::cin;
using std::cout;

class player {
public: 
	player(board prime, board second);
	board return_prime_board();
	board player::return_second_board();
	player();
	bool place_ship(Ships ship_to_place, int x, int y, int direction);
	bool place_ship_north(Ships ship_to_place, int x, int y);
	bool place_ship_south(Ships ship_to_place, int x, int y);
	bool place_ship_east(Ships ship_to_place, int x, int y);
	bool place_ship_west(Ships ship_to_place, int x, int y);
	void get_point(int index, int value);
	void set_point(int index, int value);

};