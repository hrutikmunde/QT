/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QGroupBox *groupBox;
    QTimeEdit *timeEdit;
    QLabel *label;
    QRadioButton *radiofull;
    QLabel *lbl_Chk_in_time_2;
    QRadioButton *radioEarly2;
    QRadioButton *radioHalf;
    QPushButton *btncalculate;
    QLabel *lblresult;
    QLabel *label_2;
    QRadioButton *radiofull_2;
    QPushButton *pushButton_close;
    QPushButton *pushButton;

    void setupUi(QWidget *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName("MainPage");
        MainPage->resize(451, 909);
        groupBox = new QGroupBox(MainPage);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 10, 441, 821));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"	color:cyan;\n"
"}"));
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        timeEdit = new QTimeEdit(groupBox);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setGeometry(QRect(240, 134, 121, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(false);
        timeEdit->setFont(font1);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 138, 141, 41));
        label->setFont(font1);
        radiofull = new QRadioButton(groupBox);
        radiofull->setObjectName("radiofull");
        radiofull->setGeometry(QRect(130, 290, 171, 31));
        radiofull->setFont(font1);
        lbl_Chk_in_time_2 = new QLabel(groupBox);
        lbl_Chk_in_time_2->setObjectName("lbl_Chk_in_time_2");
        lbl_Chk_in_time_2->setGeometry(QRect(50, 250, 151, 31));
        lbl_Chk_in_time_2->setFont(font1);
        radioEarly2 = new QRadioButton(groupBox);
        radioEarly2->setObjectName("radioEarly2");
        radioEarly2->setGeometry(QRect(130, 410, 161, 31));
        radioEarly2->setFont(font1);
        radioHalf = new QRadioButton(groupBox);
        radioHalf->setObjectName("radioHalf");
        radioHalf->setGeometry(QRect(130, 370, 171, 31));
        radioHalf->setFont(font1);
        btncalculate = new QPushButton(groupBox);
        btncalculate->setObjectName("btncalculate");
        btncalculate->setGeometry(QRect(150, 540, 121, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font2.setPointSize(16);
        font2.setWeight(QFont::Medium);
        font2.setItalic(false);
        btncalculate->setFont(font2);
        btncalculate->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color:red;\n"
"	color:black;\n"
"	font: 500 16pt \"Ubuntu Sans\";\n"
"}"));
        lblresult = new QLabel(groupBox);
        lblresult->setObjectName("lblresult");
        lblresult->setGeometry(QRect(130, 680, 151, 51));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        lblresult->setFont(font3);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 615, 171, 31));
        label_2->setFont(font1);
        radiofull_2 = new QRadioButton(groupBox);
        radiofull_2->setObjectName("radiofull_2");
        radiofull_2->setGeometry(QRect(130, 330, 171, 31));
        radiofull_2->setFont(font1);
        pushButton_close = new QPushButton(MainPage);
        pushButton_close->setObjectName("pushButton_close");
        pushButton_close->setGeometry(QRect(250, 850, 131, 41));
        pushButton = new QPushButton(MainPage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 850, 121, 41));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(false);
        pushButton->setFont(font4);

        retranslateUi(MainPage);

        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QWidget *MainPage)
    {
        MainPage->setWindowTitle(QCoreApplication::translate("MainPage", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainPage", "OFFICE CHECKOUT CALCULATOR", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("MainPage", "hh:mm\342\200\257Ap", nullptr));
        label->setText(QCoreApplication::translate("MainPage", "Check-in Time:", nullptr));
        radiofull->setText(QCoreApplication::translate("MainPage", "Full Day (8:45)", nullptr));
        lbl_Chk_in_time_2->setText(QCoreApplication::translate("MainPage", "Working Hours:", nullptr));
        radioEarly2->setText(QCoreApplication::translate("MainPage", "Two Hour Early", nullptr));
        radioHalf->setText(QCoreApplication::translate("MainPage", "Half Hour Early", nullptr));
        btncalculate->setText(QCoreApplication::translate("MainPage", "Calculate", nullptr));
        lblresult->setText(QString());
        label_2->setText(QCoreApplication::translate("MainPage", "Check-out Time:", nullptr));
        radiofull_2->setText(QCoreApplication::translate("MainPage", "Half Day (4:30)", nullptr));
        pushButton_close->setText(QCoreApplication::translate("MainPage", "Close", nullptr));
        pushButton->setText(QCoreApplication::translate("MainPage", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
