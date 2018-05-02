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
	void gay(std::string);
	void two(std::string);
	bool check_vector();
	bool check_vector1();

	ofxButton gui;
	ofxButton north;
	ofxButton south;
	ofxButton east;
	ofxButton west;
	//ofxButton temp_button;
	std::deque<jeevanCustomButton> board_one;
	std::deque<jeevanCustomButton> board_two;
	std::vector<int> hold_index;
	std::vector<int> directions;
	battleship game;
	board board_to_shoot;
	std::vector<Ships> ships;
	int index;
	int n;
	int h;
	int x_pos = 100;
	int y_pos = 100;
	int x2_pos = 900;
	bool place_ships = true;
	bool wow = true;
	bool start_firing = false;
	bool AI_wins = false;
	bool player_wins = false;
	bool read_placing_rules = true;
	bool shooting_rules = false;
};
