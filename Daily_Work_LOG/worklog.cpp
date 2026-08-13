#include "worklog.h"
#include "ui_worklog.h"

#include <QMessageBox>
#include <QDate>
#include <QAbstractItemView>
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include "viewlogs.h"

Worklog::Worklog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Worklog)
{
    ui->setupUi(this);

    // Current date
    ui->dateEdit->setDate(QDate::currentDate());

    // Configure table
    ui->workLogTable->setColumnCount(7);

    ui->workLogTable->setHorizontalHeaderLabels({
        "Date",
        "Task",
        "Assigned By",
        "Task Type",
        "Hours",
        "Status",
        "Remarks"
    });

    ui->workLogTable->horizontalHeader()->setStretchLastSection(true);

    ui->workLogTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    ui->workLogTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );
}

Worklog::~Worklog()
{
    delete ui;
}


// =====================================================
// ADD TASK BUTTON
// =====================================================

void Worklog::on_addButton_clicked()
{
    // -----------------------------
    // Get data from GUI
    // -----------------------------

    QString date =
        ui->dateEdit->date().toString("dd/MM/yyyy");

    QString task =
        ui->taskEdit->text().trimmed();

    QString assignedBy =
        ui->assignedByCombo_2->currentText();

    QString taskType =
        ui->taskTypeCombo->currentText();

    double hours =
        ui->doubleSpinBox->value();

    QString status =
        ui->statusCombo->currentText();

    // remarksEdit_2 is QPlainTextEdit
    QString remarks =
        ui->remarksEdit_2->toPlainText().trimmed();


    // -----------------------------
    // Validate Task
    // -----------------------------

    if (task.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Invalid Task",
            "Please enter a task."
            );

        ui->taskEdit->setFocus();

        return;
    }


    // -----------------------------
    // Validate Hours
    // -----------------------------

    if (hours <= 0)
    {
        QMessageBox::warning(
            this,
            "Invalid Hours",
            "Hours must be greater than 0."
            );

        ui->doubleSpinBox->setFocus();

        return;
    }


    // -----------------------------
    // SQLite INSERT
    // -----------------------------

    QSqlQuery query;

    query.prepare(
        "INSERT INTO work_logs "
        "(date, task, assigned_by, task_type, hours, status, remarks) "
        "VALUES "
        "(:date, :task, :assigned_by, :task_type, "
        ":hours, :status, :remarks)"
        );

    query.bindValue(":date", date);
    query.bindValue(":task", task);
    query.bindValue(":assigned_by", assignedBy);
    query.bindValue(":task_type", taskType);
    query.bindValue(":hours", hours);
    query.bindValue(":status", status);
    query.bindValue(":remarks", remarks);


    // -----------------------------
    // Execute INSERT
    // -----------------------------

    if (!query.exec())
    {
        QMessageBox::critical(
            this,
            "Database Error",
            query.lastError().text()
            );

        return;
    }


    // -----------------------------
    // Add record to table
    // -----------------------------

    int row =
        ui->workLogTable->rowCount();

    ui->workLogTable->insertRow(row);


    // Date
    ui->workLogTable->setItem(
        row,
        0,
        new QTableWidgetItem(date)
        );


    // Task
    ui->workLogTable->setItem(
        row,
        1,
        new QTableWidgetItem(task)
        );


    // Assigned By
    ui->workLogTable->setItem(
        row,
        2,
        new QTableWidgetItem(assignedBy)
        );


    // Task Type
    ui->workLogTable->setItem(
        row,
        3,
        new QTableWidgetItem(taskType)
        );


    // Hours
    ui->workLogTable->setItem(
        row,
        4,
        new QTableWidgetItem(
            QString::number(hours, 'f', 1)
            )
        );


    // Status
    ui->workLogTable->setItem(
        row,
        5,
        new QTableWidgetItem(status)
        );


    // Remarks
    ui->workLogTable->setItem(
        row,
        6,
        new QTableWidgetItem(remarks)
        );


    // Scroll to latest row
    ui->workLogTable->scrollToBottom();


    // -----------------------------
    // Success message
    // -----------------------------

    QMessageBox::information(
        this,
        "Success",
        "Work log saved successfully."
        );


    // -----------------------------
    // Clear input fields
    // -----------------------------

    ui->taskEdit->clear();

    ui->doubleSpinBox->setValue(0);

    ui->remarksEdit_2->clear();

    ui->assignedByCombo_2->setCurrentIndex(0);

    ui->taskTypeCombo->setCurrentIndex(0);

    ui->statusCombo->setCurrentIndex(0);

    ui->dateEdit->setDate(QDate::currentDate());
}


// =====================================================
// CLEAR BUTTON
// =====================================================

void Worklog::on_clearButton_clicked()
{
    ui->dateEdit->setDate(QDate::currentDate());

    ui->taskEdit->clear();

    ui->doubleSpinBox->setValue(0);

    ui->remarksEdit_2->clear();

    ui->assignedByCombo_2->setCurrentIndex(0);

    ui->taskTypeCombo->setCurrentIndex(0);

    ui->statusCombo->setCurrentIndex(0);
}
void Worklog::on_pushButton_clicked()
{
    this-> hide();
    ViewLogs *viewlogs = new ViewLogs();
    viewlogs->show();
}

