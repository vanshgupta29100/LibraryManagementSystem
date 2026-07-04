#include "returnbook.h"
#include "ui_returnbook.h"

#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QMessageBox>

ReturnBook::ReturnBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReturnBook)
{
    ui->setupUi(this);

    loadIssuedBooks();
}

ReturnBook::~ReturnBook()
{
    delete ui;
}

void ReturnBook::loadIssuedBooks()
{
    ui->issuedBooksTableWidget->setRowCount(0);

    QSqlQuery query;

    query.exec(
        "SELECT issue_id, book_id, student_name, "
        "student_roll_no, issue_date, status "
        "FROM issued_books "
        "WHERE status='Issued'"
        );

    int row = 0;

    while(query.next())
    {
        ui->issuedBooksTableWidget->insertRow(row);

        for(int col = 0; col < 6; col++)
        {
            ui->issuedBooksTableWidget->setItem(
                row,
                col,
                new QTableWidgetItem(query.value(col).toString())
                );
        }

        row++;
    }

    ui->issuedBooksTableWidget->resizeColumnsToContents();
}

void ReturnBook::on_returnButton_clicked()
{
    int currentRow = ui->issuedBooksTableWidget->currentRow();

    if(currentRow < 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please select a book."
            );
        return;
    }

    int issueId =
        ui->issuedBooksTableWidget
            ->item(currentRow,0)
            ->text()
            .toInt();

    int bookId =
        ui->issuedBooksTableWidget
            ->item(currentRow,1)
            ->text()
            .toInt();

    QSqlQuery query;

    query.prepare(
        "UPDATE issued_books "
        "SET status='Returned', "
        "return_date=date('now') "
        "WHERE issue_id=?"
        );

    query.addBindValue(issueId);

    if(query.exec())
    {
        QSqlQuery updateBook;

        updateBook.prepare(
            "UPDATE books "
            "SET quantity = quantity + 1 "
            "WHERE book_id=?"
            );

        updateBook.addBindValue(bookId);
        updateBook.exec();

        QMessageBox::information(
            this,
            "Success",
            "Book Returned Successfully."
            );

        loadIssuedBooks();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable to return book."
            );
    }
}

void ReturnBook::on_backButton_clicked()
{
    close();
}