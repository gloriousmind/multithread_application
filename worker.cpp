#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::dowork()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "myconnection");
    db.setHostName("localhost");
    db.setDatabaseName("QT_DATABASE");
    db.setUserName("root");
    db.setPassword("fengsiqi521");
    bool ok = db.open();
    qDebug() << ok;
    if (ok)
    {
        emit connection_status(true);
        query = new QSqlQuery(db);
        query->exec("SELECT * FROM computer_science_courses");
        while (query->next())
        {
            QVariantList data;
            data << query->value(0) << query->value(1);
            emit database_data(data);
        }
    }
    else
        emit connection_status(false);
}

void Worker::endwork()
{
    db.close();
    QSqlDatabase::removeDatabase("myconnection");
    delete query;
}

void Worker::updatework()
{
    QSqlDatabase::database().transaction();
    query->exec("UPDATE computer_science_courses SET NAME = CONCAT('_', name)");
    QSqlDatabase::database().commit();
    query->exec("SELECT * FROM computer_science_courses");
    while (query->next())
    {
        QVariantList data;
        data << query->value(0) << query->value(1);
        emit database_data(data);
    }
}
