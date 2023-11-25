#pragma once
#include "../QtConsoleApplication1/TCommunicator.h"
#include "Matrix.h"
#include "SquareMatrix.h"
#include <qcoreapplication.h>
#include <qobject.h>
#include <qudpsocket.h>

class ServerApp :
    public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;

    template<class number>
    number* CalcDeterminantAndRank(QByteArray, uint);

    template<class number>
    SquareMatrix<number>* CombineMatrix(QByteArray, uint);

    template<class number>
    Matrix<number>* CombineMatrix(QByteArray, uint, uint);

    template<class number>
    QString Transpose(QByteArray, uint);

    template<class number>
    QString Transpose(QByteArray, uint, uint);

    template<class number>
    int CalcRank(QByteArray, uint, uint);
    
public:
    ServerApp(int, char**);


public slots:
    void recieve(QByteArray);
};


template<class number>
number* ServerApp::CalcDeterminantAndRank(QByteArray arr, uint size)
{
    number* rezult = new number[2]();
    SquareMatrix<number>* matrix = CombineMatrix<number>(arr, size);

    rezult[0] = matrix->Determinant();
    rezult[1] = matrix->ComputeRank();
    delete matrix;
    return rezult;
}


template<class number>
SquareMatrix<number>* ServerApp::CombineMatrix(QByteArray arr, uint size)
{
    return nullptr;
}



template<class number>
Matrix<number>* ServerApp::CombineMatrix(QByteArray arr, uint height, uint width)
{
    return nullptr;
}



template<class number>
QString ServerApp::Transpose(QByteArray arr, uint size)
{
    Matrix<number>* matrix = CombineMatrix<number>(arr, size);
    matrix->SetTransposed();
    QString rezult;
    rezult << *matrix;
    delete matrix;
    return rezult;
}


template<class number>
QString ServerApp::Transpose(QByteArray arr, uint height, uint width)
{
    if (height == width)
        return Transpose<number>(arr, width);
    Matrix<number>* matrix = CombineMatrix<number>(arr, height, width);
    matrix->SetTransposed();
    QString rezult;
    rezult << *matrix;
    delete matrix;
    return rezult;
}


template<class number>
int ServerApp::CalcRank(QByteArray arr, uint height, uint width)
{
    Matrix<number>* matrix = CombineMatrix<number>(arr, height, width);
    int rank = matrix->ComputeRank();
    delete matrix;
    return rank;
}


//template<> QString& operator<< (QString&, Matrix<TComplex>&);
//template<> QString& operator<< (QString&, Matrix<Rational>&);