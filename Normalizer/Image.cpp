#include "Image.h"

Image::Image(int numRow, int numCol, int maxLevel) {
	N = numRow;
	M = numCol;
	maxL = maxLevel;
}

Image::Image() {

}

Image::Image(const Image& tempImage) {
	N = tempImage.N;
	M = tempImage.M;
	maxL = tempImage.maxL;
	imgMap = tempImage.imgMap;
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) {
	R = r;
	G = g;
	B = b;
}

Pixel::Pixel() {
	R = G = B = 0;
}

void Image::operator=(const Image& tempImg){
	N = tempImg.N;
	M = tempImg.M;
	maxL = tempImg.maxL;
	imgMap.assign(tempImg.imgMap.begin(), tempImg.imgMap.end());	
}

int Image::getSize() {
	return N * M;
}

void Image::setPixel(uint8_t* curAdress) {
	Pixel curPixel(*curAdress, *(curAdress + 1), *(curAdress + 2));
	imgMap.push_back(curPixel);
}

void Image::setPixel(Pixel pixel, int position) {
	imgMap[position] = pixel;
}

Pixel Image::getPixel(int position) {
	return imgMap[position];
}

std::string Image::getInfo() {
	return std::to_string(M) + ' ' + std::to_string(N) + '\n' + std::to_string(maxL);
}