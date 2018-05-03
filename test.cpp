#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "battleship.hpp"


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

using std::string;
using std::map;
using std::cin;
using std::cout;
battleship game;
board fun;
TEST_CASE("create_ships_method") {
    game.create_ships(5);
    REQUIRE(game.return_game_ships().size() == 5);
}

TEST_CASE("board_constructer") {
    game.set_player_one(10,10);
    REQUIRE(game.get_player_one().return_prime_board().get_height() == 10);
    REQUIRE(game.get_player_one().return_prime_board().get_width() == 10);
}

TEST_CASE("AI_constructer") {
    game.set_AI_one(10,10);
    REQUIRE(game.get_AI_player().return_prime_board().get_height() = 10);
    REQUIRE(game.get_AI_player().return_prime_board().get_width() = 10);
}

TEST_CASE("test_get_height_and_width") {
    REQUIRE(fun.get_height() == 10);
    REQUIRE(fun.get_width() == 10);
    REQUIRE(fun.is_winner() == true);
}

TEST_CASE("test_is_winner") {
    REQUIRE(fun.is_winner() == true);
    fun.set_point(25, 1);
    REQUIRE(fun.is_winner() == false);
}

TEST_CASE("test_set_and_get_point") {
    REQUIRE(fun.get_point(0) == 0);
    fun.set_point(0,1);
    REQUIRE(fun.get_point(0) == 1);
}