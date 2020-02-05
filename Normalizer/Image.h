#pragma once

#include <vector>
#include <string>

class Pixel {
public:
	uint8_t R;
	uint8_t G;
	uint8_t B;
	Pixel(uint8_t, uint8_t, uint8_t);
	Pixel();
};

class Image {
public:
	Image(const int, const int, int);
	Image();
	Image(const Image&);
	void operator=(const Image&);
	int getSize();
	void setPixel(uint8_t*);
	void setPixel(Pixel, int);
	Pixel getPixel(int);
	std::string getInfo();
private:
	int N;
	int M;
	int maxL;
	std::vector<Pixel> imgMap;
};