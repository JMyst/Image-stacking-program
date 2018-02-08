#include "ArithmeticSort.h"

ArithmeticSort::ArithmeticSort()
{
}

void ArithmeticSort::printVector(std::vector< std::vector<float> > &red, std::vector< std::vector<float> > &green, std::vector< std::vector<float> > &blue, Image &img, int row)
{
	for (int i = 0; i < (img.w * img.h); i++)
	{
		red[row][i] = img.pixels[i].r * 255;
		green[row][i] = img.pixels[i].g * 255;
		blue[row][i] = img.pixels[i].b * 255;
	}
}

void ArithmeticSort::fillMeanVector(std::vector< std::vector<float> > &vec, std::vector< std::vector<float> > &meanVec, int colour)
{
	int sum = 0;
	for (int i = 0; i < (3264 * 2448); i++)
	{
		sum = 0;

		for (int j = 0; j < 13; j++)
			sum += vec[j][i];

		meanVec[colour][i] = sum / 13.f;
	}
}

void ArithmeticSort::fillMedianVector(std::vector< std::vector<float> > &vec, std::vector< std::vector<float> > &medianVec, int colour)
{
	std::vector<float>tempVector(13, NULL);

	for (int i = 0; i < (3264 * 2448); i++)
	{
		for (int j = 0; j < 13; j++)
		{
			tempVector[j] = vec[j][i];
		}
		std::sort(tempVector.begin(), tempVector.end());
		medianVec[colour][i] = tempVector[7];
	}
}

void ArithmeticSort::assignImage(Image &img, std::vector <std::vector<float> > &sortVec)
{
	for (int i = 0; i < (img.w * img.h); i++)
	{
		img.pixels[i].r = sortVec[0][i] / 255.f;
		img.pixels[i].g = sortVec[1][i] / 255.f;
		img.pixels[i].b = sortVec[2][i] / 255.f;
	}
}

void ArithmeticSort::fillStanDeviVector(std::vector< std::vector<float> > &vec, std::vector< std::vector<float> > &meanVec, std::vector< std::vector<float> > &medianVec, std::vector< std::vector<float> > &stanDeviVec, int colour, float sigmaFactor)
{
	std::vector<float>tempVector(13, NULL);
	std::vector<float>sigmaVector;
	float sum = 0;
	float sigmaSum = 0;
	float max;
	float min;

	for (int i = 0; i < 3264 * 2448; i++)
	{
		sigmaVector.clear();
		sum = 0;
		sigmaSum = 0;

		for (int j = 0; j < 13; j++)
		{
			tempVector[j] = vec[j][i] - meanVec[colour][i];
			tempVector[j] = pow(tempVector[j], 2);
			sum += tempVector[j];
		}

		max = meanVec[colour][i] + ((std::sqrt((sum / 13.f))) * sigmaFactor); //Can be altered through sigma factor such as 0.5
		min = meanVec[colour][i] - ((std::sqrt((sum / 13.f))) * sigmaFactor); //Can be altered through sigma factor such as 0.5

		for (int j = 0; j < 13; j++)
		{
			if (vec[j][i] < max && vec[j][i] > min)
				sigmaVector.push_back(vec[j][i]);
		}
		for (std::vector<float>::iterator it = sigmaVector.begin(); it != sigmaVector.end(); ++it)
		{
			sigmaSum += *it;

		}
		if (sigmaSum == 0)
		{
			//If all values are the same, sigmaSum will return empty
			//Set to a default value
			stanDeviVec[colour][i] = vec[0][i];
		}
		else
		{
			stanDeviVec[colour][i] = sigmaSum / sigmaVector.size();
		}
	}
}

Image ArithmeticSort::nearNZoom(Image *zoomImage, int w1, int h1, int w2, int h2)
{

	std::cout << "Calculating nearest neighbour zoom image" << std::endl;
	Image *newZoom = new Image(w2, h2);
	double x_ratio = w1 / (double)w2;
	double y_ratio = h1 / (double)h2;
	double px, py;
	for (int i = 0; i < h2; i++)
	{
		for (int j = 0; j < w2; j++)
		{
			px = floor(j * x_ratio);
			py = floor(i * y_ratio);
			newZoom->pixels[(i * w2) + j] = zoomImage->pixels[(int)((py * w1) + px)];
		}
	}
	return *newZoom;
}

Image ArithmeticSort::bilinearZoom(Image *bilinearZoom, int w, int h, int w2, int h2)
{
	std::cout << "Calculating bilinear zoom image" << std::endl;
	Image *temp = new Image(w2, h2);
	Image::Rgb A, B, C, D, colour;
	int x, y, index;
	float x_ratio = ((float)(w - 1)) / w2;
	float y_ratio = ((float)(h - 1)) / h2;
	float x_diff, y_diff;
	int offset = 0;
	for (int i = 0; i < h2; i++) {
		for (int j = 0; j < w2; j++) {
			x = (int)(x_ratio * j);
			y = (int)(y_ratio * i);
			x_diff = (x_ratio * j) - x;
			y_diff = (y_ratio * i) - y;
			index = y * w + x;

			A = bilinearZoom->pixels[index];
			B = bilinearZoom->pixels[index + 1];
			C = bilinearZoom->pixels[index + w];
			D = bilinearZoom->pixels[index + w + 1];

			colour.r = (A.r*(1 - x_diff)*(1 - y_diff) + B.r*(x_diff)*(1 - y_diff) + C.r*(y_diff)*(1 - x_diff) + D.r*(x_diff*y_diff));
			colour.g = (A.g*(1 - x_diff)*(1 - y_diff) + B.g*(x_diff)*(1 - y_diff) + C.g*(y_diff)*(1 - x_diff) + D.g*(x_diff*y_diff));
			colour.b = (A.b*(1 - x_diff)*(1 - y_diff) + B.b*(x_diff)*(1 - y_diff) + C.b*(y_diff)*(1 - x_diff) + D.b*(x_diff*y_diff));

			offset++;
			temp->pixels[offset].r = colour.r;
			temp->pixels[offset].g = colour.g;
			temp->pixels[offset].b = colour.b;
		}
	}
	return *temp;
}

ArithmeticSort::~ArithmeticSort()
{
}
