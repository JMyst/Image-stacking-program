#include <iostream>
#include <fstream>
#include <string>
#include "Read.h"

Read::Read()
{
}

void Read::readPPM(const char *filename, Image &img)
{
	std::cout << "Reading image ..." << std::endl;
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);
	try {
		if (ifs.fail()) {
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;
		//std::cout << w << " " << h << std::endl;
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
		unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
		for (int i = 0; i < w * h; ++i) {
			ifs.read(reinterpret_cast<char *>(pix), 3);
			img.pixels[i].r = pix[0] / 255.f;
			img.pixels[i].g = pix[1] / 255.f;
			img.pixels[i].b = pix[2] / 255.f;
		}
		ifs.close();
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}

	//Confirm image read
	//Delete this to prevent multiple lines output
	std::cout << "Image read" << std::endl;
}

Read::~Read()
{
}
