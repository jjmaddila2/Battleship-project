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

class AI_player {
public:
	AI_player(board prime, board second);
	AI_player();
	board return_prime_board();
	board return_second_board();
	void place_ships(std::vector<Ships> ships_to_place);
	bool check_north(Ships ship_to_check, int index, board wanted_board);
	void place_ship_north(Ships ship_to_place, int index);
	bool check_south(Ships ship_to_check, int index, board wanted_board);
	void place_ship_south(Ships ship_to_place, int index);
	bool check_east(Ships ship_to_check, int index, board wanted_board);
	void place_ship_east(Ships ship_to_place, int index);
	bool check_west(Ships ship_to_check, int index, board wanted_board);
	void place_ship_west(Ships ship_to_place, int index);
	int find_place_to_fire(std::vector<Ships> ships_to_fire);
	int get_high_random_index(std::vector<int> prob);
	std::vector<std::pair<int, int>> sort_vector(std::vector<std::pair<int, int>> vector_to_sort);
	bool check_square_west(int index);
	bool check_square_east(int index);
	bool check_square_north(int index);
	bool check_square_south(int index);
	void set_point(int index, int value);
	void set_point_1(int index, int value);
	int get_point(int index);
};