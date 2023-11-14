#pragma once
#include "Number.h"
#include <iostream>

class Matrix
{
private:
	Uint size;
	number** values;
	void copyMatrix(Matrix*);
	void applyGaussMethod();

public:
	Matrix(Uint);
	Matrix(Uint, number*);
	~Matrix();

	number Determinant();
	number GetValue(Uint, Uint);
	Uint GetSize()
	{
		return size;
	}
	void SetTransposed();
	int ComputeRank();

	Matrix& operator= (Matrix& right)
	{
		if (this == &right)
			return *this;
		size = right.GetSize();
		values = new number * [size];
		for (Uint i = 0; i < size; i++)
		{
			*(values + i) = new number[size];
			for (Uint j = 0; j < size; j++)
			{
				*(*(values + i) + j) = right.GetValue(i, j);
			}
		}
		return *this;
	}


	QString ToQString();
	void Print()
	{
		for (unsigned short i = 0; i < size; i++)
		{
			for (unsigned short j = 0; j < size; j++)
			{
				std::cout << values[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}
};