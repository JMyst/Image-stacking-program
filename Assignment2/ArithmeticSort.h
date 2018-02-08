#pragma once
#include "Image.h"
#include <vector>
#include <algorithm>

class ArithmeticSort
{
public:
	ArithmeticSort();

	void printVector(std::vector< std::vector<float> > &red, std::vector< std::vector<float> > &green, std::vector< std::vector<float> > &blue, Image &img, int row);
	void fillMeanVector(std::vector< std::vector<float> > &vec, std::vector< std::vector<float> > &meanVec, int colour);
	void fillMedianVector(std::vector< std::vector<float> > &vec, std::vector< std::vector<float> > &medianVec, int medianCount);
	void fillStanDeviVector(std::vector< std::vector<float> > &vec, std::vector< std::vector<float> > &meanVec, std::vector< std::vector<float> > &medianVec, std::vector< std::vector<float> > &stanDeviVec, int colour, float sigmaFactor);
	void assignImage(Image &img, std::vector <std::vector<float> > &sortVec);
	Image nearNZoom(Image *zoomImage, int w1, int h1, int w2, int h2);
	Image bilinearZoom(Image *bilinearZoom, int w, int h, int w2, int h2);

	~ArithmeticSort();
};

