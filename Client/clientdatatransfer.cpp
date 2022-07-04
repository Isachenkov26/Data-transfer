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
    connect(ui->bFind, &QPushButton::clicked, this, &ClientDataTransfer::searchFile);
    connect(ui->bSend, &QPushButton::clicked, this, &ClientDataTransfer::sendFile);
    connect(ui->bGet, &QPushButton::clicked, this, &ClientDataTransfer::getFile);
}

ClientDataTransfer::~ClientDataTransfer()
{
    delete ui;
}

void ClientDataTransfer::searchFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Search File"), QDir::homePath(), tr("file (*.txt)"));
    ui->lTextFile->setText(file);
}

void ClientDataTransfer::sendFile()
{
    if(ui->lTextFile->text() != ""){
        ui->tabWidget->setCurrentIndex(1);
    }
}

void ClientDataTransfer::getFile()
{
    ui->tabWidget->setCurrentIndex(1);
}
