#include "ServerApp.h"
#include "Matrix.h"
#include "SquareMatrix.h"

ServerApp::ServerApp(int argc, char** argv) : QCoreApplication(argc, argv)
{
	TCommParams servParams = { QHostAddress::LocalHost, 10000,
								QHostAddress::LocalHost, 10001 };
	comm = new TCommunicator(servParams, this);

	connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

template<>
SquareMatrix<double>* ServerApp::CombineMatrix(QByteArray arr, uint size)
{
	double* valuesD = new double[size * size];
	uint k = 0;
	for (uint i = 0; i < size; i++)
	{
		for (uint j = 0; j < size; j++)
		{
			double tempD;
			arr >> tempD;
			valuesD[k] = tempD;
			k++;
		}
	}
	SquareMatrix<double>* matrix = new SquareMatrix<double>(size, valuesD);
	return matrix;
}

template<>
SquareMatrix<Rational>* ServerApp::CombineMatrix(QByteArray arr, uint size)
{
	Rational* valuesD = new Rational[size * size];
	uint k = 0;
	for (uint i = 0; i < size; i++)
	{
		for (uint j = 0; j < size; j++)
		{
			Rational tempD;
			arr >> tempD;
			valuesD[k] = tempD;
			k++;
		}
	}
	SquareMatrix<Rational>* matrix = new SquareMatrix<Rational>(size, valuesD);
	return matrix;
}

template<>
SquareMatrix<TComplex>* ServerApp::CombineMatrix(QByteArray arr, uint size)
{
	TComplex* valuesD = new TComplex[size * size];
	uint k = 0;
	for (uint i = 0; i < size; i++)
	{
		for (uint j = 0; j < size; j++)
		{
			TComplex tempD;
			arr >> tempD;
			valuesD[k] = tempD;
			k++;
		}
	}
	SquareMatrix<TComplex>* matrix = new SquareMatrix<TComplex>(size, valuesD);
	return matrix;
}

template<>
Matrix<double>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width)
{
	double* valuesD = new double[height * width];
	uint k = 0;
	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			double tempD;
			arr >> tempD;
			valuesD[k] = tempD;
			k++;
		}
	}
	Matrix<double>* matrix = new Matrix<double>(height, width, valuesD);
	return matrix;
}

template<>
Matrix<Rational>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width)
{
	Rational* valuesD = new Rational[height * width];
	uint k = 0;
	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			Rational tempD;
			arr >> tempD;
			valuesD[k] = tempD;
			k++;
		}
	}
	Matrix<Rational>* matrix = new Matrix<Rational>(height, width, valuesD);
	return matrix;
}

template<>
Matrix<TComplex>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width)
{
	TComplex* valuesD = new TComplex[height * width];
	uint k = 0;
	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			TComplex tempD;
			arr >> tempD;
			valuesD[k] = tempD;
			k++;
		}
	}
	Matrix<TComplex>* matrix = new Matrix<TComplex>(height, width, valuesD);
	return matrix;
}

void ServerApp::recieve(QByteArray msg)
{
	qDebug() << "recieved:" << msg;
	QString answer;
	int message;
	int height;
	int width;
	int typeNum;
	msg >> message;
	msg >> typeNum;
	try
	{
		switch (message)
		{
		case DETERMINANT_REQUEST:
		{
			msg >> height;
			msg >> width;
			switch (typeNum)
			{
			case RATIONAL:
				if (height == width)
				{
					Rational* rez = CalcDeterminantAndRank<Rational>(msg, width);
					answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(RATIONAL) << QString().setNum(rez[0].decimal());
					answer << QString().setNum((rez[1].decimal()));
					delete[] rez;
				}
				else
				{
					int rez = CalcRank<Rational>(msg, height, width);
					answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(RATIONAL) << QString().setNum(rez);
				}
				break;

			case REAL:
				if (height == width)
				{
					double* rez = CalcDeterminantAndRank<double>(msg, width);
					answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(REAL) << QString().setNum(rez[0]);
					answer << QString().setNum((rez[1]));
					delete[] rez;
				}
				else
				{
					int rez = CalcRank<double>(msg, height, width);
					answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(REAL) << QString().setNum(rez);
				}
				break;

			case COMPLEX:
				if (height == width)
				{
					TComplex* rez = CalcDeterminantAndRank<TComplex>(msg, width);
					answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(COMPLEX) << QString().setNum(rez[0].re) << QString().setNum(rez[0].im);
					answer << QString().setNum((rez[1].re)) << QString().setNum(rez[1].im);
					delete[] rez;
				}
				else
				{
					int rez = CalcRank<TComplex>(msg, height, width);
					answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(COMPLEX) << QString().setNum(rez);
				}
				break;
			default:
				break;
			}
			break;
		}
		case TRANSPOSE_REQUEST:
		{
			msg >> height;
			msg >> width;
			switch (typeNum)
			{
			case RATIONAL:
				answer << QString().setNum(TRANSPOSE_ANSWER) << QString().setNum(RATIONAL) << QString().setNum(width) << QString().setNum(height) << Transpose<Rational>(msg, height, width);
				break;
			case REAL:
				answer << QString().setNum(TRANSPOSE_ANSWER) << QString().setNum(REAL) << QString().setNum(width) << QString().setNum(height) << Transpose<double>(msg, height, width);
				break;
			case COMPLEX:
				answer << QString().setNum(TRANSPOSE_ANSWER) << QString().setNum(COMPLEX) << QString().setNum(width) << QString().setNum(height) << Transpose<TComplex>(msg, height, width);
				break;
			default:
				break;
			}
			break;
		}

		default:
			answer << QString().setNum(ERROR_MESSAGE);
			break;
		}
	}
	catch (...)
	{
		answer << QString().setNum(ERROR_MESSAGE);
	}
	comm->send(QByteArray().append(answer.toLatin1()));
}


//template Matrix<double>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width);
//template Matrix<Rational>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width);
//template Matrix<TComplex>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width);
//template SquareMatrix<double>* ServerApp::CombineMatrix(QByteArray arr, uint size);
//template SquareMatrix<Rational>* ServerApp::CombineMatrix(QByteArray arr, uint size);
//template SquareMatrix<TComplex>* ServerApp::CombineMatrix(QByteArray arr, uint size);