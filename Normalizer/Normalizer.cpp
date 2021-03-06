﻿// Normalizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ImageReader.h"
#include "Image.h"
#include <iostream>
#include <vector>
#include <string>

void getColors(std::vector<Pixel> &colors, std::string filename) {
	std::cout << "Reading colors... ";
	std::ifstream inFile(filename, std::ifstream::in);
	Pixel curColor;
	int curValue;
	while (inFile >> curValue) {
		curColor.R = curValue;
		inFile >> curValue;
		curColor.G = curValue;
		inFile >> curValue;
		curColor.B = curValue;
		colors.push_back(curColor);
	}
	std::cout << "done (" << colors.size() << " colors read)" << std::endl;
}

int distanceBetweenColors(Pixel a, Pixel b) {
	return sqrt(pow(a.R - b.R, 2) + pow(a.G - b.G, 2) + pow(a.B - b.B, 2));
}

void normalizeImage(Image &image, std::vector<Pixel> &colors) {
	std::cout << "[0%] Normalizing image... ";
	int minDist, t;
	Pixel closestColor;
	for (int i = 0, imgSize = image.getSize(); i < imgSize; i++) {
		minDist = 1e9;
		for (Pixel j : colors) {
			t = distanceBetweenColors(image.getPixel(i), j);
			if (t < minDist) {
				minDist = t;
				closestColor = j;
			}
		}
		image.setPixel(closestColor, i);
		std::cout << "\r[" << static_cast<int>(100 * (float)i / imgSize) << "%] Normalizing image... ";
	}
	std::cout << "\r[100%] Normalizing image... done" << std::endl;
}

void makeImageFile(Image &image) {
	std::cout << "Creating new file..." << std::endl;
	std::filebuf fb;
	fb.open("color.ppm", std::ios::out || std::ios::binary);
	std::ofstream outFile("finalImage.ppm", std::ofstream::binary);
	outFile << "P6" << std::endl;
	outFile << image.getInfo() << std::endl;
	for (int i = 0, imgSize = image.getSize(); i < imgSize; i++) {
		outFile << image.getPixel(i).R << image.getPixel(i).G << image.getPixel(i).B;
	}
}

int main()
{
	Reader reader;
	Image image;
	std::vector<Pixel> colorVector;
	std::string imgFileName, colorsFileName;
	std::cout << "Original image file name: ";
	std::cin >> imgFileName;
	std::cout << "Colors list file name: ";
	std::cin >> colorsFileName;
	reader.readImageInfo(imgFileName);
	reader.readImage();
	image = Image(reader.getImage());
	getColors(colorVector, colorsFileName);
	normalizeImage(image, colorVector);
	makeImageFile(image);
	std::cout << "finalImage.ppm created succesfully!\n";
}
