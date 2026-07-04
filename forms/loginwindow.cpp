#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "dashboard.h"

#include <QApplication>
#include <QScreen>

#include <QSqlQuery>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)

{
    ui->setupUi(this);
    setWindowTitle("Library Management System - Login");

    move(
        QApplication::primaryScreen()->availableGeometry().center()
        - rect().center()
        );

    setFixedSize(width(), height());

    this->setStyleSheet(
        "QMainWindow{background-color:#f5f5f5;}"
        "QLabel{font-size:14px;font-weight:bold;color:#333333;}"
        "QLineEdit{"
        "padding:6px;"
        "border:1px solid gray;"
        "border-radius:5px;"
        "font-size:13px;"
        "}"
        "QPushButton{"
        "background-color:#3498db;"
        "color:white;"
        "font-size:14px;"
        "font-weight:bold;"
        "border-radius:6px;"
        "padding:8px;"
        "}"
        "QPushButton:hover{"
        "background-color:#2980b9;"
        "}"
        );

}


LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username =
        ui->usernameLineEdit->text();

    QString password =
        ui->passwordLineEdit->text();

    QSqlQuery query;

    query.prepare(
        "SELECT * FROM users "
        "WHERE username=? AND password=?"
        );

    query.addBindValue(username);
    query.addBindValue(password);

    if(query.exec() && query.next())
    {
        QMessageBox::information(
            this,
            "Success",
            "Login Successful"
            );

        Dashboard *dashboard =
            new Dashboard();

        dashboard->show();

        this->close();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Login Failed",
            "Invalid Username or Password"
            );
    }
}