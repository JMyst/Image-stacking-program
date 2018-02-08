#include "Image.h"

Image::Image(const Image &im)
	{
	w = im.w;
	h = im.h;
	pixels = new Rgb[im.w * im.h];
	for (int i = 0; i < im.w * im.h; ++i)
		pixels[i] = im.pixels[i];
	}

Image &Image::operator=(const Image& other)
{
	w = other.w;
	h = other.h;
	pixels = new Rgb[other.w * other.h];
	for (int i = 0; i < other.w * other.h; ++i)
		pixels[i] = other.pixels[i];

	return *this;
}

Image Image::operator+(float brightness)
{
	brightness = brightness / 255.f;
	for (int i = 0; i < w * h; i++)
	{
		pixels[i].r = pixels[i].r + brightness;
		pixels[i].g = pixels[i].g + brightness;
		pixels[i].b = pixels[i].b + brightness;
	}
	return *this;
}

virtual void Image::displayInformation(const char *filename, int zoomScale)
{
	std::ofstream ofs;
	ofs.open(filename, std::ios::out);
	if (ofs.fail()) throw("Can't open output file");
	std::cout << "Displaying image information\n";
	std::cout << "Filename: " << filename << "\n";
	std::cout << "Image size: " << w << "x" << h << "\n";
	ofs << "Displaying image information" << std::endl;
	ofs << "Filename: " << filename << std::endl;
	ofs << "Image size: " << w << "X" << h << std::endl;
	ofs.close();
}

virtual Image:: ~Image()
{
	if (pixels != NULL)
		delete[] pixels;
	std::cout << "Image destructor called" << std::endl;
}

