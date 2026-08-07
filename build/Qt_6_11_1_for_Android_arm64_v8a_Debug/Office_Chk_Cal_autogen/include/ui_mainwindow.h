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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label_Username;
    QLabel *label_Password;
    QLineEdit *lineEdit_Username;
    QLineEdit *lineEdit_Password;
    QPushButton *pushButton_Login;
    QPushButton *pushButton_Cancel;
    QPushButton *pushButton_Finger;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(456, 904);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 451, 901));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"	color:yellow;\n"
"	font: 600 15pt \"Ubuntu Sans\";\n"
"}"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_Username = new QLabel(groupBox);
        label_Username->setObjectName("label_Username");
        label_Username->setGeometry(QRect(110, 100, 211, 51));
        label_Username->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_Password = new QLabel(groupBox);
        label_Password->setObjectName("label_Password");
        label_Password->setGeometry(QRect(110, 360, 211, 51));
        label_Password->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Username = new QLineEdit(groupBox);
        lineEdit_Username->setObjectName("lineEdit_Username");
        lineEdit_Username->setGeometry(QRect(110, 180, 211, 51));
        lineEdit_Username->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        lineEdit_Username->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Password = new QLineEdit(groupBox);
        lineEdit_Password->setObjectName("lineEdit_Password");
        lineEdit_Password->setGeometry(QRect(110, 450, 211, 51));
        lineEdit_Password->setEchoMode(QLineEdit::EchoMode::Password);
        lineEdit_Password->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_Login = new QPushButton(groupBox);
        pushButton_Login->setObjectName("pushButton_Login");
        pushButton_Login->setGeometry(QRect(230, 620, 131, 51));
        pushButton_Cancel = new QPushButton(groupBox);
        pushButton_Cancel->setObjectName("pushButton_Cancel");
        pushButton_Cancel->setGeometry(QRect(50, 620, 131, 51));
        pushButton_Finger = new QPushButton(groupBox);
        pushButton_Finger->setObjectName("pushButton_Finger");
        pushButton_Finger->setGeometry(QRect(140, 740, 141, 51));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Login Screen", nullptr));
        label_Username->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_Password->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lineEdit_Username->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Name", nullptr));
        lineEdit_Password->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Password", nullptr));
        pushButton_Login->setText(QString());
        pushButton_Cancel->setText(QString());
        pushButton_Finger->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
