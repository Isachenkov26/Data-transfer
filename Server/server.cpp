#include "server.h"

Server::Server(QString ip, int port, QObject *parent)
    : QObject{parent}
{
    m_server = new QTcpServer();
    m_server->listen(QHostAddress(ip), port);

    if(m_server->isListening())
    {
        qDebug() << "Server started at: " << m_server->serverAddress() << m_server->serverPort();
    }
    else
        qDebug() << "Server failed to start " << m_server->serverError();
    connect(m_server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::newConnection()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    m_clients.push_back(client);
    qDebug() << "New client from: " << client->localAddress();
    connect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnection);
}

void Server::disconnection()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    m_clients.removeOne(client);
    qDebug() << "Disconnected client from: " << client->localAddress();
    disconnect(client, &QTcpSocket::readyRead, this, &Server::readyRead);
    disconnect(client, &QTcpSocket::disconnected, this, &Server::disconnection);
}

void Server::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    QByteArray data = client->readAll();
    for(QTcpSocket* buffer : m_clients){
        buffer->write(data);
    }
}
