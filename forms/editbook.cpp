#include "editbook.h"
#include "ui_editbook.h"

#include <QSqlQuery>
#include <QMessageBox>

EditBook::EditBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditBook)
{
    ui->setupUi(this);
}

EditBook::~EditBook()
{
    delete ui;
}

void EditBook::setBookData(
    int id,
    QString bookName,
    QString author,
    QString publisher,
    QString isbn,
    int quantity
    )
{
    bookId = id;

    ui->bookNameLineEdit->setText(bookName);
    ui->authorLineEdit->setText(author);
    ui->publisherLineEdit->setText(publisher);
    ui->isbnLineEdit->setText(isbn);
    ui->quantitySpinBox->setValue(quantity);
}

void EditBook::on_updateButton_clicked()
{
    QSqlQuery query;

    query.prepare(
        "UPDATE books SET "
        "book_name=?, "
        "author=?, "
        "publisher=?, "
        "isbn=?, "
        "quantity=? "
        "WHERE book_id=?"
        );

    query.addBindValue(ui->bookNameLineEdit->text());
    query.addBindValue(ui->authorLineEdit->text());
    query.addBindValue(ui->publisherLineEdit->text());
    query.addBindValue(ui->isbnLineEdit->text());
    query.addBindValue(ui->quantitySpinBox->value());
    query.addBindValue(bookId);

    if(query.exec())
    {
        QMessageBox::information(
            this,
            "Success",
            "Book Updated Successfully"
            );

        if(parentWidget())
        {
            parentWidget()->close();
        }

        close();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable To Update Book"
            );
    }
}

void EditBook::on_backButton_clicked()
{
    close();
}