#ifndef CLIENTDATATRANSFER_H
#define CLIENTDATATRANSFER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QTcpSocket>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientDataTransfer; }
QT_END_NAMESPACE

class ClientDataTransfer : public QMainWindow
{
    Q_OBJECT

public:
    ClientDataTransfer(QWidget *parent = nullptr);
    ~ClientDataTransfer();

private slots:
    void connectToServer();
    void connected();
    void searchFile();
    void sendFile();
    void getFile();
    void fileReady();
    void deleteFile();

private:
    Ui::ClientDataTransfer *ui;
    QTcpSocket *m_socket;
};
#endif // CLIENTDATATRANSFER_H
