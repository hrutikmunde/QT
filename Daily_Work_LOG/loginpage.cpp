#include "loginpage.h"
#include "./ui_loginpage.h"
#include "worklog.h"
#define User "Hrutik"
#define Pass "01062001"

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->pushButton_Login->setText("Login");
    ui->pushButton_Cancel->setText("Cancel");
    ui->label_Username->setText("Username");
    ui->label_Password->setText("Password");
    ui->pushButton_Finger->setText("Fingerprint");

    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_pushButton_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Exit",
                                  "Are you sure to close the Application ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


void LoginPage::on_pushButton_Login_clicked()
{
    QString Username = ui->lineEdit_Username->text();
    QString Password = ui->lineEdit_Password->text();
    if(Username == User && Password == Pass)
    {
        QMessageBox::information(this,
                                 "Login.",
                                 "Login Successfully..");

        Worklog *worklog = new Worklog();
        worklog->show();
        this->hide();
    }
    else if(Username != User && Password != Pass)
    {
        QMessageBox::warning(this,
                             "Login Failed",
                             "Invalid UserName & Password, please try again");
    }
    else if(Username != User)
    {
        QMessageBox::warning(this,
                             "Login Failed",
                             "Invalid UserName, please try again");
    }
    else if(Password != Pass)
    {
        QMessageBox::warning(this,
                             "Login Failed",
                             "Invalid Password, please try again");
    }
}




