#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPage;
}
QT_END_NAMESPACE

class Worklog;

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage() override;

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Login_clicked();

private:
    Ui::LoginPage *ui;
    Worklog *worklog;
};
#endif // LOGINPAGE_H
