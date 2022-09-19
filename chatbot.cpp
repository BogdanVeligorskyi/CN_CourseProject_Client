#include "chatbot.h"
#include "ui_chatbot.h"

// constructor
ChatBot::ChatBot(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ChatBot)
{
    ui->setupUi(this);
}

// destructor
ChatBot::~ChatBot() {
    delete ui;
}

// "All users" query of ChatBot
int ChatBot::on_allUsersButton_clicked() {
    clicked_button_id = 0;
    this->close();
    return clicked_button_id;
}

// "Programmers" query of ChatBot
int ChatBot::on_programmersButton_clicked() {
    clicked_button_id = 1;
    this->close();
    return clicked_button_id;
}

// "Trainees" query of ChatBot
int ChatBot::on_traineesButton_clicked() {
    clicked_button_id = 2;
    this->close();
    return clicked_button_id;
}

// "Other Stuff" query of ChatBot
int ChatBot::on_otherStuffButton_clicked() {
    clicked_button_id = 3;
    this->close();
    return clicked_button_id;
}
