#ifndef DRIVER_H
#define DRIVER_H

#include <QThread>
#include <QObject>
#include "basestats.h"
#include "C:\Source\QT\QTGITREPO\s5\src\bluetooth\bluetooth.h"
#include <QTimer>
//#include "btworker.h"


class driver : public QObject
{
    Q_OBJECT
    QThread *btThread;
    QTimer *timer;
    bluetooth *b;
  //  btWorker *worker;

    QString mes; //make this a vector of mes ?
public:
    explicit driver(QObject *parent = nullptr);
    explicit driver(bluetooth *);

    void addStats(FcAirStats *);

    ~driver();

public slots:
   void inbox(const QString &mes);

signals:
    void copyMesToBT(const QString &);
    void run();
    void newMessage();
};

#endif // DRIVER_H
