#include "addbook.h"
#include "ui_addbook.h"

#include <QSqlQuery>
#include <QMessageBox>

AddBook::AddBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}

void AddBook::on_saveButton_clicked()
{
    QString bookName = ui->bookNameLineEdit->text();
    QString author = ui->authorLineEdit->text();
    QString publisher = ui->publisherLineEdit->text();
    QString isbn = ui->isbnLineEdit->text();
    int quantity = ui->quantitySpinBox->value();

    if(bookName.isEmpty() ||
        author.isEmpty() ||
        publisher.isEmpty() ||
        isbn.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please fill all fields."
            );
        return;
    }

    QSqlQuery query;

    query.prepare(
        "INSERT INTO books "
        "(book_name, author, publisher, isbn, quantity) "
        "VALUES (?, ?, ?, ?, ?)"
        );

    query.addBindValue(bookName);
    query.addBindValue(author);
    query.addBindValue(publisher);
    query.addBindValue(isbn);
    query.addBindValue(quantity);

    if(query.exec())
    {
        QMessageBox::information(
            this,
            "Success",
            "Book Added Successfully."
            );

        ui->bookNameLineEdit->clear();
        ui->authorLineEdit->clear();
        ui->publisherLineEdit->clear();
        ui->isbnLineEdit->clear();
        ui->quantitySpinBox->setValue(0);
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable to add book.\nISBN may already exist."
            );
    }
}

void AddBook::on_backButton_clicked()
{
    close();
}