#pragma once
#include "Image.h"
class ZoomImage: public Image
{
public:
	ZoomImage(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack);
	virtual ~ZoomImage();
	virtual void displayInformation(const char *filename, int zoomScale = 0);
};

