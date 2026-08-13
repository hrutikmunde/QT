#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "mainpage.h"
#define User "Hrutik"
#define Pass "123456"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Login" ,"Are you sure to close the application ?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


void LoginWindow::on_pushButton_clicked()
{
    QString Username = ui->lineEdit->text();
    QString Password = ui->lineEdit_2->text();
    if(Username == User && Password == Pass)
    {
        QMessageBox::information(this, "Login","                         Login Success...");
        this->show();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    else if(Username != User && Password != Pass)
    {
        QMessageBox::warning(this, "Login","Invalid Login & Password, please try again...");
    }
    else if(Username != User)
    {
        QMessageBox::warning(this, "Login","Invalid Login, please try again...");
    }
    else if(Password != Pass)
    {
        QMessageBox::warning(this, "Login","Invalid Password, please try again...");
    }
}
