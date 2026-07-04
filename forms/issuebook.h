#ifndef ISSUEBOOK_H
#define ISSUEBOOK_H

#include <QMainWindow>

namespace Ui {
class IssueBook;
}

class IssueBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit IssueBook(QWidget *parent = nullptr);
    ~IssueBook();

    void loadBooks();

private slots:
    void on_issueButton_clicked();
    void on_backButton_clicked();

private:
    Ui::IssueBook *ui;
};

#endif // ISSUEBOOK_H