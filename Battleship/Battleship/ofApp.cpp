#include "ofApp.h"
#include <iostream>
#include <string>
#include <sstream>

//--------------------------------------------------------------
void ofApp::gay(std::string n) {
	std::cout << n << std::endl;
	hold_index.push_back(stoi(n));
}

void ofApp::two(std::string n) {
	std::cout << n << std::endl;
	hold_index.push_back(stoi(n));
}

void ofApp::setup() {	
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
	ofSetBackgroundColorHex(0x737CA1);
	for (int i = 0; i < board_to_shoot.get_height(); i++) {
		x_pos = 200;
		for (int j = 0; j < board_to_shoot.get_width(); j++) {
			board_one.push_back(jeevanCustomButton());
			index = board_to_shoot.get_width() * i + j;
			std::string s = std::to_string(index);
			board_one.back().setup(s, 70, 70);
			board_one.back().setPosition(x_pos, y_pos);
			board_one.back().setBackgroundColor(0xFFFFFF);
			board_one.back().add_callback([this](std::string n) {this->gay(n);});
			board_one.back().setTextColor(0x0);
			x_pos += 70;
		}
		y_pos += 70;
	}
	y_pos = 100;
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
	game.create_ships(5);
	game.set_AI_one(10, 10);
	game.set_player_one(10, 10);
	directions.push_back(1);
}

bool ofApp::check_vector() {
	if (hold_index.size() <= 0) {
		return false;
	}
	return true;
}

bool ofApp::check_vector1() {
	if (hold_index.size() <= 0) {
		return false;
	}
	return true;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (wow) {
		ships = game.return_game_ships();
		n = 6;
		wow = false;
	}
	//int number;
	if (place_ships) {	
		if (check_vector()) {
			//directions.clear();
			int height = -1;
			while (hold_index[0] >= 0) {
				hold_index[0] -= 10;
				height++;
			}
			int width = hold_index[0] + 10;
			int ship = ships.size() - 1;
			if (n != 6) {
				if (directions.size() != 0 && hold_index.size() != 0) {
					if (game.get_player_one().place_ship(game.return_game_ships()[n - 1], width, height, directions[0])) {}
					else {
						n++;
					}
				}
			}
			else {
				hold_index.clear();
				directions.clear();
			}
			if (directions.size() != 0 && hold_index.size() != 0) {
				hold_index.clear();
				directions.clear();
			}
			n--;
			}
		if (n == 0) {
			read_placing_rules = false;
			shooting_rules = true;
			place_ships = false;
			start_firing = true;
			cout<<"\n" << game.return_game_ships().size() << " hoola" << "\n";
			game.get_AI_player().place_ships(game.return_game_ships());
			cout << "wow";
		}
	}
	if (start_firing) {
		if (check_vector()) {
				game.player_fire(hold_index[0]);
				hold_index.clear();
				if (game.get_AI_player().return_prime_board().is_winner()) {
					start_firing = false;
					player_wins = true;
					shooting_rules = false;
				}
				game.AI_fire();
				if (game.get_player_one().return_prime_board().is_winner()) {
					start_firing = false;
					AI_wins = true;
					shooting_rules = false;
				}
		}
	}
	//game.AI_fire();
	change_color();
	//draw();
}

void ofApp::change_color() {
	
	cout << "\n";
	vector<int> board_player_first = game.get_player_one().return_prime_board().getMat();
	for (int i = 0; i < game.get_player_one().return_prime_board().getMat().size(); i++) {
		if (game.get_player_one().return_prime_board().get_point(i) == 2) {
			board_one[i].setBackgroundColor(0xE67451);
		}
		if (game.get_player_one().return_prime_board().get_point(i) == 1) {
			cout << i << "\n";
			board_one[i].setBackgroundColor(0x0);
		}
	}
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
	for (int i = board_one.size() - 1; i >= 0 ; i--) {
		board_one.at(i).draw();
		board_two.at(i).draw();
	}
	north.draw();
	south.draw();
	east.draw();
	west.draw();
	ofSetColor(0, 0, 0);
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

void ofApp::button_pressed_north() {
	directions.push_back(0);
}

void ofApp::button_pressed_south() {
	directions.push_back(1);
}

void ofApp::button_pressed_west() {
	directions.push_back(3);
}

void ofApp::button_pressed_east() {
	directions.push_back(2);
}

