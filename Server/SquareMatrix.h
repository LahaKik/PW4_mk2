#pragma once
#include "Matrix.h"
#include <iostream>

class SquareMatrix : public Matrix
{
public:
	SquareMatrix(Uint);
	SquareMatrix(Uint, number*);

	number Determinant();
	Uint GetSize()
	{
		return width;
	}
	
	SquareMatrix& operator= (SquareMatrix& right)
	{
		if (this == &right)
			return *this;
		width = right.GetSize();
		values = new number * [width];
		for (Uint i = 0; i < width; i++)
		{
			*(values + i) = new number[width];
			for (Uint j = 0; j < width; j++)
			{
				*(*(values + i) + j) = right.GetValue(i, j);
			}
		}
		return *this;
	}
};