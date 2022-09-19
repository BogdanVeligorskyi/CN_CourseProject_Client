#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QTcpSocket>

namespace Ui {
    class DlgLogin;
}

class DlgLogin : public QDialog {
    Q_OBJECT

    QTcpSocket* socket;

public:
    explicit DlgLogin(QTcpSocket* socket, QWidget *parent = 0);
    ~DlgLogin();

private:
    Ui::DlgLogin *ui;

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
};

#endif // DLGLOGIN_H
