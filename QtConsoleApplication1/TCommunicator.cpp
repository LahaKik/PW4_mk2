#include "TCommunicator.h"

TCommunicator::TCommunicator(TCommParams& parameters, QObject* parent)
{
	params = parameters;
	ready = bind(params.rHost, params.rPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
	if (ready)
		connect(this, SIGNAL(readyRead()), this, SLOT(recieve()));
}

void TCommunicator::send(QByteArray arr)
{
	if (ready)
	{
		writeDatagram(arr, params.sHost, params.sPort);

	}
}

void TCommunicator::recieve()
{
	if (hasPendingDatagrams())
	{
		quint64 size = pendingDatagramSize();
		QByteArray messg(size, 0);
		readDatagram(messg.data(), size);

		emit recieved(messg);
	}
}
