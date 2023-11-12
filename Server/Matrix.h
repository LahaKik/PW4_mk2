#pragma once
#include "Number.h"
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

	number GetValue(Uint, Uint);
	int ComputeRank();
	void SetTransposed();
	virtual QString ToQString();
};

