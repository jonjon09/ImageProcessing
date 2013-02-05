/*
 *Image cpp file
 *Group 7: Patrick McIntyre, Jonathan Limpalair, Ronessa DaSilva, Nicole Longworth
 *
 *definitons for all functions and other necessary parts for the image class
 */

#include "Image.h"

#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>
#include <cmath>

using namespace std;

//constructor for image class
//accepts string argument, string will be the filename to be opened
Image::Image(string file) : Matrix()
{
	filename = file;
	ifstream input;
	
	//opens input file
	input.open(filename.c_str());
	
	//check to see if the file opened successfully
	if(input.fail())
	{
		//if file failed to open displays error message and exits program
		cout << "Error opening input file" << endl;
		exit(1);
	}

	//gets values from the file for variables
	input >> P2;
	input >> width;
	input >> height;

	//allocate function from Matrix class
	//allocates the memory for the image
	allocate(height, width);

	//gets input for the brightness variable
	input >> brightness;

	//reads in the data values for the image designated by the input file
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			input >> data[i][j];
		}
	}

	//closes the input file
	input.close();
}
//end of Image constructor

//Image constructor accepting 4 parameters
//must accept the string or will not write the P2 in output and not return an image
Image::Image(int w, int h, int b, string p):  brightness(b), height(h), width(w), P2(p)
{
	allocate(h, w);
}
//End of Image constructor

//Image copy constructor
Image::Image(const Image &M): brightness(M.brightness), height(M.height), width(M.width), P2(M.P2) 
//variables are set here because of data corruption if they are not set
{
	//checks for self assignment
	if(this == &M)
	{
		cout << "this == &M" << endl;
	}

	//allocates matrix based on parameter/original Image
	allocate(M.getHeight(), M.getWidth());

	//sets values of each index in the Image
	for(int i = 0; i < M.getHeight(); ++i)
	{
		for(int j = 0; j < M.getWidth(); ++j)
		{
			data[i][j] = M.data[i][j];
		}
	}
}
//End of Image copy constructor

//destructor for image class
Image::~Image()
{
	//will call Matrix class destructor automatically
}
//End of Image destructor

//write function for the Image class
//accepts string parameter that will be the output file
void Image::write(string outputFile)
{
	//creates ofstream, output stream object
	ofstream output;
	
	//opens the output file
	output.open(outputFile.c_str());

	//checks to see if the output file successfully opened
	if(output.fail())
	{
		//if output file did not open displays error message and exits
		cout << "Error opening output file" << endl;
		exit(1);
	}

	//writes to file all of the necessary header information
	output << P2 << endl;
	output << width << " " << height << endl;
	output << brightness << endl;

	//writes to file all of the values for the image
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			output << data[i][j] << " ";
		}
		output << endl;
	}

	//closes the output file
	output.close();
}
//End of write function for Image class

//effects for image class

/*
 * Image Blending
 */
//accepts two Image objects
//Uses overloaded + operator
Image Image::imgBlend(Image &I1,Image &I2)
{
	//checks to make sure both images input are the same size
	if(I1.getHeight() != I2.getHeight() || I1.getWidth() != I2.getWidth())
	{
		//returns error and exits if the images are different sizes
		cout << "[ERROR] Image::imgBlend - Different Image sizes." << endl;
		exit(1);
	}
	
	//creates new image as a copy of one of the two input images
	Image I3(I1);
	//sets value of I3, with overloaded +, to sum of two input images
	I3 = I1 + I2;
	
	//for each of the indices in the image, gets average of the input images at that pixel
	//just divides the value for the pixel by 2
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			I3.setValue(i,j, (I3.getValue(i,j) / 2));
		}
	}
	
	//returns an image object
	return I3;
}//end Image::imgBlend

/*
 * Extra Credit: Edge Detection
 */
Image Image::edgeDetection(const Image &I)
{
	//creates there image objects first two of which are the images of after hoizontal and vertical filters, third is the result
	Image horizImage(I);
	Image vertImage(I);
	Image edgeImage(I);
	
	//lets user know progress of the function
	cout << "Setting up filters" << endl;
	
	//does horizontal and verical filters then combines
	horizImage = horizFilter(I);
	vertImage = vertFilter(I);
	cout << "Combining" << endl;
	//combining for horizontal and vetical filters
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			edgeImage.setValue(i,j,
				sqrt(pow(horizImage.getValue(i,j),2)+pow(vertImage.getValue(i,j),2)));
		}
	}
	return edgeImage;
}//end Image::edgeDetection

//Horizontal filter for Image class
Image Image::horizFilter(const Image &I)
{
	//temp image for storage
	Image tmpImage(I);
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int p7 = 0;
	int p8 = 0;
	int p9 = 0;

	cout << "Finding Horizontal" << endl;
	//horizontal filtering math
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			//check for in bounds
			if(I.getValue(i-1,j-1) != -1) p1 = I.getValue(i-1,j-1);
			if(I.getValue(i,j-1) != -1) p2 = I.getValue(i,j-1);
			if(I.getValue(i+1,j-1) != -1) p3 = I.getValue(i+1,j-1);
			if(I.getValue(i-1,j+1) != -1) p7 = I.getValue(i-1,j+1);
			if(I.getValue(i,j+1) != -1) p8 = I.getValue(i,j+1);
			if(I.getValue(i+1,j+1) != -1) p9 = I.getValue(i+1,j+1);
			tmpImage.setValue(i,j,(-1*p1-2*p2-1*p3+p7+2*p8+p9));
		}
	}
	//returns the temp image
	return tmpImage;
}//end Image::horizFilter

//Vertical filter for Image class
Image Image::vertFilter(const Image &I)
{
	//temp image object
	Image tmpImage(I);
	int p1 = 0;
	int p4 = 0;
	int p7 = 0;
	int p3 = 0;
	int p6 = 0;
	int p9 = 0;

	cout << "Finding Vertical" << endl;
	//vertical filter math
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			//check for in bounds
			if(I.getValue(i-1,j-1) != -1) p1 = I.getValue(i-1,j-1);
			if(I.getValue(i-1,j) != -1) p4 = I.getValue(i-1,j);
			if(I.getValue(i-1,j+1) != -1) p7 = I.getValue(i-1,j+1);
			if(I.getValue(i+1,j-1) != -1) p3 = I.getValue(i+1,j-1);
			if(I.getValue(i+1,j) != -1) p6 = I.getValue(i+1,j);
			if(I.getValue(i+1,j+1) != -1) p9 = I.getValue(i+1,j+1);
			tmpImage.setValue(i,j,(-1*p1-2*p4-1*p7+p3+2*p6+p9));
		}
	}
	//returns the temp image object
	return tmpImage;
}//end Image::vertFilter

/* 
 Local Contrast Enhancement
*/
Image Image::localContrast(int r)
{
	//set up random seed
	srand(time (NULL));

	//declare variables
	int x = 0;
	int y = 0;
	int radius = r;
	int max = 0;
	int min = brightness;
	int a1 = 0;
	int a2 = height;
	int a3 = 0;
	int a4 = width;
	double contrast = 0.0;
	double currentPixel = 0.0;
	double brightness2 = 0.0;
	double min2 = 0.0;
	double max2 = 0.0;

	//selects random pixel starting point for contrast enhancement
	x = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * height);
	y = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * width);
	
	//sets the radii for the circle
	if(x-radius > 0) a1 = x-radius;
	if(x+radius < height) a2 = x+radius ;
	if(y-radius > 0) a3 = y-radius;
	if(y+radius < width) a4 = y+radius;

	//displays to user where the random pixel is located
	cout << "Random pixel location: X: " << x << " Y: " << y << endl;
	
	//finds the maximum and minimum brightness values for the area to be enhanced
	for( int i = a1; i < a2 ; ++i)
	{
		for(int j = a3; j < a4; ++j)
		{
    			if(getValue(i,j) > max) max = getValue(i,j);
			if(getValue(i,j) < min && getValue(i,j) != -1) min = getValue(i,j);
		}
	}

	
	double test = 0.0;

	//performs contrast enhancement for area of the circle
	for(int i = a1; i < a2 ; ++i)
	{
		for(int j = a3; j < a4; ++j)
		{
			//checks to make sure all of the values are within the radius input by the user
			if(static_cast<int>(sqrt(pow(abs(x-i),2)+pow(abs(y-j),2))) <= radius)
			{
				brightness2 = static_cast<double>(brightness);
				currentPixel = static_cast<double>(getValue(i,j));
				min2 = static_cast<double>(min);
				max2 = static_cast<double>(max);

				contrast = ((currentPixel - min2) / (max2 - min2) * brightness2);
		
				setValue(i,j, static_cast<int>(contrast));
			}
		}
	}

	//returns image object
	return *this;
}//end of contrast loop

/*
 *Median Filtering
 */

Image Image:: MedianFiltering(int neighborhood) //neighborhood will be input by user
{
	//variables
	int size = neighborhood * neighborhood;
	int testOdd = neighborhood % 2;
	int counter = 0; 
	bool swapped = false;

	Image temp(width, height, brightness, P2);

	//1D array which stores all of the values in the neighborhood
	int a[size];

	//checks that neighborhood value is odd
	//if the value is not odd the neighborhood will not center properly
	if (testOdd != 1)
	{
		//if neighborhood is even, displays message and exits program
		cout << "Neighborhood must be an odd number" << endl;
		exit(1);
	}

	//starts looping over image
	for (int ii =0; ii < height; ++ii)
	{
		for (int jj =0; jj < width; ++jj)
		{	
			int count = 0;	
			// for loop = store the values in temp in array a
			for (int i = (ii - (neighborhood/2)); i <= (ii + (neighborhood/2)); ++i)
			{
				for (int j = (jj - (neighborhood/2)); j <= (jj + (neighborhood/2)); ++j)
				{
					//checking if the index is in bounds
					if(getValue(i,j) != -1)
					{	
						a[count] = getValue(i,j);
					}
					else 
					{
						a[count] = 0;
					}
					count++;

					//bubble swap
					do 
					{
						swapped = false;
						for (int i = 1; i < size; ++i)
						{
							if(a[i-1] > a[i])
							{
								swap(a[i-1], a[i]);
								swapped = true;
								counter++;
							}
						}
					}
					while (swapped);	
		
					//gets the median index and sets the median value
					int medianIndex = (size/2); //find the index of the median 
					int medianValue =  a[medianIndex]; //get the value of the median number in array a (the 1D array)

					//sets temp image values to median value for each pixel's neighborhood
					temp.setValue(ii, jj, medianValue);
					}	
			}	
		}
	}
	//returns temp image
	return temp;
}
//End of Median Filtering function


/*
 * Overloaded operators
 */
Image Image::operator + (const Image &I)
{
  Image tmpImage(I); //temporary array
  for(int i = 0; i < height; ++i)
  {
    for(int j = 0; j < width; ++j)
    {
      tmpImage.setValue(i,j, getValue(i,j) + I.getValue(i,j));
    }
  }
  return tmpImage;
}//end Image::operator+
