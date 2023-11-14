#pragma once

#include <qobject.h>
#include <qapplication.h>
#include "TInterface.h"
#include "../QtConsoleApplication1/TCommunicator.h"


class ClientApp :
    public QApplication
{
    Q_OBJECT;

    TInterface* InterfMatr;
    AdditionalInterface* InterfSize;
    TCommunicator* comm;
public:
    ClientApp(int, char**);
    ~ClientApp();

public slots:
    void SendToServ(QString);
    void RecievefromServ(QByteArray);
    void Reconnect(TInterface*);

signals:
    void transfer(QString);
};

