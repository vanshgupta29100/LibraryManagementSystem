#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool DatabaseManager::connectDatabase()
{
    QSqlDatabase db =
        QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("library.db");

    if(db.open())
    {
        qDebug() << "Database Connected";

        QSqlQuery query;

        query.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "username TEXT,"
            "password TEXT,"
            "role TEXT)"
            );
        query.exec(
            "CREATE TABLE IF NOT EXISTS books ("
            "book_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "book_name TEXT NOT NULL,"
            "author TEXT NOT NULL,"
            "publisher TEXT NOT NULL,"
            "isbn TEXT UNIQUE,"
            "quantity INTEGER NOT NULL)"
            );

        query.exec(
            "CREATE TABLE IF NOT EXISTS issued_books ("
            "issue_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "book_id INTEGER,"
            "student_name TEXT NOT NULL,"
            "student_roll_no TEXT NOT NULL,"
            "issue_date TEXT NOT NULL,"
            "return_date TEXT,"
            "status TEXT NOT NULL)"
            );

        query.exec(
            "INSERT OR IGNORE INTO users "
            "(user_id,username,password,role) "
            "VALUES "
            "(1,'admin','admin123','admin')"
            );

        return true;
    }

    qDebug() << db.lastError().text();

    return false;
}