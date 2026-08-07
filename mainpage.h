#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QTimeEdit>
#include <QMessageBox>
namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void on_btncalculate_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
