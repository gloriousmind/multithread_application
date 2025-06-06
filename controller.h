#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include "worker.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent);
    ~Controller();
    void startWork();
    void endWork();
    void updateWork();

signals:
    void connect_for_thread();
    void disconnect_for_thread();
    void update_for_thread();

public:
    Worker *cur_worker;
    QThread *workerThread;
};



#endif // CONTROLLER_H
