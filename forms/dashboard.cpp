#include "dashboard.h"
#include "ui_dashboard.h"

#include "addbook.h"
#include "viewbooks.h"
#include "issuebook.h"
#include "returnbook.h"
#include "loginwindow.h"

#include <QSqlQuery>
#include <QShowEvent>

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    setWindowTitle("Library Management System - Dashboard");

    setFixedSize(width(), height());

    this->setStyleSheet(
        "QMainWindow{background-color:#f5f5f5;}"
        "QLabel{font-size:14px;font-weight:bold;color:#333333;}"
        "QPushButton{"
        "background-color:#3498db;"
        "color:white;"
        "font-size:14px;"
        "font-weight:bold;"
        "border-radius:6px;"
        "padding:8px;"
        "min-width:140px;"
        "min-height:35px;"
        "}"
        "QPushButton:hover{"
        "background-color:#2980b9;"
        "}"
        );

    loadStatistics();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    loadStatistics();
}

void Dashboard::loadStatistics()
{
    QSqlQuery query;

    query.exec("SELECT COUNT(*) FROM books");

    if(query.next())
        ui->totalBooksLabel->setText(query.value(0).toString());

    query.exec("SELECT IFNULL(SUM(quantity),0) FROM books");

    if(query.next())
        ui->availableBooksLabel->setText(query.value(0).toString());

    query.exec(
        "SELECT COUNT(*) "
        "FROM issued_books "
        "WHERE status='Issued'"
        );

    if(query.next())
        ui->issuedBooksLabel->setText(query.value(0).toString());
}

void Dashboard::on_addBookButton_clicked()
{
    AddBook *window = new AddBook(this);
    window->show();
}

void Dashboard::on_viewBooksButton_clicked()
{
    ViewBooks *window = new ViewBooks(this);
    window->show();
}

void Dashboard::on_issueBookButton_clicked()
{
    IssueBook *window = new IssueBook(this);
    window->show();
}

void Dashboard::on_returnBookButton_clicked()
{
    ReturnBook *window = new ReturnBook(this);
    window->show();
}

void Dashboard::on_logoutButton_clicked()
{
    LoginWindow *login = new LoginWindow();

    login->show();

    close();
}