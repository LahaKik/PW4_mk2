#include "ServerApp.h"

void ServerApp::recieve(QByteArray msg)
{
	qDebug() << "recieved:" << msg;
	QString answer;
	int message;
	int height;
	int width;
	msg >> message;
	try
	{
		switch (message)
		{
		case DETERMINANT_REQUEST:
		{
			msg >> height;
			msg >> width;
			if(height == width)
			{
				number* rez = CalcDeterminantAndRank(msg, width);
				answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(rez[0].decimal());
				answer << QString().setNum((rez[1].decimal()));
				delete[] rez;
			}
			else
			{
				int rez = CalcRank(msg, height, width);
				answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(rez);
			}
			break;
		}
		case TRANSPOSE_REQUEST:
		{
			msg >> height;
			msg >> width;
			answer << QString().setNum(TRANSPOSE_ANSWER) << QString().setNum(width) << QString().setNum(height) << Transpose(msg, height, width);
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

ServerApp::ServerApp(int argc, char** argv) : QCoreApplication(argc, argv)
{
	TCommParams servParams = { QHostAddress::LocalHost, 10000,
								QHostAddress::LocalHost, 10001 };
	comm = new TCommunicator(servParams, this);

	connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

number* ServerApp::CalcDeterminantAndRank(QByteArray arr, uint size)
{
	number* rezult = new Rational[2]();
	SquareMatrix* matrix = CombineMatrix(arr, size);
	
	rezult[0] = matrix->Determinant();
	rezult[1] = matrix->ComputeRank();
	delete matrix;
	return rezult;
}

SquareMatrix* ServerApp::CombineMatrix(QByteArray arr, uint size)
{
	number* values = new number[size * size];
	uint k = 0;
	for (uint i = 0; i < size; i++)
	{
		for (uint j = 0; j < size; j++)
		{
			Rational temp;
			arr >> temp;
			values[k] = temp;
			k++;
		}
	}
	SquareMatrix* matrix = new SquareMatrix(size, values);
	return matrix;
}

Matrix* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width)
{
	number* values = new number[height * width];
	uint k = 0;
	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			Rational temp;
			arr >> temp;
			values[k] = temp;
			k++;
		}
	}
	Matrix* matrix = new Matrix(height, width, values);
	return matrix;
}

QString ServerApp::Transpose(QByteArray arr, uint size)
{
	Matrix* matrix = CombineMatrix(arr, size);
	matrix->SetTransposed();
	QString rezult = matrix->ToQString();
	delete matrix;
	return rezult;
}

QString ServerApp::Transpose(QByteArray arr, uint height, uint width)
{
	if (height == width)
		return Transpose(arr, width);
	Matrix* matrix = CombineMatrix(arr, height, width);
	matrix->SetTransposed();
	QString rezult = matrix->ToQString();
	delete matrix;
	return rezult;
}

int ServerApp::CalcRank(QByteArray arr, uint height, uint width)
{
	Matrix* matrix = CombineMatrix(arr, height, width);
	int rank = matrix->ComputeRank();
	delete matrix;
	return rank;
}