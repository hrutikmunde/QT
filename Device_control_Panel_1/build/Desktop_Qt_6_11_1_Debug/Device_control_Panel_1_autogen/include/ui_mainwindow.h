/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QCheckBox *checkBox_Motor;
    QCheckBox *checkBox_LED;
    QCheckBox *checkBox_Buzzer;
    QCheckBox *checkBox_auto;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_exit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(439, 557);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(2, 10, 421, 31));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 70, 131, 21));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 190, 66, 18));
        label_3->setFont(font1);
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(30, 110, 181, 31));
        comboBox->setFont(font1);
        checkBox_Motor = new QCheckBox(centralwidget);
        checkBox_Motor->setObjectName("checkBox_Motor");
        checkBox_Motor->setGeometry(QRect(40, 220, 161, 23));
        checkBox_Motor->setFont(font1);
        checkBox_Motor->setMouseTracking(true);
        checkBox_LED = new QCheckBox(centralwidget);
        checkBox_LED->setObjectName("checkBox_LED");
        checkBox_LED->setGeometry(QRect(39, 260, 151, 23));
        checkBox_LED->setFont(font1);
        checkBox_LED->setMouseTracking(true);
        checkBox_Buzzer = new QCheckBox(centralwidget);
        checkBox_Buzzer->setObjectName("checkBox_Buzzer");
        checkBox_Buzzer->setGeometry(QRect(40, 300, 171, 23));
        checkBox_Buzzer->setFont(font1);
        checkBox_Buzzer->setMouseTracking(true);
        checkBox_auto = new QCheckBox(centralwidget);
        checkBox_auto->setObjectName("checkBox_auto");
        checkBox_auto->setGeometry(QRect(40, 350, 161, 23));
        checkBox_auto->setFont(font1);
        checkBox_auto->setMouseTracking(true);
        pushButton_start = new QPushButton(centralwidget);
        pushButton_start->setObjectName("pushButton_start");
        pushButton_start->setGeometry(QRect(50, 430, 94, 26));
        pushButton_start->setFont(font1);
        pushButton_start->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color:green;\n"
"	color:black;\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:black;\n"
"	color:green;\n"
"\n"
"}"));
        pushButton_stop = new QPushButton(centralwidget);
        pushButton_stop->setObjectName("pushButton_stop");
        pushButton_stop->setGeometry(QRect(180, 430, 94, 26));
        pushButton_stop->setFont(font1);
        pushButton_stop->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color:red;\n"
"	color:black;\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:red;\n"
"	color:black;\n"
"\n"
"}"));
        pushButton_reset = new QPushButton(centralwidget);
        pushButton_reset->setObjectName("pushButton_reset");
        pushButton_reset->setGeometry(QRect(300, 430, 94, 26));
        pushButton_reset->setFont(font1);
        pushButton_reset->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color:blue;\n"
"	color:black;\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:black;\n"
"	color:blue;\n"
"\n"
"}"));
        pushButton_exit = new QPushButton(centralwidget);
        pushButton_exit->setObjectName("pushButton_exit");
        pushButton_exit->setGeometry(QRect(180, 490, 94, 26));
        pushButton_exit->setFont(font1);
        pushButton_exit->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color:gray;\n"
"	color:black;\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:black;\n"
"	color:grey;\n"
"\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "DEVICE CONTROL PANEL", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Operating Mode", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Options", nullptr));
        checkBox_Motor->setText(QCoreApplication::translate("MainWindow", "Motor Enable", nullptr));
        checkBox_LED->setText(QCoreApplication::translate("MainWindow", "LED Enable", nullptr));
        checkBox_Buzzer->setText(QCoreApplication::translate("MainWindow", "Buzzer Enable", nullptr));
        checkBox_auto->setText(QCoreApplication::translate("MainWindow", "Auto Mode", nullptr));
        pushButton_start->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        pushButton_reset->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
