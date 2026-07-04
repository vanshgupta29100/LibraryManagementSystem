#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QMainWindow>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr);
    ~ReturnBook();

    void loadIssuedBooks();

private slots:
    void on_returnButton_clicked();
    void on_backButton_clicked();

private:
    Ui::ReturnBook *ui;
};

#endif