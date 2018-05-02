#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include "AI_player.h"

using std::string;
using std::map;
using std::cin;
using std::cout;

board AI_first_board;
board AI_second_board;

AI_player::AI_player(board prime, board second) {
	AI_first_board = prime;
	AI_second_board = second;
}

AI_player::AI_player() {};

board AI_player::return_prime_board() {
	return AI_first_board;
}

board AI_player::return_second_board() {
	return AI_second_board;
}

void AI_player::set_point(int index, int value) {
	AI_first_board.set_point(index, value);
}

void AI_player::set_point_1(int index, int value) {
	AI_second_board.set_point(index, value);
}

void AI_player::place_ships(std::vector<Ships> ships_to_place) {
	bool can_place_ship;
	for (int i = 0; i < ships_to_place.size(); i++) {
		can_place_ship = true;
		while (can_place_ship) {
			//index for where to put the head of a ship
			int random_index = rand() % AI_first_board.getMat().size();
			int random_direction = rand() % 4;
			if (AI_first_board.get_point(random_index) != 0) {
				continue;
			}
			//for north
			else if (random_direction == 0) {
				if (check_north(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_north(ships_to_place[i], random_index);
					cout << random_direction << " " << random_index << "\n";
				}
			}
			//for south
			else if (random_direction == 1) {
				if (check_south(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_south(ships_to_place[i], random_index);
					cout << random_direction << " " << random_index << "\n";
				}
			}
			//for east
			else if (random_direction == 2) {
				if (check_east(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_east(ships_to_place[i], random_index);
					cout << random_direction << " " << random_index << "\n";
				}
			}
			//for west
			else if (random_direction == 3) {
				if (check_west(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_west(ships_to_place[i], random_index);
					cout << random_direction << " " << random_index << "\n";
				}
			}
		}
	}
}

bool AI_player::check_north(Ships ship_to_check, int index, board wanted_board) {
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width();
	if (height - ship_to_check.getLength() < -1) {
		return false;
	}
	for (int i = (wanted_board.get_width() * height) + width;
		i >= ((height + 1 - ship_to_check.getLength()) * wanted_board.get_width() + width); i -= wanted_board.get_width()) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	return true;
}

void AI_player::place_ship_north(Ships ship_to_place, int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_first_board.get_width();
		height++;
	}
	int width = index + AI_first_board.get_width();
	for (int i = (AI_first_board.get_width() * height) + width;
		i >= ((height + 1 - ship_to_place.getLength()) * AI_first_board.get_width() + width); i -= AI_first_board.get_width()) {
		AI_first_board.set_point(i, 1);
	}
}

bool AI_player::check_south(Ships ship_to_check, int index, board wanted_board) {
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width();
	if (height + ship_to_check.getLength() > wanted_board.get_height()) {
		return false;
	}
	for (int i = (wanted_board.get_width() * height) + width;
		i <= ((height - 1 + ship_to_check.getLength()) * wanted_board.get_width() + width); i += wanted_board.get_width()) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	return true;
}

void AI_player::place_ship_south(Ships ship_to_place, int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_first_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	for (int i = (AI_first_board.get_width() * height) + width;
		i <= ((height - 1 + ship_to_place.getLength()) * AI_first_board.get_width() + width); i += AI_first_board.get_width()) {
		AI_first_board.set_point(i, 1);
	}
}

bool AI_player::check_east(Ships ship_to_check, int index, board wanted_board) {
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width() + 1;
	if (width + ship_to_check.getLength()  > wanted_board.get_width()) {
		return false;
	}
	for (int i = (wanted_board.get_width() * height) + width;
		i <= ((height * wanted_board.get_width()) + width + ship_to_check.getLength() - 1); i++) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	return true;
}

void AI_player::place_ship_east(Ships ship_to_place, int index) {
		int height = -1;
		while (index >= 0) {
			index -= AI_first_board.get_width();
			height++;
		}
		int width = index + AI_first_board.get_width();
		for (int i = (AI_first_board.get_width() * height) + width;
			i <= ((height * AI_first_board.get_width()) + width + ship_to_place.getLength()) - 1; i++) {
			AI_first_board.set_point(i, 1);
		}
}

bool AI_player::check_west(Ships ship_to_check, int index, board wanted_board) {
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width();
	if (width - ship_to_check.getLength() < -1) {
		return false;
	}
	for (int i = (wanted_board.get_width() * height) + width;
		i >= (wanted_board.get_width() * height) + width - ship_to_check.getLength() + 1; i--) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	return true;
}

void AI_player::place_ship_west(Ships ship_to_place, int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_first_board.get_width();
		height++;
	}
	int width = index + AI_first_board.get_width();
	for (int i = (AI_first_board.get_width() * height) + width;
		i >= (AI_first_board.get_width() * height) + width - ship_to_place.getLength() + 1; i--) {
		AI_first_board.set_point(i, 1);
	}
}

int AI_player::find_place_to_fire(std::vector<Ships> ships_to_hit) {
	std::vector<int> probabilties;
	int count;
	for (int i = 0; i < AI_first_board.getMat().size(); i++) {
		count = 0;
		for (int j = 0; j < ships_to_hit.size(); j++) {
			if (check_east(ships_to_hit[j], i, AI_second_board)) {
				count++;
			}
			if (check_north(ships_to_hit[j], i, AI_second_board)) {
				count++;
			}
			if (check_south(ships_to_hit[j], i, AI_second_board)) {
				count++;
			}
			if (check_west(ships_to_hit[j], i, AI_second_board)) {
				count++;
			}
		}
		probabilties.push_back(count);
	}
	return get_high_random_index(probabilties);
}

int AI_player::get_high_random_index(std::vector<int> prob) {
	std::vector<std::pair<int, int>> prob_and_index;
	for (int i = 0; i < prob.size(); i++) {
		//cout << prob[i] << "\n";
		prob_and_index.push_back(std::make_pair(i, prob[i]));
	}
	prob_and_index = sort_vector(prob_and_index);
	std::vector<std::pair<int, int>> only_high;
	for (int i = 0; i < prob_and_index.size(); i++) {
		//cout << prob_and_index[i].second << "\n";
		
		if (prob_and_index[i].second == prob_and_index[0].second) {
			only_high.push_back(prob_and_index[i]);
		}
		else {
			break;
		}
		
	}
	for (int i = 0; i < only_high.size(); i++) {
		//cout << only_high[i].first << "\n";
	}
	int random_index = rand() % only_high.size();
	cout << "\n" << random_index << "\n";
	return only_high[random_index].first;
}

bool myFunction(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
	return (p1.second > p2.second);
}

std::vector<std::pair<int, int>> AI_player::sort_vector(std::vector<std::pair<int, int>> vector_to_sort) {
	std::sort(vector_to_sort.begin(), vector_to_sort.end(), myFunction);
	return vector_to_sort;
}

bool AI_player::check_square_west(int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	if (width == 0) {
		return false;
	}
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width - 1) != 0) {
		return false;
	}
	return true;
}

bool AI_player::check_square_east(int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	if (width == AI_second_board.get_width() - 1) {
		return false;
	}
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width + 1) != 0) {
		return false;
	}
	return true;
}

bool AI_player::check_square_south(int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	if (height == AI_second_board.get_height() - 1) {
		return false;
	}
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width + AI_second_board.get_width()) != 0) {
		return false;
	}
	return true;
}

bool AI_player::check_square_north(int index) {
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	if (height ==0) {
		cout << "false" << "\n";
		return false;
	}
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width - AI_second_board.get_width()) != 0) {
		return false;
	}
	return true;
}

int AI_player::get_point(int index) {
	return return_prime_board().get_point(index);
}