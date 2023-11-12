#include "Matrix.h"

Matrix::Matrix(uint height, uint width) : height(height), width(width)
{
	values = new number * [height];
	for (Uint i = 0; i < height; i++)
	{
		*(values + i) = new number[width];
		for (Uint j = 0; j < width; j++)
		{
			*(*(values + i) + j) = 1;
		}
	}
}

Matrix::Matrix(uint height, uint width, number* arr) : height(height), width(width)
{
	values = new number * [height];
	int t = 0;
	for (Uint i = 0; i < height; i++)
	{
		*(values + i) = new number[width];
		for (Uint j = 0; j < width; j++)
		{
			*(*(values + i) + j) = arr[t];
			t++;
		}
	}
	delete[] arr;
}

Matrix::~Matrix()
{
	for (Uint i = 0; i < height; i++)
	{
		delete[] * (values + i);
	}
	delete[] values;
}

number Matrix::GetValue(Uint i, Uint j)
{
	return values[i][j];
}

void Matrix::copyMatrix(Matrix* target)
{
	for (Uint i = 0; i < height; i++)
	{
		for (Uint j = 0; j < width; j++)
		{
			*(*(values + i) + j) = target->GetValue(i, j);
		}
	}
}
void Matrix::SetTransposed()
{
	number** tempValue = new number * [width];
	for (Uint i = 0; i < width; i++)
	{
		tempValue[i] = new number[height];
		for (Uint j = 0; j < height; j++)
		{
			tempValue[i][j] = values[j][i];
		}
	}
	for (Uint i = 0; i < height; i++)
	{
		delete[] * (values + i);
	}
	delete[] values;
	values = tempValue;
	uint t = height;
	height = width;
	width = t;
}
int Matrix::ComputeRank()
{
	Matrix temp(height, width);
	temp.copyMatrix(this);

	applyGaussMethod();
	std::cout << std::endl;
	//Print();
	int rank = 0;

	for (Uint i = 0; i < ((height > width) ? width : height); i++)
	{
		if (values[i][i] != 0)
			rank++;
		else
			break;
	}

	this->copyMatrix(&temp);

	return rank;
}

void Matrix::applyGaussMethod()
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

QString Matrix::ToQString()
{
	QString rezult;
	for (Uint i = 0; i < height; i++)	
	{
		for (Uint j = 0; j < width; j++)
		{
			rezult << QString().setNum(values[i][j].upNum) << QString().setNum(values[i][j].downNum);
		}
	}
	return rezult;
}