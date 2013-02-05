/*
 *CSCE 240 Final Project - Image Processing
 *Matrix class cpp
 *Group 7: Patrick McIntyre, Jonathan Limpalair, Ronessa DaSilva, Nicole Longworth
 *Matrix class definition file
 */

#include "Matrix.h"

#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

//constructor for Matrix class object
Matrix::Matrix()
{
	//intentionally blank
}
//end Matrix class constructor

//Copy constructor
Matrix::Matrix(const Matrix &M)
{
	//debugging line
	cout << " Starting matrix copy constructor" << endl;
	
	//creates new Matrix same as the parameter Matrix
	allocate(M.getHeight(),M.getWidth());
	
	//sets value to that of the parameter Matrix
	for(int i = 0; i < M.getHeight(); ++i)
	{
		for(int j = 0; j < M.getWidth(); ++j)
		{
			data[i][j] = M.data[i][j];
		}
	}
		
	//extra debug lines
	cout << "done with matrix copy constructor" << endl;
	cout << getHeight() << " x " << getWidth() << endl;
}
//End copy consturctor Matrix class

//Matrix Destructor
Matrix::~Matrix()
{
	//checks status of data to see if it has been allocated
	if(data != NULL)
	{
		//deallocates all memory
		for(int i = 0; i < height; ++i)
		{
			if(data[i] == NULL)
			{
				cout << "data found null " << i << endl;
			}
			delete [] data[i];
		}
		delete [] data;
	}
}
//End Matrix destructor

//read function
void Matrix::read() const
{
	//assigns values to 
	for(int i = 0; i < width; ++i)
	{
		for(int j = 0; j < height; ++j)
		{
			cin >> data[i][j];
		}
	}
}
//End Matrix read function

//display function
void Matrix::display() const
{
	for(int i = 0; i < width; ++i)
	{
		for(int j = 0; j < height; ++j)
		{
			cout << data[i][j] << " ";
		}
		cout << endl << endl;
	}
}

//getValue
int Matrix::getValue(int i, int j) const
{
  if( i > -1 && j > -1 && i < height && j < width)
    return(data[i][j]);
  else
  {
    return -1;
  }
}//end Matrix::getValue

//setValue
void Matrix::setValue(int i, int j, int value)
{
  if( i > -1 && j > -1 && i < height && j < width)
    data[i][j] = value;
  else
  {
    cout << "[ERROR] Matrix::setValue -> Attempted to access array out of bounds [" << i << "," << j << "]" << endl;
    exit(1);
  }
}//end Matrix::setValue


//get number of rows
int Matrix::getHeight() const
{
  return height;
}//end Matrix::getHeight

//get number of columns
int Matrix::getWidth() const
{
  return width;
}//end Matrix::width



//Allocate function
void Matrix::allocate(int h, int w)
{
	height = h;
	width = w;

	//creates 2D matrix of height and width, checks to see if memory is allocated
	data = new int*[height];

	if(data == NULL)
	{
		cout << "ERROR" << endl;
		exit(1);
	}
	
	for(int i = 0; i < height; ++i)
	{
		data[i] = new int[width];
		if(data[i] ==NULL)
		{
			cout <<"Memory could not be allocated" << endl;
			exit(1);
		}
	}
	
	
}
//End of allocate function

//Overloaded = operator
Matrix& Matrix::operator = (const Matrix &M)
{
  if(this != &M) //check for self-assignement
  {
    //delete memory for calling object
    for(int i = 0; i < M.getHeight(); ++i)
    {
      if(data[i] != NULL)
        delete [] data[i];
    }
    if(data != NULL)
      delete [] data;

    //allocate memory to calling object equal to M
    data = new int* [M.getHeight()];
    if(data == NULL)
    {
      cout << "[ERROR] Matrix::allocateMemory -> Insufficient Memory" << endl;
      exit(1);
    }
    for(int i = 0; i < M.getHeight(); ++i)
    {
      data[i] = new int [M.getWidth()];
      if(data[i] == NULL)
      {
        cout << "[ERROR] Matrix::allocateMemory -> Insufficient Memory" << endl;
        exit(1);
      }
    }
    
    //copy data from M to calling object
    for(int i = 0; i < M.getHeight(); ++i)
    {
      for(int j = 0; j < M.getWidth(); ++j)
      {
        setValue(i,j, M.getValue(i,j));
      }
    }  
    //return calling object
    return *this;  
  }
}//end Matrix::operator=
