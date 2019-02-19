#include "mainwindow.h"
#include <QDebug>
#include <QNetworkDatagram>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    socket = new QUdpSocket(this);
    QHostAddress velodyneAddress;
    bool ipSetFlag = velodyneAddress.setAddress("192.168.1.201");
    qDebug() << ipSetFlag;
    bool result =  socket->bind(QHostAddress::AnyIPv4, 2368);//velodyneAddress, 2368);//
        qDebug() << result;
        if(result)
        {
            qDebug() << "PASS";
        }
        else
        {
            qDebug() << "FAIL";
        }
        processPendingDatagrams();
        connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()),Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
}

void MainWindow::processPendingDatagrams()
 {
    qDebug() << "in !";
    QHostAddress sender;
    u_int16_t port;/*
    while (true) {
        qDebug()<<"OLL";
//        qDebug() << socket->hasPendingDatagrams();
        QNetworkDatagram datagram = socket->receiveDatagram();
        qDebug() <<datagram.isNull();
        //QByteArray datagram;
        //datagram.resize(socket->pendingDatagramSize());
        //socket->readDatagram(datagram.data(),datagram.size(),&sender,&port);

    }*/

    while (true)//socket->hasPendingDatagrams())
    {
        qDebug()<<socket->hasPendingDatagrams();
        if (socket->hasPendingDatagrams()){
         QByteArray datagram;
         datagram.resize(socket->pendingDatagramSize());
         socket->readDatagram(datagram.data(),datagram.size(),&sender,&port);
        qDebug() <<"Message From :: " << sender.toString();
        qDebug() <<"Port From :: "<< port;
        qDebug() <<"Message :: " << datagram;
        QThread::usleep(10000);
        }
    }
}
