#include "forms/loginwindow.h"
#include "database/databasemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseManager::connectDatabase();

    LoginWindow w;
    w.show();

    return a.exec();
}