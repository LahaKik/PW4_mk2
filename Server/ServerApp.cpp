#include "ServerApp.h"

void ServerApp::recieve(QByteArray msg)
{
	qDebug() << "recieved";
	QString answer;
	int message;
	int size;
	msg >> message;
	msg >> size;
	try
	{
		switch (message)
		{
		case DETERMINANT_REQUEST:
		{
			number* rez = CalcDeterminantAndRank(msg, size);
			answer << QString().setNum(DETERMINANT_ANSWER) << QString().setNum(rez[0].decimal());
			answer << QString().setNum((rez[1].decimal()));
			delete[] rez;
			break;
		}
		case TRANSPOSE_REQUEST:
		{
			answer << QString().setNum(TRANSPOSE_ANSWER) << QString().setNum(size) << Transpose(msg, size);
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
	Matrix* matrix = CombineMatrix(arr, size);
	
	rezult[0] = matrix->Determinant();
	rezult[1] = matrix->ComputeRank();
	delete matrix;
	return rezult;
}

Matrix* ServerApp::CombineMatrix(QByteArray arr, uint size)
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
	Matrix* matrix = new Matrix(size, values);
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