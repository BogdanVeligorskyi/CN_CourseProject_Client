#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <dlgLogin.h>
#include <dlgRegister.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTcpSocket* socket;

public slots:
    void sockReady();
    void sockDisc();

private:
    Ui::MainWindow *ui;
    DlgLogin *login;
    DlgRegister* registration;

private slots:
    void on_registerButton_clicked();
    void on_loginButton_clicked();

};

#endif // MAINWINDOW_H
