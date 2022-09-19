#include "mainwindow.h"
#include "dlgregister.h"
#include "ui_dlgregister.h"

// constructor
DlgRegister::DlgRegister(QTcpSocket* socket, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DlgRegister)
{
    ui->setupUi(this);
    this->socket = socket;
}

// destructor
DlgRegister::~DlgRegister() {
    delete ui;
}

// clicking on "Ok"
void DlgRegister::on_okButton_clicked() {
    QString name = ui->lineName->text();
    QString login = ui->lineLogin->text();
    QString password = ui->lineNewPassword->text();
    QString role = ui->lineRole->text();
    QByteArray buffer;
    buffer.append("New user info: ");
    buffer.append(name);
    buffer.append("\n");
    buffer.append(login);
    buffer.append("\n");
    buffer.append(password);
    buffer.append("\n");
    buffer.append(role);
    socket->write(buffer);
}

// clicking on "Cancel"
void DlgRegister::on_cancelButton_clicked() {
    this->hide();
    this->destroy(true, true);
}
