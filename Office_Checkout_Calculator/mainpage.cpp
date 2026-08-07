#include "mainpage.h"
#include "ui_mainpage.h"
#include "mainwindow.h"

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_btncalculate_clicked()
{
    QTime time = ui->timeEdit->time();

    if(ui->radiofull->isChecked())
        time = time.addSecs((8 * 3600) + (45 * 60));
    else if(ui->radiofull_2->isChecked())
        time = time.addSecs((4 *3600) + (30 * 60));
    else if(ui->radioEarly2->isChecked())
        time = time.addSecs((7 * 3600));
    else if(ui->radioHalf->isChecked())
        time = time.addSecs((8 * 3600) + (30 * 60));


    ui->lblresult->setText(time.toString("hh:mm AP"));
}


void MainPage::on_pushButton_close_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "close", "Are you want to close the application ?", QMessageBox::Yes | QMessageBox::No);
    if(reply ==QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


void MainPage::on_pushButton_clicked()
{
    this->hide();
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();
}

