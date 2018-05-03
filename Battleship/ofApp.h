#pragma once
#pragma once
#include <cstdlib>
#include <utility>

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

#include "ofMain.h"
#include "ofxGui.h"
#include "jeevanCustomButton.h"
#include "battleship.h"




class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void change_color();
	void button_pressed_north();
	void button_pressed_east();
	void button_pressed_west();
	void button_pressed_south();
	void one(std::string);
	void two(std::string);
	bool check_vector();

	ofxButton north;
	ofxButton south;
	ofxButton east;
	ofxButton west;
	std::deque<jeevanCustomButton> board_one;
	std::deque<jeevanCustomButton> board_two;
	std::vector<int> hold_index;
	std::vector<int> directions;
	battleship game;
	board board_to_shoot;
	std::vector<Ships> ships;
	int index;
	int number_of_ships;
	int x_pos = 100;
	int y_pos = 100;
	int x2_pos = 900;
	bool place_ships = true;
	bool first_time_in_update = true;
	bool start_firing = false;
	bool AI_wins = false;
	bool player_wins = false;
	bool read_placing_rules = true;
	bool shooting_rules = false;
	ofSoundPlayer winner;
	ofSoundPlayer loser;
	ofSoundPlayer backround;
};
