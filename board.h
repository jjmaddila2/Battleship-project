#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>


using std::string;
using std::map;
using std::cin;
using std::cout;

	class board {
	public:
		board::board();
		board::board(int w, int h);
		void set_point(int index, int value);
		int get_height();
		int get_width();
		int get_point(int index);
		bool is_winner();
		std::vector<int> getMat();
		std::vector<int> board_dim;
	};
