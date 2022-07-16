#include "clientdatatransfer.h"
#include "ui_clientdatatransfer.h"

ClientDataTransfer::ClientDataTransfer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientDataTransfer)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0, "Enter");
    ui->tabWidget->setTabText(1, "Action");
    ui->lTextFile->setReadOnly(true);

    m_socket = new QTcpSocket();

    connect(m_socket, &QTcpSocket::connected, this, &ClientDataTransfer::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientDataTransfer::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientDataTransfer::fileReady);

    connect(ui->bPush, &QPushButton::clicked, this, &ClientDataTransfer::connectToServer);
    connect(ui->bFind, &QPushButton::clicked, this, &ClientDataTransfer::searchFile);
    connect(ui->bSend, &QPushButton::clicked, this, &ClientDataTransfer::sendFile);
    connect(ui->bGet, &QPushButton::clicked, this, &ClientDataTransfer::getFile);
    connect(ui->bRestart, &QPushButton::clicked, this, &ClientDataTransfer::restart);
}

ClientDataTransfer::~ClientDataTransfer()
{
    delete ui;
}

QByteArray text;
//QString type;

void ClientDataTransfer::connectToServer()
{
    m_socket->connectToHost(ui->lIp->text(), ui->sPort->value());
}

void ClientDataTransfer::connected()
{
    ui->tabWidget->setCurrentIndex(1);
}

void ClientDataTransfer::searchFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Search File"), QDir::homePath(), tr("File (*.txt *.dat *.bin *.jpg *.mp3 *.mp4 *.docx *.pdf *.png *.avi *.doc)"));
    ui->lTextFile->setText(file);
    QFile myFile(file);
    myFile.open(QIODevice::ReadOnly);
    text = myFile.readAll();
    if (myFile.isOpen()) {
            qDebug() << "File is open!";
        } else {
            qDebug() << "Failed to open the file!";
        }
    myFile.close();
//    QFileInfo path(file);
//    type = "File (*." + path.suffix() + ")";
//    QByteArray bytes = type.toLocal8Bit();
//    strcpy(types, bytes.data());
//    QFileInfo path(file);
//     type = path.suffix();
}

void ClientDataTransfer::sendFile()
{
    m_socket->write(text);
    ui->lTextFile->setText("");
    qDebug() << "File sended!";
}

void ClientDataTransfer::getFile()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("File (*.txt *.dat *.bin *.jpg *.mp3 *.mp4 *.docx *.pdf *.png *.avi *.doc)"));
    QFile myFile(file);
    myFile.open(QIODevice::WriteOnly);
    myFile.write(m_socket->readAll());
    qDebug() << "File received!";
    ui->lReady->setText("The file is not ready");
}

void ClientDataTransfer::fileReady()
{
    ui->lReady->setText("The file is ready");
}

void ClientDataTransfer::restart()
{
    QByteArray example;
    example.push_back(m_socket->readAll());
    qDebug() << "Program restarted. Socket clear!";
    ui->lReady->setText("The file is not ready");
}
