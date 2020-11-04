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

    bool running;
#if 0
    vector<int> match;
    vector<int> selected;
    vector<int> added;

#endif

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

    const int sampleSize = 240;

    QString * mySpline::getName(int val);

    static const char* example[2];

public slots:
    void handleTimeout();
    void updateValues();
    void search(QString);
    void append(const QString &t);
    //void append(const char *t);
    void appendItem();
    void menuSelect(int pos);
    void startStop();

signals:
    void appendCompleted();
};

#endif // MYSPLINE_H
