#include "controller.h"

Controller::Controller(QObject *parent) : QObject{parent}
{
    workerThread = new QThread(nullptr);
    cur_worker = new Worker(nullptr);
    cur_worker->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, cur_worker, &QObject::deleteLater);
    connect(this, &Controller::connect_for_thread, cur_worker, &Worker::dowork);
    connect(this, &Controller::disconnect_for_thread, cur_worker, &Worker::endwork);
    connect(this, &Controller::update_for_thread, cur_worker, &Worker::updatework);
    workerThread->start();
}

void Controller::startWork()
{
    emit connect_for_thread();
}

void Controller::endWork()
{
    emit disconnect_for_thread();
}

void Controller::updateWork()
{
    emit update_for_thread();
}

Controller::~Controller()
{
    workerThread->quit();
    workerThread->wait();
}
