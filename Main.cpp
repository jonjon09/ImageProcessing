/*
 *CSCE 240 Final Project - Image Processing
 *Main.cpp
 *Group 7: Patrick McIntyre, Jonathan Limpalair, Ronessa DaSilva, Nicole Longworth
 *
 *Main for the Final Project, will allow user to make choices, uses the .pgm file type.
 *Offers four choices for Image effects; Median Filtering, Image Blending, Contrast Enhancement, and Edge Detection.
 *implements all effects, uses file streaming
 */

//Libraries for inclusion
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

//Class files
#include "Matrix.h"
#include "Image.h"

using namespace std;

int main(int argc, char **argv)
{
	//Variables
	int choice;
	int radius;
	int neighborhood;
	string fileNameOne;
	string fileNameTwo;
	string outputFile;
	//End of variables ----------------------------

	//What is first seen by the user
	cout << endl << endl; //Create space between last line in console and first line in program
	cout << "****************************************" << endl;
	cout << "    Welcome to the Image Manipulator    " << endl;
	cout << "    by: Group 7: Patrick McIntyre, Jonathan Limpalair, Ronessa DaSilva, Nicole Longworth     " << endl;
	cout << "****************************************" << endl;

	cout << endl;

	//Displays choices for the user
	cout << "This program supports the following effects:" << endl;
	cout << "1. Median Filtering" << endl;
	cout << "2. Image Blending" << endl;
	cout << "3. Local Contrast Enhancement" << endl;
	cout << "4. Edge Detection" << endl;
	cout << "----------------------------" << endl;

	cout << endl;

	cout << "Enter your choice 1, 2, 3, or 4: ";
	cin >> choice;

	cout << endl;

	
	//If statements that will execute different effects based on user input
	//choice for Median Filtering or blur effect	
	if(choice == 1)
	{
		cout << "Your choice was Median Filtering" << endl;
		cout << "Required inputs are 1 file in PGM format and a neighborhood size" << endl;
		cout << "Please enter the filename now: ";
		cin >> fileNameOne;
		cout << "Please enter the (n*n) neighborhood size: ";
		cin >> neighborhood;
		cout << "Please enter the output file name: ";
		cin >> outputFile;

		cout << "-------------------------------------------------------------------" << endl;
		cout << "Processing" << endl;

		Image img1(fileNameOne);
		Image img2(img1);
		img2 = img1.MedianFiltering(neighborhood);
		img2.write(outputFile);

		cout << "Result written to: " << outputFile << endl;
		cout << endl;
	}
	//choice for image blending
	//takes two input images and returns a blended image of them
	else if(choice == 2)
	{
		cout << "Your choice was Image Blending" << endl;
		cout << "Required inputs are 2 files in PGM format" << endl;
		cout << "Enter first file name now: ";
		cin >> fileNameOne;
		cout << "Enter second file name now: ";
		cin >> fileNameTwo;
		cout << "Please enter the output file name now: ";
		cin >> outputFile;

		cout << "-------------------------------------------------------------------" << endl;
		cout << "Processing" << endl;
		
		Image img1(fileNameOne);
		Image img2(fileNameTwo);
		Image img3(img1);
		img3 = img1.imgBlend(img1,img2);
		img3.write(outputFile);
		
		cout << "Result written to: " << outputFile << endl;
		cout << endl;
	}
	//choice for contrast enhancement
	//takes image, finds random pixel, increases contrast in a radius around that pixel
	else if(choice == 3)
	{
		cout << "Your choice was Local Contrast Enhancement" << endl;
		cout << "Required inputs are 1 file in PGM format and a radius for neighborhood" << endl;
		cout << "Enter file name now: ";
		cin >> fileNameOne;
		cout << "Enter the radius: ";
		cin >> radius;
		cout << "Please enter the output file name now: ";
		cin >> outputFile;

		cout << "-------------------------------------------------------------------" << endl;
		cout << "Processing" << endl;

		Image img1(fileNameOne);
		Image img2(img1);
		img2 = img1.localContrast(radius);
		img2.write(outputFile);

		cout << "Result written to: " << outputFile << endl;
		cout << endl;
	}
	//choice for edge detection
	//user selects the input and output files
	else if(choice == 4)
	{
		cout << "Your choice was Edge Detection" << endl;
		cout << "Required input is 1 files in PGM format" << endl;
		cout << "Enter file name now: ";
		cin >> fileNameOne;
		cout << "Please enter the output file name now: ";
		cin >> outputFile;

		cout << "-------------------------------------------------------------------" << endl;
		cout << "Processing" << endl;
		
		Image img1(fileNameOne);
		Image img2(img1);
		img2 = img1.edgeDetection(img1);
		img2.write(outputFile);
		
		cout << "Result written to: " << outputFile << endl;
		cout << endl;
	}
	
	//creates space between last line and command line
	cout << endl;
	return(0);
}
