#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QString ip, int port, QObject *parent = nullptr);

private slots:
    void newConnection();
    void disconnection();
    void readyRead();

private:
    QTcpServer *m_server;
    QVector <QTcpSocket*> m_clients;
};

#endif // SERVER_H
