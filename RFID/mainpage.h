#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QSerialPortInfo>


namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private:
    Ui::MainPage *ui;

    QComboBox *comboPort;
    QComboBox *comboBaud;

    QPushButton *buttonConnect;

    QLabel *labelStatus;

    void loadSerialPorts();

};

#endif // MAINPAGE_H
