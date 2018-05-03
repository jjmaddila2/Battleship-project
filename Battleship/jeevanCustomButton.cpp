#pragma once
#include "ofxButton.h"
#include "jeevanCustomButton.h"
/*
callback method so my buttons will work on impact and give me the index
*/
void jeevanCustomButton::add_callback(std::function<void(std::string)> callback) {
	this->func = callback;
	value.addListener(this, &jeevanCustomButton::value_changed);
}

/*
gets the actual index here and says that the button is pressed
*/
void jeevanCustomButton::value_changed(bool& b) {
	if (!b) {
		func(this->getName());
	}
}
