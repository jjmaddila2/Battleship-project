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

//the boards for the AI
board AI_first_board;
board AI_second_board;

//constructer to set the AI with its board
AI_player::AI_player(board prime, board second) {
	AI_first_board = prime;
	AI_second_board = second;
}

//default constructer
AI_player::AI_player() {};

//returns the prime board for the AI
board AI_player::return_prime_board() {
	return AI_first_board;
}

//returns the prime board for the AI
board AI_player::return_second_board() {
	return AI_second_board;
}

//simple method to simply call board method for prime board
void AI_player::set_point(int index, int value) {
	AI_first_board.set_point(index, value);
}

//same as above but for second board
void AI_player::set_point_1(int index, int value) {
	AI_second_board.set_point(index, value);
}

//method to have AI place all of their ships
void AI_player::place_ships(std::vector<Ships> ships_to_place) {
	bool can_place_ship;
	//goes through every ship
	for (int i = 0; i < ships_to_place.size(); i++) {
		can_place_ship = true;
		//this while statement will force the AI to keep trying to place the ship until it ca
		while (can_place_ship) {
			//index for where to put the head of a ship
			int random_index = rand() % AI_first_board.getMat().size();
			//finds a random direction
			int random_direction = rand() % 4;
			//sees if the random index already has a ship
			if (AI_first_board.get_point(random_index) != 0) {
				continue;
			}
			//for north
			else if (random_direction == 0) {
				//checks if the ship can be placed then places the ship
				if (check_north(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_north(ships_to_place[i], random_index);
				}
			}
			//for south
			else if (random_direction == 1) {
				//if ship can be placed than it will be placed
				if (check_south(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_south(ships_to_place[i], random_index);
				}
			}
			//for east
			else if (random_direction == 2) {
				//if ship can be placed than it will be placed
				if (check_east(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_east(ships_to_place[i], random_index);
				}
			}
			//for west
			else if (random_direction == 3) {
				//if ship can be placed than it will be placed
				if (check_west(ships_to_place[i], random_index, AI_first_board)) {
					can_place_ship = false;
					place_ship_west(ships_to_place[i], random_index);
				}
			}
		}
	}
}

//method to check if the ship can be placed north
bool AI_player::check_north(Ships ship_to_check, int index, board wanted_board) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width();
	//if ship will go off screen return false
	if (height - ship_to_check.getLength() < -1) {
		return false;
	}
	//if ship will cause overlap than return false
	for (int i = (wanted_board.get_width() * height) + width;
		i >= ((height + 1 - ship_to_check.getLength()) * wanted_board.get_width() + width); i -= wanted_board.get_width()) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	//if it gets this far than ship can be placed and return true
	return true;
}

void AI_player::place_ship_north(Ships ship_to_place, int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_first_board.get_width();
		height++;
	}
	int width = index + AI_first_board.get_width();
	//adds the ship
	for (int i = (AI_first_board.get_width() * height) + width;
		i >= ((height + 1 - ship_to_place.getLength()) * AI_first_board.get_width() + width); i -= AI_first_board.get_width()) {
		AI_first_board.set_point(i, 1);
	}
}

//method to check if the ship can be placed south
bool AI_player::check_south(Ships ship_to_check, int index, board wanted_board) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width();
	//if ship will go off screen return false
	if (height + ship_to_check.getLength() > wanted_board.get_height()) {
		return false;
	}
	//if ship will cause overlap than return false
	for (int i = (wanted_board.get_width() * height) + width;
		i <= ((height - 1 + ship_to_check.getLength()) * wanted_board.get_width() + width); i += wanted_board.get_width()) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	//if it gets this far than ship can be placed and return true
	return true;
}

void AI_player::place_ship_south(Ships ship_to_place, int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_first_board.get_width();
		height++;
	}
	//adds the ship
	int width = index + AI_second_board.get_width();
	for (int i = (AI_first_board.get_width() * height) + width;
		i <= ((height - 1 + ship_to_place.getLength()) * AI_first_board.get_width() + width); i += AI_first_board.get_width()) {
		AI_first_board.set_point(i, 1);
	}
}

//method to check if the ship can be placed east
bool AI_player::check_east(Ships ship_to_check, int index, board wanted_board) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width() + 1;
	//if ship will go off screen return false
	if (width + ship_to_check.getLength()  > wanted_board.get_width()) {
		return false;
	}
	//if ship will cause overlap than return false
	for (int i = (wanted_board.get_width() * height) + width;
		i <= ((height * wanted_board.get_width()) + width + ship_to_check.getLength() - 1); i++) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	//if it gets this far than ship can be placed and return true
	return true;
}

void AI_player::place_ship_east(Ships ship_to_place, int index) {
	//code to convert index to an x, y cordinate
		int height = -1;
		while (index >= 0) {
			index -= AI_first_board.get_width();
			height++;
		}
		int width = index + AI_first_board.get_width();
		//adds the ship
		for (int i = (AI_first_board.get_width() * height) + width;
			i <= ((height * AI_first_board.get_width()) + width + ship_to_place.getLength()) - 1; i++) {
			AI_first_board.set_point(i, 1);
		}
}

//method to check if the ship can be placed west
bool AI_player::check_west(Ships ship_to_check, int index, board wanted_board) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= wanted_board.get_width();
		height++;
	}
	int width = index + wanted_board.get_width();
	//if ship will go off screen return false
	if (width - ship_to_check.getLength() < -1) {
		return false;
	}
	//if ship will cause overlap than return false
	for (int i = (wanted_board.get_width() * height) + width;
		i >= (wanted_board.get_width() * height) + width - ship_to_check.getLength() + 1; i--) {
		if (wanted_board.get_point(i) != 0) {
			return false;
		}
	}
	//if it gets this far than ship can be placed and return true
	return true;
}

void AI_player::place_ship_west(Ships ship_to_place, int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_first_board.get_width();
		height++;
	}
	int width = index + AI_first_board.get_width();
	//adds the ship
	for (int i = (AI_first_board.get_width() * height) + width;
		i >= (AI_first_board.get_width() * height) + width - ship_to_place.getLength() + 1; i--) {
		AI_first_board.set_point(i, 1);
	}
}

//method used for AI_fire() this will generate probilites for each square
int AI_player::find_place_to_fire(std::vector<Ships> ships_to_hit) {
	//vector that represents the probility for each square
	std::vector<int> probabilties;
	int count;
	//goes through every square
	for (int i = 0; i < AI_first_board.getMat().size(); i++) {
		count = 0;
		//and then every ship and see if the ship can be placed in every direction
		for (int j = 0; j < ships_to_hit.size(); j++) {
			//if the ship can placed in that direction it adds one to the total
			//does this for every square in every direction for every ship
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
		//adds count to the vector
		probabilties.push_back(count);
	}
	return get_high_random_index(probabilties);
}

//method to get the highet count value(square with highest probility)
int AI_player::get_high_random_index(std::vector<int> prob) {
	std::vector<std::pair<int, int>> prob_and_index;
	for (int i = 0; i < prob.size(); i++) {
		//adds orginal index and count total to a new vector
		prob_and_index.push_back(std::make_pair(i, prob[i]));
	}
	//sorts the vectro
	prob_and_index = sort_vector(prob_and_index);
	std::vector<std::pair<int, int>> only_high;
	//makes a new vector with only the highest count value
	for (int i = 0; i < prob_and_index.size(); i++) {
		if (prob_and_index[i].second == prob_and_index[0].second) {
			only_high.push_back(prob_and_index[i]);
		}
		else {
			break;
		}	
	}
	//generates a random index of the highest count values
	int random_index = rand() % only_high.size();
	//returns the index that the AI will fire at
	return only_high[random_index].first;
}

bool myFunction(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
	return (p1.second > p2.second);
}

//simply function to sort vector
std::vector<std::pair<int, int>> AI_player::sort_vector(std::vector<std::pair<int, int>> vector_to_sort) {
	std::sort(vector_to_sort.begin(), vector_to_sort.end(), myFunction);
	return vector_to_sort;
}

//once the AI gets a hit these methods check if the squres next to that square can also be hit
//check if a square to the west can be hit
bool AI_player::check_square_west(int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	//if width is already zero than return false
	if (width == 0) {
		return false;
	}
	//if the next square is already shot at than return false
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width - 1) != 0) {
		return false;
	}
	//if it gets this far than the square is open and you can hit it.
	return true;
}

//check if a square to the east can be hit
bool AI_player::check_square_east(int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	//if width is already max than return false
	if (width == AI_second_board.get_width() - 1) {
		return false;
	}
	//if the next square is already shot at than return false
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width + 1) != 0) {
		return false;
	}
	//if it gets this far than the square is open and you can hit it.
	return true;
}

//check if a square to the south can be hit
bool AI_player::check_square_south(int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	//if height is already zero than return false
	if (height == AI_second_board.get_height() - 1) {
		return false;
	}
	//if the next square is already shot at than return false
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width + AI_second_board.get_width()) != 0) {
		return false;
	}
	//if it gets this far than the square is open and you can hit it.
	return true;
}

//check if a square to the north can be hit
bool AI_player::check_square_north(int index) {
	//code to convert index to an x, y cordinate
	int height = -1;
	while (index >= 0) {
		index -= AI_second_board.get_width();
		height++;
	}
	int width = index + AI_second_board.get_width();
	//if height is already max than return false
	if (height ==0) {
		return false;
	}
	//if the next square is already shot at than return false
	else if (AI_second_board.get_point(AI_second_board.get_width() * height + width - AI_second_board.get_width()) != 0) {
		return false;
	}
	//if it gets this far than the square is open and you can hit it.
	return true;
}

//simpel method to simply call get_point for prime board 
int AI_player::get_point(int index) {
	return return_prime_board().get_point(index);
}