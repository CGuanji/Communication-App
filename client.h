#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <iostream>
#include <QTcpServer>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();
    QTcpSocket *myclientSocket;


public slots:


    void on_Connect_button_clicked();

    void on_Send_button_clicked();

    void readyRead();

    void displayError(QAbstractSocket::SocketError socketError);

    void on_Disconnect_Button_clicked();

private:
    Ui::Client *ui;
};
#endif // CLIENT_H
