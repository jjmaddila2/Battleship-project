#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include "battleship.h"


using std::string;
using std::map;
using std::cin;
using std::cout;

board playe;
board AI;
player custom_player;
AI_player custom_AI;
std::vector<Ships> game_ships;


int head_index;
int temp_index;
std::vector<char> directions;
bool change_name;
bool change_direction;
int random_direction;
bool special_switch;

board battleship::set_player_custom_first_board(int x, int y) {
	playe = board(x, y);
	return playe;
}

board battleship::get_board() {
	return playe;
}

player battleship::set_player_one(int x, int y) {
	custom_player = player(set_player_custom_first_board(x, y), set_player_custom_first_board(x, y));
	cout << get_player_one().return_prime_board().getMat().size() << "\n";
	return custom_player;
}

player battleship::get_player_one() {
	return custom_player;
}

AI_player battleship::get_AI_player() {
	return custom_AI;
}

board battleship::set_AI_custom_board(int x, int y) {
	AI = board(x, y);
	return AI;
}

AI_player battleship::set_AI_one(int x, int y) {
	custom_AI = AI_player(set_AI_custom_board(x, y), set_AI_custom_board(x, y));
	return custom_AI;
}

void battleship::create_ships(int n) {
	if (n > 5) {
		n = 5;
	}
	int standard = 3;
	for (int i = n; i > 0; i--) {
		game_ships.push_back(Ships(standard));
	}
}

std::vector<Ships> battleship::return_game_ships() {
	cout << "ship size" << game_ships.size() << "\n";
	cout << "new ship size" << new_.size() << "\n";
	for (int i = 0; i < 5; i++) {
		new_.push_back(game_ships[i]);
	}
	return game_ships;
}

void battleship::player_fire(int index) {
	cout << index << "\n";
	cout << get_AI_player().get_point(index) << "\n";
	if (get_AI_player().return_prime_board().get_point(index) == 1) {
		cout << "printing something" << "\n";
		custom_player.set_point(index, 1);
		custom_AI.set_point(index, 2);

	}
	else if (custom_AI.return_prime_board().get_point(index) == 0) {
		cout << "printing" << "\n";
		custom_AI.set_point(index, 2);
		custom_player.set_point(index, 2);
	}
	else {
		cout << "You cannot fire here, you already have";
	}
	for (int i = 0; i < custom_player.return_second_board().getMat().size(); i++) {
		//cout << custom_player.return_second_board().getMat()[i] << "\n";
	}
}

bool hit(bool value) {
	return value;
}

void battleship::AI_fire() {
	if (!check_around) {
		int index = custom_AI.find_place_to_fire(game_ships);
		if (custom_player.return_prime_board().get_point(index) == 1) {
		
			custom_AI.set_point_1(index, 1);
			custom_player.get_point(index, 2);
			check_around = true;
			change_direction = true;
			special_switch = false;
			head_index = index;
			temp_index = index;
			directions.clear();
			directions.push_back('N');
			directions.push_back('S');
			directions.push_back('E');
			directions.push_back('W');
			
		}
		else {
		
			custom_player.get_point(index, 2);
			custom_AI.set_point_1(index, 2);
		}
	}
	else {
		change_name = true;
		
		if (directions.size() == 0) {
			check_around = false;
			change_name = false;
		}
		else if (change_direction) {
			random_direction = rand() % directions.size();
		}	
		while (change_name) {
			if ((special_switch) && (directions.size() != 0)){
				random_direction = rand() % directions.size();
			}
			if (directions.size() == 0) {
				break;
			}
			if (directions[random_direction] == 'W') {
				if (custom_AI.check_square_west(temp_index)) {
					temp_index--;
					if (custom_player.return_prime_board().get_point(temp_index) == 1) {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 1);
						directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
						directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
						for (int i = 0; i < directions.size(); i++) {
							random_direction = i;
						}
						change_name = false;
						change_direction = false;
						special_switch = false;
					}
					else {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 2);
						temp_index = head_index;
						directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
						change_name = false;
						change_direction = true;
						special_switch = false;
					}
				}
				else {
					temp_index = head_index;
					directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
					change_direction = true;
					special_switch = true;
					cout << directions.size();
				}
			}

			else if (directions[random_direction] == 'E') {
				if (custom_AI.check_square_east(temp_index)) {
					temp_index++;
					if (custom_player.return_prime_board().get_point(temp_index) == 1) {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 1);
						directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
						directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
						random_direction = 0;
						change_direction = false;
						change_name = false;
						special_switch = false;
					}
					else {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 2);
						temp_index = head_index;
						directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
						change_name = false;
						change_direction = true;
						special_switch = false;
					}
				}
				else {
					temp_index = head_index;
					directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
					change_direction = true;
					special_switch = true;
				}
			}

			else if (directions[random_direction] == 'N') {
				if (custom_AI.check_square_north(temp_index)) {
					temp_index -= playe.get_width();
					if (custom_player.return_prime_board().get_point(temp_index) == 1) {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 1);
						directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
						directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
						change_name = false;
						change_direction = false;
						special_switch = false;
					}
					else {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 2);
						temp_index = head_index;
						directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
						change_name = false;
						change_direction = true;
						special_switch = false;
					}
				}
				else {
					temp_index = head_index;
					directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
					change_direction = true;
					special_switch = true;
				}
			}

			else if (directions[random_direction] == 'S') {
				if (custom_AI.check_square_south(temp_index)) {
					temp_index += playe.get_width();
					if (custom_player.return_prime_board().get_point(temp_index) == 1) {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 1);
						directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
						directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
						change_name = false;
						special_switch = false;
						change_direction = false;
					}
					else {
						custom_player.get_point(temp_index, 2);
						custom_AI.set_point_1(temp_index, 2);
						temp_index = head_index;
						directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
						change_name = false;
						change_direction = true;
						special_switch = false;
					}
				}
				else {
					temp_index = head_index;
					directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
					change_direction = true;
					special_switch = true;
				}
			}
		}
	}
}
