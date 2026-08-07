#include "mainwindow.h"
#include "./ui_mainwindow.h"


#define User "Hrutik"
#define Pass "01062001"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_Login->setText("Login");
    ui->pushButton_Cancel->setText("Cancel");
    ui->label_Username->setText("Username");
    ui->label_Password->setText("Password");
    ui->pushButton_Finger->setText("Fingerprint");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "", "Are you sure to close the Application ?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


void MainWindow::on_pushButton_Login_clicked()
{
    QString Username = ui->lineEdit_Username->text();
    QString Password = ui->lineEdit_Password->text();
    if(Username == User && Password == Pass)
    {
        QMessageBox::information(this, "Login.", "Login Successfully..");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    else if(Username != User && Password != Pass)
    {
        QMessageBox::warning(this, "Login Failed...!", "Invalid UserName & Password, please try again");
    }
    else if(Username != User)
    {
        QMessageBox::warning(this, "Login Failed...!", "Invalid UserName, please try again");
    }
    else if(Password != Pass)
    {
        QMessageBox::warning(this, "Login Failed...!", "Invalid Password, please try again");
    }
}


void MainWindow::on_pushButton_Finger_clicked()
{
    this->hide();
    MainPage *mainpage = new MainPage();
    mainpage->show();

}

