#pragma once
//*********************************************
//Image class to hold and allow manipulation of images once read into the code
//from https://www.scratchapixel.com/
//*********************************************
#include <cstdlib> 
#include <cstdio> 
#include <iostream>
#include <fstream>

class Image
{
public:
	// Rgb structure, i.e. a pixel 
	struct Rgb
	{
	Rgb() : r(0), g(0), b(0) {}
	Rgb(float c) : r(c), g(c), b(c) {}
	Rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
	float r, g, b;
	};

	Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }
	Image(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack) :w(_w), h(_h), pixels(NULL)
	{
		pixels = new Rgb[w * h];
		for (int i = 0; i < w * h; ++i)
		pixels[i] = c;
	}
	//copy constructor
	Image(const Image &im)
	{
		w = im.w;
		h = im.h;
		pixels = new Rgb[im.w * im.h];
		for (int i = 0; i < im.w * im.h; ++i)
			pixels[i] = im.pixels[i];
	}

	//copy assignment operator
	Image& operator=(const Image& other)
	{
		w = other.w;
		h = other.h;
		pixels = new Rgb[other.w * other.h];
		for (int i = 0; i < other.w * other.h; ++i)
			pixels[i] = other.pixels[i];

		return *this;
	}

	Image operator+(float brightness)
	{
		brightness = brightness / 255.f;
		for (int i = 0; i < w * h; i++)
		{
			pixels[i].r = pixels[i].r + brightness;
			pixels[i].g = pixels[i].g + brightness;
			pixels[i].b = pixels[i].b + brightness;
			if (pixels[i].r < 0)
			{
				pixels[i].r = 0;
			}
			if (pixels[i].g < 0)
			{
				pixels[i].g = 0;
			}
			if (pixels[i].b < 0)
			{
				pixels[i].b = 0;
			}
		}
		return *this;
	}

	virtual ~Image()
	{
		if (pixels != NULL)
		delete[] pixels;
		std::cout << "Image destructor called" << std::endl;
	}
	virtual void displayInformation(const char *filename, int zoomScale = NULL)
	{
		std::ofstream ofs;
		ofs.open(filename, std::ios::out);
		if (ofs.fail()) throw("Can't open output file");
		std::cout << "\nDisplaying image information\n";
		std::cout << "Filename: " << filename << "\n";
		std::cout << "Image size: " << w << "x" << h << "\n\n";
		ofs << "Displaying image information" << std::endl;
		ofs << "Filename: " << filename << std::endl;
		ofs << "Image size: " << w << "X" << h << std::endl;
		ofs.close();
	}

	unsigned int w, h; // Image resolution 
	Rgb *pixels; // 1D array of pixels 
	static const Rgb kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors 
};


//bool operator != (const Rgb &c) const
//{
//	return c.r != r || c.g != g || c.b != b;
//}
//Rgb& operator *= (const Rgb &rgb)
//{
//	r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this;
//}
//Rgb& operator += (const Rgb &rgb)
//{
//	r += rgb.r, g += rgb.g, b += rgb.b; return *this;
//}
//friend float& operator += (float &f, const Rgb rgb)
//{
//	f += (rgb.r + rgb.g + rgb.b) / 3.f; return f;
//}
//const Rgb& operator [] (const unsigned int &i) const
//{
//	return pixels[i];
//}
//Rgb& operator [] (const unsigned int &i)
//{
//	return pixels[i];
//}

