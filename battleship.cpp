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
bool make_sure_AI_fires;
bool change_direction;
int random_direction;
bool special_switch;

//sets player one board
board battleship::set_player_custom_first_board(int x, int y) {
	playe = board(x, y);
	return playe;
}


//set player one with two board
player battleship::set_player_one(int x, int y) {
	custom_player = player(set_player_custom_first_board(x, y), set_player_custom_first_board(x, y));
	cout << get_player_one().return_prime_board().getMat().size() << "\n";
	return custom_player;
}

//easy way to acess player one
player battleship::get_player_one() {
	return custom_player;
}

//easy way to acess the AI
AI_player battleship::get_AI_player() {
	return custom_AI;
}

//sets the AI's board
board battleship::set_AI_custom_board(int x, int y) {
	AI = board(x, y);
	return AI;
}

//sets the AI player class
AI_player battleship::set_AI_one(int x, int y) {
	custom_AI = AI_player(set_AI_custom_board(x, y), set_AI_custom_board(x, y));
	return custom_AI;
}

//creates the ships for the game
//if too many ships wnated defaults as 5
void battleship::create_ships(int n) {
	if (n > 5) {
		n = 5;
	}
	//all ships will be lenght 5
	int standard = 3;
	for (int i = n; i > 0; i--) {
		game_ships.push_back(Ships(standard));
	}
}

//easy way to get the ships
std::vector<Ships> battleship::return_game_ships() {
	return game_ships;
}

void battleship::player_fire(int index) {
	//if the index that the player wants to shoot at is a 1 or zero that proper change is done
	if (get_AI_player().return_prime_board().get_point(index) == 1) {
		custom_player.set_point(index, 1);
		custom_AI.set_point(index, 2);

	}
	else if (custom_AI.return_prime_board().get_point(index) == 0) {
		custom_AI.set_point(index, 2);
		custom_player.set_point(index, 2);
	}
}

void battleship::AI_fire() {
	//check aroud is true if the previous shot is hit so whenever the AI wants to look for a new location this is false
	if (!check_around) {
		//finds a index to fire
		int index = custom_AI.find_place_to_fire(game_ships);
		//if index is a hit
		if (custom_player.return_prime_board().get_point(index) == 1) {
			//sets the proper values for AI and player
			custom_AI.set_point_1(index, 1);
			custom_player.get_point(index, 2);
			//will go and check aroung hit
			check_around = true;
			change_direction = true;
			special_switch = false;
			//stores this index as the head index
			head_index = index;
			temp_index = index;
			directions.clear();
			//adds all possible location
			directions.push_back('N');
			directions.push_back('S');
			directions.push_back('E');
			directions.push_back('W');
			
		}
		else {
			//if miss than sets the correct total for AI and player
			custom_player.get_point(index, 2);
			custom_AI.set_point_1(index, 2);
		}
	}
	else {
		//method to check all directions
		direction();
	}
}

void battleship::direction() {
	//this will make sure the AI fires
	make_sure_AI_fires = true;
	//if directions is zero than AI looked at all possible directiosn and its time to look for a new index to fire at
	if (directions.size() == 0) {
		check_around = false;
		make_sure_AI_fires = false;
	}
	//this is only true when it is time for the AI to strart choseing a new direction to fire
	else if (change_direction) {
		random_direction = rand() % directions.size();
	}
	//will go so the AI fires
	while (make_sure_AI_fires) {
		//will only go once the AI fires until it hits a wall and needs to find a new direction to fire at
		if ((special_switch) && (directions.size() != 0)) {
			random_direction = rand() % directions.size();
		}
		//if no directions to fire left than break and find a new index
		if (directions.size() == 0) {
			break;
		}
		//random direction will use one of these 4 methods
		if (directions[random_direction] == 'W') {
			fire_west();
		}

		else if (directions[random_direction] == 'E') {
			fire_east();
		}

		else if (directions[random_direction] == 'N') {
			fire_north();
		}

		else if (directions[random_direction] == 'S') {
			fire_south();
		}
	}
}

//method to fire west of the index the AI is at
void battleship::fire_west() {
	//if the AI can fire the west square it will
	if (custom_AI.check_square_west(temp_index)) {
		temp_index--;
		//if a hit occur then it will change the proper values
		if (custom_player.return_prime_board().get_point(temp_index) == 1) {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 1);
			//it will remove the directions north and south from being hit becaue we already know the ship is horizontal
			directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
			directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
			//will fire random direction to change to the new index of West
			for (int i = 0; i < directions.size(); i++) {
				random_direction = i;
			}
			//keep bool so it keeps running west until miss
			make_sure_AI_fires = false;
			change_direction = false;
			special_switch = false;
		}
		//if miss change values 
		else {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 2);
			//go back to the head_index
			temp_index = head_index;
			//remove west from being picked again and let a new direction be chosen
			directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
			make_sure_AI_fires = false;
			change_direction = true;
			special_switch = false;
		}
	}
	//if you cannot fire west than reset to head_index
	else {
		temp_index = head_index;
		//erase the west direction
		directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
		//and without breaking out of the loop in direction() fire in a new direction
		change_direction = true;
		special_switch = true;
	}
}

//method to fire east of the index the AI is at
void battleship::fire_east() {
	//if the AI can fire the east square it will
	if (custom_AI.check_square_east(temp_index)) {
		temp_index++;
		//if a hit occur then it will change the proper values
		if (custom_player.return_prime_board().get_point(temp_index) == 1) {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 1);
			//it will remove the directions north and south from being hit becaue we already know the ship is horizontal
			directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
			directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
			//will fire random direction to change to the new index of east
			random_direction = 0;
			//keep bool so it keeps running east until miss
			change_direction = false;
			make_sure_AI_fires = false;
			special_switch = false;
		}
		//if miss change values 
		else {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 2);
			//go back to the head_index
			temp_index = head_index;
			//remove east from being picked again and let a new direction be chosen
			directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
			make_sure_AI_fires = false;
			change_direction = true;
			special_switch = false;
		}
	}
	//if you cannot fire west than reset to head_index
	else {
		temp_index = head_index;
		//erase the east direction
		directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
		//and without breaking out of the loop in direction() fire in a new direction
		change_direction = true;
		special_switch = true;
	}
}

//method to fire north of the index the AI is at
void battleship::fire_north() {
	//if the AI can fire the north square it will
	if (custom_AI.check_square_north(temp_index)) {
		temp_index -= playe.get_width();
		//if a hit occur then it will change the proper values
		if (custom_player.return_prime_board().get_point(temp_index) == 1) {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 1);
			//it will remove the directions east and west from being hit becaue we already know the ship is vertcal
			directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
			directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
			//keep bool so it keeps running north until miss
			make_sure_AI_fires = false;
			change_direction = false;
			special_switch = false;
		}
		//if miss change values 
		else {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 2);
			//go back to the head_index
			temp_index = head_index;
			//remove north from being picked again and let a new direction be chosen
			directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
			make_sure_AI_fires = false;
			change_direction = true;
			special_switch = false;
		}
	}
	//if you cannot fire west than reset to head_index
	else {
		temp_index = head_index;
		//erase the north direction
		directions.erase(std::remove(directions.begin(), directions.end(), 'N'), directions.end());
		//and without breaking out of the loop in direction() fire in a new direction
		change_direction = true;
		special_switch = true;
	}
}

//method to fire south of the index the AI is at
void battleship::fire_south() {
	//if the AI can fire the south square it will
	if (custom_AI.check_square_south(temp_index)) {
		temp_index += playe.get_width();
		//if a hit occur then it will change the proper values
		if (custom_player.return_prime_board().get_point(temp_index) == 1) {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 1);
			//it will remove the directions east and west from being hit becaue we already know the ship is vertcal
			directions.erase(std::remove(directions.begin(), directions.end(), 'W'), directions.end());
			directions.erase(std::remove(directions.begin(), directions.end(), 'E'), directions.end());
			//keep bool so it keeps running south until miss
			make_sure_AI_fires = false;
			special_switch = false;
			change_direction = false;
		}
		//if miss change values 
		else {
			custom_player.get_point(temp_index, 2);
			custom_AI.set_point_1(temp_index, 2);
			//go back to the head_index
			temp_index = head_index;
			//remove south from being picked again and let a new direction be chosen
			directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
			make_sure_AI_fires = false;
			change_direction = true;
			special_switch = false;
		}
	}
	//if you cannot fire west than reset to head_index
	else {
		temp_index = head_index;
		//erase the south direction
		directions.erase(std::remove(directions.begin(), directions.end(), 'S'), directions.end());
		//and without breaking out of the loop in direction() fire in a new direction
		change_direction = true;
		special_switch = true;
	}
}

