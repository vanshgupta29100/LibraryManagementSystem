#include "issuebook.h"
#include "ui_issuebook.h"

#include <QDate>
#include <QSqlQuery>
#include <QMessageBox>

IssueBook::IssueBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IssueBook)
{
    ui->setupUi(this);

    ui->issueDateEdit->setDate(QDate::currentDate());

    loadBooks();
}

IssueBook::~IssueBook()
{
    delete ui;
}

void IssueBook::loadBooks()
{
    ui->bookComboBox->clear();

    QSqlQuery query;

    query.exec(
        "SELECT book_id, book_name "
        "FROM books "
        "WHERE quantity > 0"
        );

    while(query.next())
    {
        ui->bookComboBox->addItem(
            query.value(1).toString(),
            query.value(0).toInt()
            );
    }
}

void IssueBook::on_issueButton_clicked()
{
    QString studentName =
        ui->studentNameLineEdit->text();

    QString rollNo =
        ui->studentRollNoLineEdit->text();

    QString issueDate =
        ui->issueDateEdit->date()
            .toString("yyyy-MM-dd");

    if(studentName.isEmpty() || rollNo.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Fill all fields."
            );

        return;
    }

    int bookId =
        ui->bookComboBox
            ->currentData()
            .toInt();

    QSqlQuery query;

    query.prepare(
        "INSERT INTO issued_books "
        "(book_id, student_name, student_roll_no, issue_date, status) "
        "VALUES (?, ?, ?, ?, 'Issued')"
        );

    query.addBindValue(bookId);
    query.addBindValue(studentName);
    query.addBindValue(rollNo);
    query.addBindValue(issueDate);

    if(query.exec())
    {
        QSqlQuery updateQuery;

        updateQuery.prepare(
            "UPDATE books "
            "SET quantity = quantity - 1 "
            "WHERE book_id=?"
            );

        updateQuery.addBindValue(bookId);
        updateQuery.exec();

        QMessageBox::information(
            this,
            "Success",
            "Book Issued Successfully"
            );

        ui->studentNameLineEdit->clear();
        ui->studentRollNoLineEdit->clear();

        loadBooks();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable To Issue Book"
            );
    }
}

void IssueBook::on_backButton_clicked()
{
    close();
}