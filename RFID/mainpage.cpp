#include "mainpage.h"
#include "ui_mainpage.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>


MainPage::MainPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);

    setWindowTitle("RFID Accesory Tester");
    resize(1000, 700);

    // Main widget
    QWidget *centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    //COM port
    QLabel *portLabel = new QLabel("COM Port:");

    comboPort = new QComboBox();

    comboPort->addItem("COM3");
    comboPort->addItem("COM4");
    comboPort->addItem("COM5");


    //Baud Rate
    QLabel *baudLabel = new QLabel("Baud Rate:");

    comboBaud = new QComboBox();

    comboBaud->addItem("9600");
    comboBaud->addItem("19200");
    comboBaud->addItem("115200");

    comboBaud->setCurrentText("115200");

    // Connect button
    buttonConnect = new QPushButton("CONNECT");

    // Status
    labelStatus = new QLabel("Status: Disconnected");

    // Horizontal layout
    QHBoxLayout *connectionlayout = new QHBoxLayout();

    connectionlayout->addWidget(portLabel);
    connectionlayout->addWidget(comboPort);

    connectionlayout->addWidget(baudLabel);
    connectionlayout->addWidget(comboBaud);

    connectionlayout->addWidget(buttonConnect);

    connectionlayout->addWidget(labelStatus);

    mainLayout->addLayout(connectionlayout);


}

MainPage::~MainPage()
{
    delete ui;
}

void QMainWindow::loadSerialPorts()
{
    comboPort->clear();

    const auto ports = QSerialPortInfo::availablePorts();

    for(const QSerialPortInfo &port : ports)
    {
        comboPort->addItem(port.portName());
    }

    if(comboPort->count() == 0)
    {
        comboPort->addItem("No COM Port");
    }
}
