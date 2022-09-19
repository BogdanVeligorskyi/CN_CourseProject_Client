#include "mainwindow.h"
#include "dlglogin.h"
#include "ui_dlglogin.h"

// constructor
DlgLogin::DlgLogin(QTcpSocket* socket, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DlgLogin)
{
    ui->setupUi(this);
    this->socket = socket;
}

// destructor
DlgLogin::~DlgLogin() {
    delete ui;
}

// clicking on "Ok"
void DlgLogin::on_okButton_clicked() {
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    QByteArray buffer;
    buffer.append("Login info: ");
    buffer.append(login);
    buffer.append("\n");
    buffer.append(password);
    socket->write(buffer);
}

// clicking on "Cancel"
void DlgLogin::on_cancelButton_clicked() {
    this->hide();
    this->destroy(true, true);
}
