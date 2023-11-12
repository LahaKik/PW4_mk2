#include "SquareMatrix.h"

SquareMatrix::SquareMatrix(Uint size) : Matrix(size, size){}

SquareMatrix::SquareMatrix(Uint size, number* inpNum) : Matrix(size, size, inpNum){}

number SquareMatrix::Determinant()
{
	SquareMatrix temp(width);
	temp.copyMatrix(this);

	applyGaussMethod();

	number com = 1;
	for (Uint i = 0; i < width; i++)
	{
		com *= values[i][i];
	}

	this->copyMatrix(&temp);

	return com;
}