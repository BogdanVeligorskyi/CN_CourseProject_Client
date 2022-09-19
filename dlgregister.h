#ifndef DLGREGISTER_H
#define DLGREGISTER_H

#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
    class DlgRegister;
}

class DlgRegister : public QDialog {
    Q_OBJECT

    QTcpSocket* socket;

public:
    explicit DlgRegister(QTcpSocket* socket, QWidget *parent = 0);
    ~DlgRegister();

private:
    Ui::DlgRegister *ui;

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
};

#endif // DLGREGISTER_H
