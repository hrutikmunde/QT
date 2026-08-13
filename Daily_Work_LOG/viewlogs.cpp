#include "viewlogs.h"
#include "ui_viewlogs.h"

#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QHeaderView>

ViewLogs::ViewLogs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewLogs)
{
    ui->setupUi(this);

    ui->fromDateEdit->setDate(QDate::currentDate());
    ui->fromDateEdit_2->setDate(QDate::currentDate());

    ui->logTable->setColumnCount(7);

    ui->logTable->setHorizontalHeaderLabels({
        "Date",
        "Task",
        "Assigned By",
        "Task Type",
        "Hours",
        "Status",
        "Remarks"
    });

    ui->logTable->horizontalHeader()
        ->setStretchLastSection(true);

    loadAllLogs();
}

ViewLogs::~ViewLogs()
{
    delete ui;
}


void ViewLogs::loadAllLogs()
{
    QSqlQuery query;

    query.prepare(
        "SELECT date, task, assigned_by, task_type, "
        "hours, status, remarks "
        "FROM work_logs "
        "ORDER BY rowid DESC"
        );

    if (!query.exec())
    {
        QMessageBox::critical(
            this,
            "Database Error",
            query.lastError().text()
            );

        return;
    }

    ui->logTable->setRowCount(0);

    while (query.next())
    {
        int row = ui->logTable->rowCount();

        ui->logTable->insertRow(row);

        ui->logTable->setItem(
            row,
            0,
            new QTableWidgetItem(
                query.value("date").toString()
                )
            );

        ui->logTable->setItem(
            row,
            1,
            new QTableWidgetItem(
                query.value("task").toString()
                )
            );

        ui->logTable->setItem(
            row,
            2,
            new QTableWidgetItem(
                query.value("assigned_by").toString()
                )
            );

        ui->logTable->setItem(
            row,
            3,
            new QTableWidgetItem(
                query.value("task_type").toString()
                )
            );

        ui->logTable->setItem(
            row,
            4,
            new QTableWidgetItem(
                QString::number(
                    query.value("hours").toDouble(),
                    'f',
                    1
                    )
                )
            );

        ui->logTable->setItem(
            row,
            5,
            new QTableWidgetItem(
                query.value("status").toString()
                )
            );

        ui->logTable->setItem(
            row,
            6,
            new QTableWidgetItem(
                query.value("remarks").toString()
                )
            );
    }
}

void ViewLogs::on_searchButton_clicked()
{
    QString fromDate =
        ui->fromDateEdit->date().toString("dd/MM/yyyy");

    QString toDate =
        ui->fromDateEdit_2->date().toString("dd/MM/yyyy");

    QSqlQuery query;

    query.prepare(
        "SELECT date, task, assigned_by, task_type, "
        "hours, status, remarks "
        "FROM work_logs "
        "WHERE date BETWEEN :fromDate AND :toDate "
        "ORDER BY rowid DESC"
        );

    query.bindValue(":fromDate", fromDate);
    query.bindValue(":toDate", toDate);

    if (!query.exec())
    {
        QMessageBox::critical(
            this,
            "Database Error",
            query.lastError().text()
            );

        return;
    }

    ui->logTable->setRowCount(0);

    while (query.next())
    {
        int row = ui->logTable->rowCount();

        ui->logTable->insertRow(row);

        ui->logTable->setItem(
            row, 0,
            new QTableWidgetItem(
                query.value(0).toString()
                )
            );

        ui->logTable->setItem(
            row, 1,
            new QTableWidgetItem(
                query.value(1).toString()
                )
            );

        ui->logTable->setItem(
            row, 2,
            new QTableWidgetItem(
                query.value(2).toString()
                )
            );

        ui->logTable->setItem(
            row, 3,
            new QTableWidgetItem(
                query.value(3).toString()
                )
            );

        ui->logTable->setItem(
            row, 4,
            new QTableWidgetItem(
                QString::number(
                    query.value(4).toDouble(),
                    'f',
                    1
                    )
                )
            );

        ui->logTable->setItem(
            row, 5,
            new QTableWidgetItem(
                query.value(5).toString()
                )
            );

        ui->logTable->setItem(
            row, 6,
            new QTableWidgetItem(
                query.value(6).toString()
                )
            );
    }
}

void ViewLogs::on_allDataButton_clicked()
{
    loadAllLogs();
}