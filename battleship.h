#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "player.h"
#include "AI_player.h"


using std::string;
using std::map;
using std::cin;
using std::cout;

class battleship {
public:
	bool check_around = false;
	board set_player_custom_first_board(int x, int y);
	player set_player_one(int x, int y);
	player get_player_one();
	AI_player get_AI_player();
	board set_AI_custom_board(int x, int y);
	AI_player set_AI_one(int x, int y);
	void create_ships(int n);
	std::vector<Ships> return_game_ships();
	void player_fire(int y);
	void AI_fire();
	void direction();
	void fire_west();
	void fire_east();
	void fire_south();
	void fire_north();



};
