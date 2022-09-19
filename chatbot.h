#ifndef CHATBOT_H
#define CHATBOT_H

#include <QDialog>

namespace Ui {
    class ChatBot;
}

class ChatBot : public QDialog {
    Q_OBJECT

public:
    explicit ChatBot(QWidget *parent = 0);
    ~ChatBot();

    int clicked_button_id;

private:
    Ui::ChatBot *ui;

private slots:
    int on_otherStuffButton_clicked();
    int on_traineesButton_clicked();
    int on_programmersButton_clicked();
    int on_allUsersButton_clicked();
};

#endif // CHATBOT_H
