#ifndef CLIENTDATATRANSFER_H
#define CLIENTDATATRANSFER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>

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
    void searchFile();
    void sendFile();
    void getFile();

private:
    Ui::ClientDataTransfer *ui;
};
#endif // CLIENTDATATRANSFER_H
