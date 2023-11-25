#include "ClientApp.h"

ClientApp::ClientApp(int argc, char** argv) : QApplication(argc, argv)
{
	TCommParams params = { QHostAddress::LocalHost, 10001,
						  QHostAddress::LocalHost, 10000 };

	comm = new TCommunicator(params, this);

	InterfMatr = new TInterface(2, 2);
	InterfSize = new AdditionalInterface(InterfMatr, InterfMatr);
	InterfSize->show();

	connect(InterfSize, SIGNAL(ChangedSize(TInterface*)), this, SLOT(Reconnect(TInterface*)));
	connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(RecievefromServ(QByteArray)));

}

ClientApp::~ClientApp()
{
	delete InterfSize;
	delete comm;
}

void ClientApp::SendToServ(QString str)
{
	//qDebug() << "request sended" << str;
	comm->send(QByteArray().append(str.toLatin1()));
}

void ClientApp::RecievefromServ(QByteArray arr)
{
	emit transfer(QString(arr));
}

void ClientApp::Reconnect(TInterface* fc)
{
	connect(fc, SIGNAL(request(QString)), this, SLOT(SendToServ(QString)));
	connect(this, SIGNAL(transfer(QString)), fc, SLOT(reception(QString)));
}