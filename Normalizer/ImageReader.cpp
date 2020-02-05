#include "ImageReader.h"

void Reader::readImageInfo(std::string fileName) {
	std::cout << "Reading file info...";
	inStream.open(fileName, std::ifstream::in | std::ifstream::binary);
	if (!inStream) {
		std::cout << "Couldn't open file" << std::endl;
		return;
	}
	char tempRead[4];
	char tempChar;
	int n, m, maxL;
	inStream.getline(tempRead, 100, '\n');
	if (tempRead[0] != 'P' || tempRead[1] != '6') {
		std::cout << "Image file format must be PPM" << std::endl;
		return;
	}
	tempChar = inStream.get();
	while (tempChar < '0' || tempChar > '9') {
		tempChar = inStream.get();
	}
	inStream.unget();
	inStream >> m >> n >> maxL;
	inStream.get();
	std::cout << "done" << std::endl;
	img = Image(n, m, maxL);
}

void Reader::readImage() {
	std::cout << "[0%] Reading image file... ";
	int imgSize = img.getSize();
	uint8_t *bufferImage = (uint8_t*)new uint8_t[imgSize * 3];
	inStream.read(reinterpret_cast<char *>(bufferImage), imgSize * 3);
	for (int i = 0; i < imgSize; i++) {
		std::cout << "\r[" << static_cast<int>(100 * (float)i / imgSize) << "%] Reading image file... ";
		img.setPixel(&bufferImage[3 * i]);
	}
	inStream.close();
	std::cout << "\r[100%] Reading image file... done" << std::endl;
}

Reader::Reader() {
}

Image Reader::getImage() {
	return img;
}