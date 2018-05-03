#include "ofMain.h"
#include "ofApp.h"
#include "battleship.h"


//========================================================================

int main() {
	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context

									// this kicks off the running of my app
													// can be OF_WINDOW or OF_FULLSCREEN
													// pass in width and height too:
	ofRunApp(new ofApp());
	//player new_player = game.set_player_one(10, 10);
	//AI_player aI = game.set_AI_one(10, 10);
	//new_player.return_prime_board().print_board();


}
