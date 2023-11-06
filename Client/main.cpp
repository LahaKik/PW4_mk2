#include <QtCore/QCoreApplication>
#include <qapplication.h>
#include "ClientApp.h"

int main(int argc, char* argv[])
{
    ClientApp clientApp(argc, argv);

    return clientApp.exec();
}