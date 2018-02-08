//main.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <cstdlib> 
#include <cstdio> 
#include "Image.h"
#include "Read.h"
#include "Write.h"
#include "ZoomImage.h"
#include "ArithmeticSort.h"

//void readPPM(const char* file, Image &img);
//void writePPM(const Image &img, const char* file);

const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(1);
const Image::Rgb Image::kRed = Image::Rgb(1, 0, 0);
const Image::Rgb Image::kGreen = Image::Rgb(0, 1, 0);
const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 1);

int main()
{
	std::cout << "************************************" << std::endl;
	std::cout << "Image Stacker / Image Scaler" << std::endl;
	std::cout << "************************************" << std::endl;

	//****************************************************
	//As an example, read one ppm file and write it out to testPPM.ppm
	//We need to specify the dimensions of the image
	//****************************************************
	Read reader;
	Write writer;
	ArithmeticSort stat;
	Image *zoomImageX2 = new ZoomImage(750, 750);
	Image *zoomImageX4 = new ZoomImage(750, 750);
	Image *bilinear = new ZoomImage(750, 750);
	Image *img = new Image(3264, 2448);
	Image *meanImg = new Image(3264, 2448);
	Image *medianImg = new Image(3264, 2448);
	Image *stanDeviImg = new Image(3264, 2448);

	std::vector <std::vector<float> > redPixels(13, std::vector<float>(3264 * 2448, NULL));
	std::vector <std::vector<float> > greenPixels(13, std::vector<float>(3264 * 2448, NULL));
	std::vector <std::vector<float> > bluePixels(13, std::vector<float>(3264 * 2448, NULL));
	std::vector <std::vector<float> > meanVector(3, std::vector<float>(3264 * 2448, NULL));
	std::vector <std::vector<float> > medianVector(3, std::vector<float>(3264 * 2448, NULL));
	std::vector <std::vector<float> > stanDeviVector(3, std::vector<float>(3264 * 2448, NULL));

	reader.readPPM("Images/ImageStacker_set1/IMG_1.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 0);
	reader.readPPM("Images/ImageStacker_set1/IMG_2.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 1);
	reader.readPPM("Images/ImageStacker_set1/IMG_3.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 2);
	reader.readPPM("Images/ImageStacker_set1/IMG_4.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 3);
	reader.readPPM("Images/ImageStacker_set1/IMG_5.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 4);
	reader.readPPM("Images/ImageStacker_set1/IMG_6.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 5);
	reader.readPPM("Images/ImageStacker_set1/IMG_7.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 6);
	reader.readPPM("Images/ImageStacker_set1/IMG_8.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 7);
	reader.readPPM("Images/ImageStacker_set1/IMG_9.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 8);
	reader.readPPM("Images/ImageStacker_set1/IMG_10.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 9);
	reader.readPPM("Images/ImageStacker_set1/IMG_11.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 10);
	reader.readPPM("Images/ImageStacker_set1/IMG_12.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 11);
	reader.readPPM("Images/ImageStacker_set1/IMG_13.ppm", *img);
	stat.printVector(redPixels, greenPixels, bluePixels, *img, 12);

	reader.readPPM("Images/Zoom/zIMG_1.ppm", *zoomImageX2);
	*zoomImageX2 = stat.nearNZoom(zoomImageX2, zoomImageX2->w, zoomImageX2->h, zoomImageX2->w * 2, zoomImageX2->h * 2);
	writer.writePPM(*zoomImageX2, "NewImages/ZOOMX2PPM.ppm");

	reader.readPPM("Images/Zoom/zIMG_1.ppm", *zoomImageX4);
	*zoomImageX4 = stat.nearNZoom(zoomImageX4, zoomImageX4->w, zoomImageX4->h, zoomImageX4->w * 4, zoomImageX4->h * 4);
	writer.writePPM(*zoomImageX4, "NewImages/ZOOMX4PPM.ppm");

	reader.readPPM("Images/Zoom/zIMG_1.ppm", *bilinear);
	*bilinear = stat.bilinearZoom(bilinear, bilinear->w, bilinear->h, bilinear->w * 2, bilinear->h * 2);
	writer.writePPM(*bilinear, "NewImages/BILINEARPPM.ppm");

	std::cout << "Filling mean vector" << std::endl;
	stat.fillMeanVector(redPixels, meanVector, 0);
	stat.fillMeanVector(greenPixels, meanVector, 1);
	stat.fillMeanVector(bluePixels, meanVector, 2);
	stat.assignImage(*meanImg, meanVector);
	writer.writePPM(*meanImg, "NewImages/MEANPPM.ppm");

	std::cout << "Filling median vector" << std::endl;
	stat.fillMedianVector(redPixels, medianVector, 0);
	stat.fillMedianVector(greenPixels, medianVector, 1);
	stat.fillMedianVector(bluePixels, medianVector, 2);
	stat.assignImage(*medianImg, medianVector);
	writer.writePPM(*medianImg, "NewImages/MEDIANPPM.ppm");

	float sigmaFactor;
	std::cout << "Enter sigma value:" << std::endl;
	std::cin >> sigmaFactor;
	
	std::cout << "Filling standard deviation vector" << std::endl;
	stat.fillStanDeviVector(redPixels, meanVector, medianVector, stanDeviVector, 0, sigmaFactor);
	stat.fillStanDeviVector(greenPixels, meanVector, medianVector, stanDeviVector, 1, sigmaFactor);
	stat.fillStanDeviVector(bluePixels, meanVector, medianVector, stanDeviVector, 2, sigmaFactor);
	stat.assignImage(*stanDeviImg, stanDeviVector);
	writer.writePPM(*stanDeviImg, "NewImages/STANDEVIPPM.ppm");

	Image newImg = *img;
	float brightLevel;
	std::cout << "Enter a brightness value, it will produce a new image with these brightness alterations" << std::endl;
	std::cin >> brightLevel;
	newImg + brightLevel;
	writer.writePPM(newImg, "NewImages/BRIGHTPPM.ppm");

	meanImg->displayInformation("NewImages/ImageInfo/MEANINFO.txt");
	medianImg->displayInformation("NewImages/ImageInfo/ZOOMX2INFO.txt");
	stanDeviImg->displayInformation("NewImages/ImageInfo/STANDEVIINFO.txt");
	zoomImageX2->displayInformation("NewImages/ImageInfo/ZOOMX2INFO.txt", 2);
	zoomImageX4->displayInformation("NewImages/ImageInfo/ZOOMX4INFO.txt", 4);
	bilinear->displayInformation("NewImages/ImageInfo/BILINEARINFO.txt", 2);

	delete zoomImageX2;
	delete zoomImageX4;
	delete bilinear;
	delete img;
	delete meanImg;
	delete medianImg;
	delete stanDeviImg;

	system("pause");

	return 0;
}

//float standardDeviation(std::vector< std::vector<float> >vec, int pixel)
//{
//	float sum = 0, standardDeviation = 0, mean;
//
//	for (int i = 0; i < 13; i++)
//	{
//		sum += vec[i][pixel];
//	}
//	mean = sum / 13;
//	for (int i = 0; i < 13; i++)
//	{
//		standardDeviation += pow(vec[i][pixel] - mean, 2);
//	}
//	return sqrt(standardDeviation / 13);
//}

//You can access the individual pixel data
//This accesses and writes out the r, g, b pixel values for the first pixel
//Values are multiplied by 255 as they are 'clamped' between 0 and 1
//std::cout << (img.pixels[0].r)*255 << std::endl;
//std::cout << (img.pixels[0].g)*255 << std::endl;
//std::cout << (img.pixels[0].b)*255 << std::endl;

//std::cout << redPixels[6][140] << std::endl;
//std::cout << greenPixels[6][140] << std::endl;
//std::cout << bluePixels[6][140] << std::endl;