#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Select Mode");
    ui->comboBox->addItem("Normal");
    ui->comboBox->addItem("Fast");
    ui->comboBox->addItem("Slow");
    ui->comboBox->addItem("Maintenance");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     qDebug() << "Select Operating mode";     break;
    case 1:     qDebug() << "Normal mode";     break;
    case 2:     qDebug() << "Fast mode";       break;
    case 3:     qDebug() << "Slow mode";       break;
    case 4:     qDebug() << "Maintenance";     break;
    }
}

void MainWindow::on_checkBox_Motor_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Checked)
    {
        qDebug() << "Motor Enable";
    }
    else
    {
        qDebug() << "Motor Disable";
    }
}


void MainWindow::on_checkBox_LED_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Checked)
    {
        qDebug() << "LED Enable";
    }
    else
    {
        qDebug() << "LED Disable";
    }
}


void MainWindow::on_checkBox_Buzzer_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Checked)
    {
        qDebug() << "Buzzer Enable";
    }
    else
    {
        qDebug() << "Buzzer Disable";
    }
}


void MainWindow::on_checkBox_auto_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Checked)
    {
        qDebug() << "Auto mode Enable";
        ui->comboBox->currentText();
    }
    else
    {
        qDebug() << "Auto mode Disable";
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    if(ui->comboBox->currentIndex() == 0)
    {
        qDebug() << "Selected Operating mode";
        return;
    }
    qDebug() << "Device Started";
    qDebug() << "Operating mode Selected : " << ui->comboBox->currentText();
}


void MainWindow::on_pushButton_reset_clicked()
{
    ui->comboBox->setCurrentIndex(0);

    ui->checkBox_Motor->setChecked(false);
    ui->checkBox_LED->setChecked(false);
    ui->checkBox_Buzzer->setChecked(false);
    ui->checkBox_auto->setChecked(false);
}


void MainWindow::on_pushButton_stop_clicked()
{
    qDebug() << "Device Stopped";

}

void MainWindow::on_pushButton_exit_clicked()
{
    close();
}