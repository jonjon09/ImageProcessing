/*
 *CSCE 240 Final Project - Image Processing
 *Group 7: Patrick McIntyre, Jonathan Limpalair, Ronessa DaSilva, Nicole Longworth
 *Image class for final project
 */

#ifndef IMAGE_H
#define IMAGE_H

#include<string>
#include "Matrix.h"

class Image : public Matrix
{
	private:
	//Variables for Image class
	int brightness, width, height;
	std::string filename;
	std::string outputFile;
	std::string P2;

	public:
	//Constructors and destructors
	Image(std::string filename);
	Image(int w, int h, int b, std::string p);
	Image(const Image &M);
	virtual ~Image();

	//Write function
 	void write(std::string outputFile);
	
	//operators overloaded
	Image operator + (const Image &I);
	using Matrix::operator=;
	//Image& operator = (const Image &M);

	//Effects
	Image imgBlend(Image &I1, Image &I2);
	Image edgeDetection(const Image &I);
	Image horizFilter(const Image &I);
	Image vertFilter(const Image &I);
	Image MedianFiltering(int neighborhood);
	Image localContrast(int radius);
};

#endif
