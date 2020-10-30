#ifndef MYSPLINE_H
#define MYSPLINE_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QObject>

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>

#include <QSplineSeries>
QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class mySpline : public QObject
{
    Q_OBJECT

 //QVector<StatsItem*> ilist;

    QVector<QSplineSeries *> series;
    QVector<QString*> m_names;
    //QVector<QString> m_names;
    QTimer *m_timer;
    QDateTime m_nextDataTime;
    QValueAxis *m_axis;

    qreal m_step;
    qreal m_x;
    qreal m_y;
    QStringList m_titles;

    QObject* m_object;
     QObject* m_chart;

   QVector<QPointF> m_data1, m_data2;
public:
    explicit mySpline(QObject *parent = nullptr);
    mySpline(QObject* object, QObject *parent);
    virtual ~mySpline();

    void append(QString* Uinput);
    const int sampleSize = 240;

    static const QString m_status[2];

public slots:
    void handleTimeout();
    void updateValues();
    void search(QString);
    void append();

signals:
 void appendCompleted();
};

#endif // MYSPLINE_H
