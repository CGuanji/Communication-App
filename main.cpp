#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client *client = new Client();
    client->show();

    return a.exec();
}
