#ifndef VIEWBOOKS_H
#define VIEWBOOKS_H

#include <QMainWindow>

namespace Ui {
class ViewBooks;
}

class ViewBooks : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewBooks(QWidget *parent = nullptr);
    ~ViewBooks();

    void loadBooks();

private slots:
    void on_backButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_searchButton_clicked();

    void on_showAllButton_clicked();

private:
    Ui::ViewBooks *ui;
};

#endif // VIEWBOOKS_H