#pragma once
#include "Image.h"

class Read
{
private:

public:
	Read();
	void readPPM(const char *filename, Image &img);
	~Read();
};
