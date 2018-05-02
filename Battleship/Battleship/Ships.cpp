#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Ships.h"



/*
default consturcter
*/
Ships::Ships()
{
	length = 3;
}

/*
allows ships of any length
*/
Ships::Ships(int len) {
	length = len;
}

/*
gets length of ship
*/
int Ships::getLength() {
	return length;
}


