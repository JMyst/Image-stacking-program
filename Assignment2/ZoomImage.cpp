#include "ZoomImage.h"

ZoomImage::ZoomImage(const unsigned int &_w, const unsigned int &_h, const Rgb &c) : Image(_w, _h, c) {}

void ZoomImage::displayInformation(const char *filename, int zoomScale)
{
	std::ofstream ofs;
	ofs.open(filename, std::ios::out);
	if (ofs.fail()) throw("Can't open output file");
	std::cout << "\nDisplaying zoom image information\n";
	std::cout << "Filename: " << filename << "\n";
	std::cout << "Image size: " << w << "x" << h << "\n";
	std::cout << "Zoom scale: " << zoomScale << "\n\n";
	ofs << "Displaying zoom image information" << std::endl;
	ofs << "Filename: " << filename << std::endl;
	ofs << "Image size: " << w << "X" << h << std::endl;
	ofs << "Zoom scale: " << zoomScale << std::endl;
	ofs.close();
}

ZoomImage::~ZoomImage()
{
	std::cout << "Zoom destructor called" << std::endl;
}
