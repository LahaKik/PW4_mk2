#include <QtCore/QCoreApplication>
#include "ServerApp.h"

int main(int argc, char *argv[])
{
    ServerApp serverApp(argc, argv);

    return serverApp.exec();
}
