#pragma once


#include <qcoreapplication.h>
#include <qobject.h>
#include <qudpsocket.h>

#include "SquareMatrix.h"
#include "../QtConsoleApplication1/TCommunicator.h"

class ServerApp :
    public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;
    number* CalcDeterminantAndRank(QByteArray, uint);
    SquareMatrix* CombineMatrix(QByteArray, uint);
    Matrix* CombineMatrix(QByteArray, uint, uint);
    QString Transpose(QByteArray, uint);
    QString Transpose(QByteArray, uint, uint);
    int CalcRank(QByteArray, uint, uint);
public:
    ServerApp(int, char**);

public slots:
    void recieve(QByteArray);
};

