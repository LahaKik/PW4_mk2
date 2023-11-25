#pragma once
#include <qtypes.h>
#include <qstring.h>
#include "Complex.h"
#include "Rational.h"

template<class number>
class Matrix
{
private:
	uint height;

protected:
	uint width;
	number** values;
	void copyMatrix(Matrix*);
	void applyGaussMethod();

public:
	Matrix(uint, uint);
	Matrix(uint, uint, number*);
	~Matrix();

	number GetValue(uint, uint);
	int ComputeRank();
	void SetTransposed();
	//virtual QString ToQString();
	friend QString& operator<< (QString& str, const Matrix<number>& matrix) 
	{
		for (uint i = 0; i < matrix.height; i++)
		{
			for (uint j = 0; j < matrix.width; j++)
			{
				str << matrix.values[i][j];
			}
		}
		return str;
	}

};


template<class number>
Matrix<number>::Matrix(uint height, uint width) : height(height), width(width)
{
	values = new number * [height];
	for (uint i = 0; i < height; i++)
	{
		*(values + i) = new number[width];
		for (uint j = 0; j < width; j++)
		{
			*(*(values + i) + j) = 1;
		}
	}
}

template<class number>
Matrix<number>::Matrix(uint height, uint width, number* arr) : height(height), width(width)
{
	values = new number * [height];
	int t = 0;
	for (uint i = 0; i < height; i++)
	{
		*(values + i) = new number[width];
		for (uint j = 0; j < width; j++)
		{
			*(*(values + i) + j) = arr[t];
			t++;
		}
	}
	delete[] arr;
}

template<class number>
Matrix<number>::~Matrix()
{
	for (uint i = 0; i < height; i++)
	{
		delete[] * (values + i);
	}
	delete[] values;
}

template<class number>
number Matrix<number>::GetValue(uint i, uint j)
{
	return values[i][j];
}

template<class number>
void Matrix<number>::copyMatrix(Matrix* target)
{
	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			*(*(values + i) + j) = target->GetValue(i, j);
		}
	}
}

template<class number>
void Matrix<number>::SetTransposed()
{
	number** tempValue = new number * [width];
	for (uint i = 0; i < width; i++)
	{
		tempValue[i] = new number[height];
		for (uint j = 0; j < height; j++)
		{
			tempValue[i][j] = values[j][i];
		}
	}
	for (uint i = 0; i < height; i++)
	{
		delete[] * (values + i);
	}
	delete[] values;
	values = tempValue;
	uint t = height;
	height = width;
	width = t;
}

template<class number>
int Matrix<number>::ComputeRank()
{
	Matrix temp(height, width);
	temp.copyMatrix(this);

	applyGaussMethod();

	//Print();
	int rank = 0;

	for (uint i = 0; i < ((height > width) ? width : height); i++)
	{
		if (values[i][i] != 0)
			rank++;
		else
			break;
	}

	this->copyMatrix(&temp);

	return rank;
}

template<class number> 
void Matrix<number>::applyGaussMethod()
{
	for (int k = 0; k < height - 1; k++)
	{
		for (int i = k + 1; i < height; i++)
		{
			number tmp;
			tmp = -(values[i][k] / (number)values[k][k]);
			for (int j = 0; j < width; j++)
			{
				number temp = values[k][j] * tmp;
				values[i][j] += temp;
			}
		}
	}
}

//template<class number>
//QString Matrix<number>::ToQString()
//{
//	QString rezult;
//	for (uint i = 0; i < height; i++)
//	{
//		for (uint j = 0; j < width; j++)
//		{
//			rezult << QString().setNum(GetValue(i, j)) << QString().setNum(GetValue(i, j));
//		}
//	}
//	return rezult;
//}

