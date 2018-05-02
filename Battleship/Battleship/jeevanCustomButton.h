#pragma once
#include "ofxButton.h"
class jeevanCustomButton : public ofxButton {
	private:

		std::function<void(std::string)> func;

	public:
		void add_callback(std::function<void(std::string)>);
		void value_changed(bool&);
};