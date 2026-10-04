#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_exit_clicked();

    void on_checkBox_Motor_checkStateChanged(const Qt::CheckState &arg1);

    void on_checkBox_LED_checkStateChanged(const Qt::CheckState &arg1);

    void on_checkBox_Buzzer_checkStateChanged(const Qt::CheckState &arg1);

    void on_checkBox_auto_checkStateChanged(const Qt::CheckState &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_start_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_stop_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
