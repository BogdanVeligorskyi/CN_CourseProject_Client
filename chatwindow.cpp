#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatbot.h"

// constructor
ChatWindow::ChatWindow(QTcpSocket *socketc, QStringList users_list,
                       QString user_name, QWidget *parent) :
QDialog(parent),
ui(new Ui::ChatWindow)
{
    socketc->close();
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 8080);
    this->users_list = users_list;
    ui->setupUi(this);
    ui->labelUserName->setText(user_name);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));

    // creating list of users
    for (int i = 0; i<users_list.size()-1; i++) {
        ui->listWidget->addItem(users_list.value(i));
    }
}

// destructor
ChatWindow::~ChatWindow() {
    delete ui;
}

// reading answer from server
void ChatWindow::sockReady() {
    QByteArray data = socket->readAll();
    QString str = QByteArray(data);
    if (str.startsWith("allMessages"))
        str.remove(0, 11);
    else if (str.startsWith("chatBot0Result"))
        str.remove(0, 14);
    else if (str.startsWith("chatBot1Result"))
        str.remove(0, 14);
    else if (str.startsWith("chatBot2Result"))
        str.remove(0, 14);
    else if (str.startsWith("chatBot3Result"))
        str.remove(0, 14);
    ui->textEdit->setText(str);
}

// socket disconnection
void ChatWindow::sockDisc() {
    socket->deleteLater();
}

// pressing on item in list widget: getting history of conversation
void ChatWindow::on_listWidget_itemPressed(QListWidgetItem* item) {
    QByteArray buffer;
    reciever = item->text();
    buffer.append("messagesHistory");
    buffer.append(ui->labelUserName->text());
    buffer.append("\n");
    buffer.append(reciever);
    socket->write(buffer, buffer.size());
}

// clicking on "Send" button: sending message to another user
void ChatWindow::on_sendButton_clicked() {
    // message format:
    // "Date"| "Sender"| "Message"
    QDateTime cdt = QDateTime::currentDateTime();
    QString message = cdt.toString("dd.MM.yyyy hh:mm:ss");
    QByteArray buffer;
    message.append("| ");
    message.append(ui->labelUserName->text());
    message.append("| ");
    message.append(ui->lineEnter->text());
    ui->textEdit->append(message);
    message.append("| ");
    message.append(reciever);
    message.replace("| ", "\n");
    buffer.append("newMessage");
    buffer.append(message);
    socket->write(buffer);
}

// clicking on "Use bot" button: opening window of queries to server
void ChatWindow::on_useBotButton_clicked() {
    ChatBot *bot = new ChatBot();
    bot->exec();
    QByteArray buffer;
    if (bot->clicked_button_id == 0) {
        buffer.append("chatBot0");
        socket->write(buffer);
    }
    else if (bot->clicked_button_id == 1) {
        buffer.append("chatBot1");
        socket->write(buffer);
    }
    else if (bot->clicked_button_id == 2) {
        buffer.append("chatBot2");
        socket->write(buffer);
    }
    else if (bot->clicked_button_id == 3) {
        buffer.append("chatBot3");
        socket->write(buffer);
    }
}

// searching for users that match entered prompt
void ChatWindow::on_lineEdit_textChanged(QString str) {
    ui->listWidget->clear();
    for (int i = 0; i < users_list.size()-1; i++) {
        QString user = users_list.value(i);
        if (user.contains(str, Qt::CaseInsensitive))
            ui->listWidget->addItem(users_list.value(i));
    }
    // if line is empty - show all users in list
    if (str == "") {
        ui->listWidget->clear();
        for (int i = 0; i<users_list.size()-1; i++) {
            ui->listWidget->addItem(users_list.value(i));
        }
    }
}

void ChatWindow::on_ChatWindow_accepted()
{
    ui->labelWelcome->setText("HAAH");
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 8080);
}

/*void ChatWindow::on_ChatWindow_customContextMenuRequested(QPoint pos)
{
    ui->labelWelcome->setText("HAHA");
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 8080);
}*/
