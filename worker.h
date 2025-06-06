#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent);

public slots:
    void dowork();
    void endwork();
    void updatework();

signals:
    void connection_status(bool connected);
    void database_data(QVariantList data);

public:
    QSqlDatabase db;
    QSqlQuery *query;
};
#endif // WORKER_H
