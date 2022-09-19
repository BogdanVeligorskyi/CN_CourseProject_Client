#include "mainwindow.h"
#include "chatwindow.h"
#include "dlgLogin.h"
#include "dlgRegister.h"
#include "ui_mainwindow.h"

// constructor
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 8080);
    login = new DlgLogin(socket, this);
    registration = new DlgRegister(socket, this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
}

// destructor
MainWindow::~MainWindow() {
    delete ui;
}

// socket ready for connection
void MainWindow::sockReady(){
    QByteArray data = socket->readAll();
    QString str = QByteArray(data);

    // if log in wasn`t successful
    if (str.startsWith("falseLogin")) {
        QMessageBox::information(this, "Log In", "Incorrect login or password!");
    }

    // if log in was successful - open ChatWindow
    else if (str.startsWith("trueLogin")) {
        QMessageBox::information(this, "Log In", "You`ve logged in successfully!");
        QStringList users_list;
        this->hide();
        login->hide();
        str.remove(0, 9);
        users_list = str.split("\n");

        ChatWindow *chat = new ChatWindow(socket, users_list,
                                          users_list.value(users_list.size()-1), this);
        chat->exec();
    }

    // if registration wasn`t successful
    else if (str.startsWith("falseRegister")) {
        QMessageBox::information(this,
                                 "Registration", "This user name already exists!");
    }

    // if registration was successful - open ChatWindow
    else if (str.startsWith("trueRegister")) {
        QMessageBox::information(this,
                                 "Registration", "You`ve registered successfully!");
        QStringList users_list;
        this->hide();
        registration->hide();
        str.remove(0, 12);
        users_list = str.split("\n");
        ChatWindow *chat = new ChatWindow(socket, users_list,
                                          users_list.value(users_list.size()-1), this);
        chat->exec();
    }
}

// clicking on "Login"
void MainWindow::on_loginButton_clicked() {
    this->hide();
    login->exec();
    this->show();
}

// clicking on "Register"
void MainWindow::on_registerButton_clicked() {
    this->hide();
    registration->exec();
    this->show();
}

// socket disconnection
void MainWindow::sockDisc(){
    socket->deleteLater();
}
