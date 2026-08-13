#ifndef WORKLOG_H
#define WORKLOG_H

#include <QWidget>

namespace Ui
{
class Worklog;
}

class Worklog : public QWidget
{
    Q_OBJECT

public:
    explicit Worklog(QWidget *parent = nullptr);
    ~Worklog();

private slots:
    void on_addButton_clicked();
    void on_clearButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Worklog *ui;
};

#endif // WORKLOG_H