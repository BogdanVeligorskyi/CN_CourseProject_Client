#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QListWidget>
#include <QDateTime>
#include <chatbot.h>

namespace Ui {
    class ChatWindow;
}

class ChatWindow : public QDialog {
    Q_OBJECT

public:
    explicit ChatWindow(QTcpSocket* socket, QStringList users_list,
                        QString user_name, QWidget *parent = 0);
    ~ChatWindow();

    QTcpSocket *socket;
    QString reciever;
    QStringList users_list;

private:
    Ui::ChatWindow *ui;

private slots:
    void on_ChatWindow_accepted();
    //void on_ChatWindow_customContextMenuRequested(QPoint pos);
    void on_useBotButton_clicked();
    void on_sendButton_clicked();
    void on_lineEdit_textChanged(QString );
    void on_listWidget_itemPressed(QListWidgetItem* item);
    void sockReady();
    void sockDisc();
};

#endif // CHATWINDOW_H
