#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);


}






Client::~Client()
{
    delete ui;
    delete myclientSocket;
}


void Client::readyRead(){
    QByteArray myByte;
    myByte = myclientSocket->readAll();
    ui->Server_message->setText(QString(myByte));
}


void Client::on_Connect_button_clicked()
{
    myclientSocket=new QTcpSocket(this);

    connect(myclientSocket,SIGNAL (readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);

    myclientSocket->connectToHost(ui->TCP_Enter->toPlainText(),
                                  ui->Port_Enter->toPlainText().toInt(), QIODevice::ReadWrite);





    if(myclientSocket->waitForConnected(300)){
        ui->Server_message->setText("connect to challenge.airtime.com port 2323");
        qDebug()<<"Connected";
    }
    else{
        ui->Server_message->setText("Connect Failed to challenge.airtime.com port 2323");
        qDebug()<<"Not Connected";
    }


}

void Client::on_Disconnect_Button_clicked()
{
    if(myclientSocket->isOpen()){
        myclientSocket->close();
        ui->Server_message->setText("Connect to challenge.airtime.com port 2323 is closed");
        qDebug()<<"Not Connected";
    }
}



void Client::on_Send_button_clicked()
{

     QString myStr = ui->Message_Enter->toPlainText();

    // states always shows disconnect:(
//     if(myclientSocket->state() == QAbstractSocket::ConnectedState)
//     {
//         qDebug()<<"Connect!";
//     }



     myclientSocket->write(myStr.toUtf8());
     myclientSocket->flush();
     myclientSocket->waitForBytesWritten(1000);
     ui->Server_message->setText("Client Send: "+ QString(myStr));






}



void Client:: displayError(QAbstractSocket::SocketError socketError){
    switch(socketError){
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this,tr("Fortune Client"),
                                     tr("The host was not found. Please check thehost name and port settings."  ));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this,tr("Fortune Client"),tr("The connection was refused by the peer."
                                                                  "Make sure the fortune server is running"));
        break;
    default:
        QMessageBox::information(this,tr("Fortune Client"),
                                 tr("The following error occured: %1.").arg(myclientSocket->errorString()));
    }
}




