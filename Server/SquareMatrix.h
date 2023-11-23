#pragma once
#include "Matrix.h"
#include <iostream>

template<class number>
class SquareMatrix : public Matrix<number>
{
public:
	SquareMatrix(uint size) : Matrix<number>(size, size) {}
	SquareMatrix(uint size, number* inpNum) : Matrix<number>(size, size, inpNum) {}

	number Determinant();
	uint GetSize()
	{
		return Matrix<number>::width;
	}
	
	SquareMatrix& operator= (SquareMatrix& right)
	{
		if (this == &right)
			return *this;
		Matrix<number>::width = right.GetSize();
		Matrix<number>::values = new number * [Matrix<number>::width];
		for (uint i = 0; i < Matrix<number>::width; i++)
		{
			*(Matrix<number>::values + i) = new number[Matrix<number>::width];
			for (uint j = 0; j < Matrix<number>::width; j++)
			{
				*(*(Matrix<number>::values + i) + j) = Matrix<number>::right.GetValue(i, j);
			}
		}
		return *this;
	}
};


template<class number>
number SquareMatrix<number>::Determinant()
{
	SquareMatrix temp(Matrix<number>::width);
	temp.copyMatrix(this);

	Matrix<number>::applyGaussMethod();

	number com = 1;
	for (uint i = 0; i < Matrix<number>::width; i++)
	{
		com *= Matrix<number>::values[i][i];
	}

	this->copyMatrix(&temp);

	return com;
}
