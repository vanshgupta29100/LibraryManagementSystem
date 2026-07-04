#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>

class QShowEvent;

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

    void loadStatistics();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_addBookButton_clicked();
    void on_viewBooksButton_clicked();
    void on_issueBookButton_clicked();
    void on_returnBookButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H