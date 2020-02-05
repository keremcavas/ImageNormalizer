#pragma once

#include "Image.h"
#include <string>
#include <fstream>
#include <iostream>

class Reader {
public:
	void readImageInfo(std::string);
	void readImage();
	Reader();
	Image getImage();
private:
	Image img;
	std::ifstream inStream;
	std::string fileName;
};