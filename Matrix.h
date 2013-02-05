/*
 *CSCE 240 Final Project - Image Processing
 *Matrix class
 *Group 7: Patrick McIntyre, Jonathan Limpalair, Ronessa DaSilva, Nicole Longworth
 *Matrix class file
 */

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	protected:
	//variables and allocate function
	int height, width;
	int **data;
	void allocate(int m, int n);

	public:
	//consturctors and destructor(s)
	Matrix();
	Matrix(const Matrix &M);
	virtual ~Matrix();

	//accessors/mutators
	int getValue(int i, int j) const;
	void setValue(int i, int j, int value);
	int getHeight() const;
	int getWidth() const;

	//IO
	void read() const;
	void display() const;

	//overloaded = operator, will be used by Image class
	Matrix& operator = (const Matrix &M);
};

#endif //MATRIX_H
