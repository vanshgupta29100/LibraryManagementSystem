#include "viewbooks.h"
#include "ui_viewbooks.h"
#include "editbook.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QTableWidgetItem>

ViewBooks::ViewBooks(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewBooks)
{
    ui->setupUi(this);

    ui->booksTableWidget->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    ui->booksTableWidget->setSelectionMode(
        QAbstractItemView::SingleSelection
        );

    ui->booksTableWidget->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    ui->booksTableWidget->horizontalHeader()
        ->setStretchLastSection(true);

    loadBooks();
}

ViewBooks::~ViewBooks()
{
    delete ui;
}

void ViewBooks::loadBooks()
{
    ui->booksTableWidget->setRowCount(0);

    QSqlQuery query;

    query.exec(
        "SELECT * FROM books"
        );

    int row = 0;

    while(query.next())
    {
        ui->booksTableWidget->insertRow(row);

        ui->booksTableWidget->setItem(
            row,
            0,
            new QTableWidgetItem(query.value(0).toString())
            );

        ui->booksTableWidget->setItem(
            row,
            1,
            new QTableWidgetItem(query.value(1).toString())
            );

        ui->booksTableWidget->setItem(
            row,
            2,
            new QTableWidgetItem(query.value(2).toString())
            );

        ui->booksTableWidget->setItem(
            row,
            3,
            new QTableWidgetItem(query.value(3).toString())
            );

        ui->booksTableWidget->setItem(
            row,
            4,
            new QTableWidgetItem(query.value(4).toString())
            );

        ui->booksTableWidget->setItem(
            row,
            5,
            new QTableWidgetItem(query.value(5).toString())
            );

        row++;
    }

    ui->booksTableWidget->resizeColumnsToContents();
}

void ViewBooks::on_backButton_clicked()
{
    close();
}

void ViewBooks::on_editButton_clicked()
{
    int currentRow =
        ui->booksTableWidget->currentRow();

    if(currentRow < 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please Select A Book"
            );

        return;
    }

    EditBook *editBook = new EditBook(this);

    editBook->setBookData(
        ui->booksTableWidget->item(currentRow,0)->text().toInt(),
        ui->booksTableWidget->item(currentRow,1)->text(),
        ui->booksTableWidget->item(currentRow,2)->text(),
        ui->booksTableWidget->item(currentRow,3)->text(),
        ui->booksTableWidget->item(currentRow,4)->text(),
        ui->booksTableWidget->item(currentRow,5)->text().toInt()
        );

    editBook->show();
}

void ViewBooks::on_deleteButton_clicked()
{
    int currentRow =
        ui->booksTableWidget->currentRow();

    if(currentRow < 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please Select A Book"
            );

        return;
    }

    int bookId =
        ui->booksTableWidget
            ->item(currentRow,0)
            ->text()
            .toInt();

    if(QMessageBox::question(
            this,
            "Delete Book",
            "Are you sure you want to delete this book?"
            ) != QMessageBox::Yes)
    {
        return;
    }

    QSqlQuery query;

    query.prepare(
        "DELETE FROM books "
        "WHERE book_id=?"
        );

    query.addBindValue(bookId);

    if(query.exec())
    {
        QMessageBox::information(
            this,
            "Success",
            "Book Deleted Successfully"
            );

        loadBooks();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable To Delete Book"
            );
    }
}

void ViewBooks::on_searchButton_clicked()
{
    QString keyword = ui->searchLineEdit->text().trimmed();

    ui->booksTableWidget->setRowCount(0);

    QSqlQuery query;

    query.prepare(
        "SELECT * FROM books "
        "WHERE book_name LIKE ? "
        "OR author LIKE ? "
        "OR isbn LIKE ?"
        );

    QString searchText = "%" + keyword + "%";

    query.addBindValue(searchText);
    query.addBindValue(searchText);
    query.addBindValue(searchText);

    if(!query.exec())
    {
        QMessageBox::warning(
            this,
            "SQL Error",
            query.lastError().text()
            );
        return;
    }

    int row = 0;

    while(query.next())
    {
        ui->booksTableWidget->insertRow(row);

        for(int col = 0; col < 6; col++)
        {
            ui->booksTableWidget->setItem(
                row,
                col,
                new QTableWidgetItem(query.value(col).toString())
                );
        }

        row++;
    }

    QMessageBox::information(
        this,
        "Debug",
        "Rows Found = " + QString::number(row)
        );
}

void ViewBooks::on_showAllButton_clicked()
{
    ui->searchLineEdit->clear();

    loadBooks();
}