#ifndef VIEWLOGS_H
#define VIEWLOGS_H

#include <QWidget>

namespace Ui {
class ViewLogs;
}

class ViewLogs : public QWidget
{
    Q_OBJECT

public:
    explicit ViewLogs(QWidget *parent = nullptr);
    ~ViewLogs();

private slots:
    void on_searchButton_clicked();
    void on_allDataButton_clicked();

private:
    Ui::ViewLogs *ui;

    void loadAllLogs();
};

#endif // VIEWLOGS_H