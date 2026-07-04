#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QMainWindow>

namespace Ui {
class EditBook;
}

class EditBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditBook(QWidget *parent = nullptr);
    ~EditBook();

    void setBookData(
        int id,
        QString bookName,
        QString author,
        QString publisher,
        QString isbn,
        int quantity
        );

private slots:
    void on_updateButton_clicked();
    void on_backButton_clicked();

private:
    Ui::EditBook *ui;

    int bookId;
};

#endif