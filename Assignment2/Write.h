#pragma once
#include "Image.h"

class Write
{
private:
public:
	Write();
	void writePPM(const Image &img, const char *filename);
	~Write();
};

