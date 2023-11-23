#pragma once

#include <qobject.h>
#include <qudpsocket.h>

struct TCommParams
{
    QHostAddress rHost;
    quint16      rPort;
    QHostAddress sHost;
    quint16      sPort;
};

class TCommunicator :
    public QUdpSocket
{
    Q_OBJECT

        bool ready;
    TCommParams params;
public:
    TCommunicator(TCommParams&, QObject* parent = nullptr);
    bool IsReady() const { return ready; }

public slots:
    void send(QByteArray);

private slots:
    void recieve();

signals:
    void recieved(QByteArray);
};

