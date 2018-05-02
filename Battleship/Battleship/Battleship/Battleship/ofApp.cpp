#include "ofApp.h"
#include <iostream>
#include <string>
#include <sstream>

//--------------------------------------------------------------
//button method for when you press the left board
void ofApp::one(std::string n) {
	//pushes the index of teh pressed button to the vector
	hold_index.push_back(stoi(n));
}

//button method for when you press the right board
void ofApp::two(std::string n) {
	//pushes the index of the pressed button to the vector
	hold_index.push_back(stoi(n));
}

void ofApp::setup() {
	//cretes the button for all 4 directions and sets up the button method for all four
	north.setBackgroundColor(0xB4CFEC);
	north.setup("North", 100, 30);
	north.setPosition(650, 900);
	north.addListener(this,&ofApp::button_pressed_north);
	south.setBackgroundColor(0xB4CFEC);
	south.setup("South", 100, 30);
	south.setPosition(800, 900);
	south.addListener(this, &ofApp::button_pressed_south);
	east.setBackgroundColor(0xB4CFEC);
	east.setup("East", 100, 30);
	east.setPosition(950, 900);
	east.addListener(this, &ofApp::button_pressed_east);
	west.setBackgroundColor(0xB4CFEC);
	west.setup("Wast", 100, 30);
	west.setPosition(1100, 900);
	west.addListener(this, &ofApp::button_pressed_west);
	//sets the backround color of the screen
	ofSetBackgroundColorHex(0x737CA1);
	//creates the cordinate system of the left board
	for (int i = 0; i < board_to_shoot.get_height(); i++) {
		x_pos = 200;
		for (int j = 0; j < board_to_shoot.get_width(); j++) {
			//adds all buttons
			board_one.push_back(jeevanCustomButton());
			//formula to convert cordinate point to index
			index = board_to_shoot.get_width() * i + j;
			std::string s = std::to_string(index);
			//name of button represnets button index
			board_one.back().setup(s, 70, 70);
			board_one.back().setPosition(x_pos, y_pos);
			board_one.back().setBackgroundColor(0xFFFFFF);
			board_one.back().add_callback([this](std::string n) {this->one(n);});
			board_one.back().setTextColor(0x0);
			x_pos += 70;
		}
		y_pos += 70;
	}
	y_pos = 100;
	//creates the cordinate system of buttons for the right board
	for (int i = 0; i < board_to_shoot.get_height(); i++) {
		x2_pos = 1000;
		for (int j = 0; j < board_to_shoot.get_width(); j++) {
			index = board_to_shoot.get_width() * i + j;
			board_two.push_back(jeevanCustomButton());
			board_two.back().add_callback([this](std::string n) {this->two(n); });
			board_two.back().setTextColor(0x0);
			std::string s = std::to_string(index);
			board_two.back().setup(s, 70, 70);
			board_two.back().setPosition(x2_pos, y_pos);
			board_two.back().setBackgroundColor(0xFFFFFF);
			x2_pos += 70;
		}
		y_pos += 70;
	}
	//creates the ships and the dimensions of the board 
	game.create_ships(5);
	game.set_AI_one(10, 10);
	game.set_player_one(10, 10);
}

//method to see if button of cordinates system has been pressed
bool ofApp::check_vector() {
	if (hold_index.size() <= 0) {
		return false;
	}
	return true;
}

//--------------------------------------------------------------
void ofApp::update() {
	//values to set the first time through update
	if (first_time_in_update) {
		ships = game.return_game_ships();
		number_of_ships = 6;
		first_time_in_update = false;
	}
	//if statment where ships will be placed
	if (place_ships) {	
		//if button has pressed continue
		if (check_vector()) {
			//convert index to x, y coordinate
			int height = -1;
			while (hold_index[0] >= 0) {
				hold_index[0] -= 10;
				height++;
			}
			int width = hold_index[0] + 10;
			int ship = ships.size() - 1;
			//for some reason when the game starts the button automatically sets at zero so it passes through that with this if
			if (number_of_ships != 6) {
				//if player has chosen a direction and a button than ship is placed if it can
				if (directions.size() != 0 && hold_index.size() != 0) {
					if (game.get_player_one().place_ship(game.return_game_ships()[number_of_ships - 1], width, height, directions[0])) {}
					//if it cannot be placed it basiclly continues
					else {
						number_of_ships++;
					}
				}
			}
			//if n = 6 resets both buttons and sets them to nothing 
			else {
				hold_index.clear();
				directions.clear();
			}
			//if both a button and direction was pressed than a ship was placed and both vectors are cleared
			if (directions.size() != 0 && hold_index.size() != 0) {
				hold_index.clear();
				directions.clear();
			}
			//decreases the number of ships by one
			number_of_ships--;
			}
		//if number of ships goes to zero it will stop placing ships and stop reading the rules for placing ships
		//then it will let firing start while reading the firing rules
		if (number_of_ships == 0) {
			read_placing_rules = false;
			shooting_rules = true;
			place_ships = false;
			start_firing = true;
			//it also places the AI ships here
			game.get_AI_player().place_ships(game.return_game_ships());
		}
	}
	//once placing ships is done then the firing can begin
	if (start_firing) {
		//again will strat with seeing if an button was pressed
		if (check_vector()) {
			//if so it will fire at that index and clear the button que
				game.player_fire(hold_index[0]);
				hold_index.clear();
				//then checks if player has won, if yes than reads that the player wins and stops the game
				if (game.get_AI_player().return_prime_board().is_winner()) {
					start_firing = false;
					player_wins = true;
					shooting_rules = false;
				}
				//lets the AI_fire
				game.AI_fire();
				//then checks if the AI has won
				if (game.get_player_one().return_prime_board().is_winner()) {
					start_firing = false;
					AI_wins = true;
					shooting_rules = false;
				}
		}
	}
	//will change color of the corrct square and then draw
	change_color();
}

void ofApp::change_color() {
	//goes through the board of buttons and if the board has a one or two for an index than it will change the color of the button
	for (int i = 0; i < game.get_player_one().return_prime_board().getMat().size(); i++) {
		if (game.get_player_one().return_prime_board().get_point(i) == 2) {
			board_one[i].setBackgroundColor(0xE67451);
		}
		if (game.get_player_one().return_prime_board().get_point(i) == 1) {
			cout << i << "\n";
			board_one[i].setBackgroundColor(0x0);
		}
	}
	//same thing but for board two
	for (int i = 0; i < game.get_player_one().return_second_board().getMat().size(); i++) {
		if (game.get_player_one().return_second_board().get_point(i) == 2) {
			board_two[i].setBackgroundColor(0xE67451);
		}
		if (game.get_player_one().return_second_board().get_point(i) == 1) {
			board_two[i].setBackgroundColor(0x0);
		}
	}
}
//--------------------------------------------------------------
void ofApp::draw() {
	//will draw the boards
	for (int i = board_one.size() - 1; i >= 0 ; i--) {
		board_one.at(i).draw();
		board_two.at(i).draw();
	}
	//then draws the buttons
	north.draw();
	south.draw();
	east.draw();
	west.draw();
	//sets the color of the text
	ofSetColor(0, 0, 0);
	//will print the correct output depending on what part of the game the user is on
	if (player_wins) {
		ofDrawBitmapString("Human Player Wins", 880, 850);
	}
	if (AI_wins) {
		ofDrawBitmapString("AI Wins", 900, 850);
	}
	if (read_placing_rules) {
		ofDrawBitmapString("To place ships, First choose a direction and than choose square to place it", 650, 850);
	}
	if (shooting_rules) {
		ofDrawBitmapString("To fire click and square, your results will appear on the left screen", 675, 850);
	}
}

//button method for north button
void ofApp::button_pressed_north() {
	directions.push_back(0);
}

//button method for south button
void ofApp::button_pressed_south() {
	directions.push_back(1);
}

//button method for west button
void ofApp::button_pressed_west() {
	directions.push_back(3);
}

//button method for east button
void ofApp::button_pressed_east() {
	directions.push_back(2);
}

