#pragma once


#include <qcoreapplication.h>
#include <qobject.h>
#include <qudpsocket.h>

#include "Matrix.h"
#include "../QtConsoleApplication1/TCommunicator.h"

class ServerApp :
    public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;
    number* CalcDeterminantAndRank(QByteArray, uint);
    Matrix* CombineMatrix(QByteArray, uint);
    QString Transpose(QByteArray, uint);
public:
    ServerApp(int, char**);

public slots:
    void recieve(QByteArray);
};

