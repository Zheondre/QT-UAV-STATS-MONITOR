#ifndef STATSENTRY_H
#define STATSENTRY_H

#include <QObject>

struct StatsEntry {
    enum {
        DecodeCalendar,
        DecodeUptime,
        DecodeNormal,
        DecodeHex
    };

    QString name;
    QString command;
    QString unitDesc;
    size_t nScale;
    QString unit;
    int nDecode;
};



#endif // STATSENTRY_H

