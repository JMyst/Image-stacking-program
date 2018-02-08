#include <iostream>
#include <fstream>
#include <algorithm>
#include "Write.h"

Write::Write()
{
}


Write::~Write()
{
}

void Write::writePPM(const Image &img, const char *filename)
{
	//std::cout << filename << std::endl;
	std::cout << "Writing image ..." << std::endl;
	if (img.w == 0 || img.h == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
	std::ofstream ofs;
	try {
		ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 
		if (ofs.fail()) throw("Can't open output file");
		ofs << "P6\n" << img.w << " " << img.h << "\n255\n";
		//std::cout << "P6\n" << img.w << " " << img.h << "\n255\n";
		unsigned char r, g, b;
		// loop over each pixel in the image, clamp and convert to byte format
		for (int i = 0; i < img.w * img.h; ++i) {
			r = static_cast<unsigned char>(std::min(1.f, img.pixels[i].r) * 255);
			g = static_cast<unsigned char>(std::min(1.f, img.pixels[i].g) * 255);
			b = static_cast<unsigned char>(std::min(1.f, img.pixels[i].b) * 255);
			ofs << r << g << b;
		}
		ofs.close();
		//Confirm image write
		std::cout << "Image written" << std::endl;
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ofs.close();
	}
}
