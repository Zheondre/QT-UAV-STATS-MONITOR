#include "driver.h"


void driver::inbox(const QString &mes){

    // mutex ?
    this->mes = mes;
    //mutex //
     emit newMessage(); // send this out to mavlink
}

driver::driver(bluetooth *b) : QObject(nullptr)
{
    this->b = b;
    btThread = new QThread();
    b->moveToThread(btThread);

    //worker = new btWorker(b);
    //worker->moveToThread(&btThread);

    connect(btThread, &QThread::finished, b, &QObject::deleteLater);
    connect(b, &bluetooth::sleep, btThread, &QThread::sleep);
    connect(this, &driver::run, b, &bluetooth::run);

    //connect(this, &driver::copyMesToBT, worker, &btWorker::copyMes); //double check
    //need to connect driver fto incoming messages from phone.
    connect(this->b, &bluetooth::inbox, this, &driver::inbox);

    btThread->start();
}

driver::driver(QObject *parent) : QObject(parent)
{
}

driver::~driver() {
    btThread->quit();
    btThread->wait();
}

void driver::addStats( FcAirStats *s){
    worker->addStats(s);
}
