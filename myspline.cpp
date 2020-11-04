#include <QDateTime>
#include <QtCharts>
#include "myspline.h"

const char *mySpline::example[2] = {
"test_A",
"Test_B"
};

static int testCounter = 0;
mySpline::mySpline(QObject *parent): QObject(parent) {}

mySpline::mySpline(QObject* object, QObject *parent): QObject(parent), running(false)
{
    /*
    m_axis(new QValueAxis),
    m_step(0),
    m_x(5),
    m_y(1)*/
// test ///
  series.resize(2);
//TEST ////
    m_timer = new QTimer();
    m_object = object;

    // grabs the chart qml object
    m_chart = m_object->findChild<QObject*>("qmlViewChart");

    //maybe change this to only update as new radio data comes in
    connect(m_timer, &QTimer::timeout, this, &mySpline::updateValues);
    connect(m_object, SIGNAL(srchEditSignal(QString)), this, SLOT(search(const QString &)));
    connect(m_object->findChild<QObject*>("addfcItem"), SIGNAL(addButtonClicked()),
            this, SLOT(appendItem()));
    connect(m_object->findChild<QObject*>("startStop"), SIGNAL(startStop()),
                this, SLOT(startStop()));

   m_timer->start(100);
   m_timer->stop();
}

mySpline::~mySpline(){}

void mySpline::startStop(){

    if(running){
        running = false;
        //m_object->findChild<QObject*>("startStop")->setProperty("text", "Stop");
        m_timer->stop();
    }else {
        running = true;
        //m_object->findChild<QObject*>("startStop")->setProperty("text", "Start"); // got an index of out of range error
        m_timer->start();
    }
}

void mySpline::menuSelect(int pos){
    // add index of selected item
    /*
     if(!selected.find(match.at(pos))
        selected.push_back(match.at(pos));
     */
}

void mySpline::search(const QString &Uinput){
    // pull up list of all matching statsitem

    //TODO go through all lists allocated in app
    //Fcairstats *fairInst
    /*
    //go through all names in fairInst->n_names[i]
    //if there is a partial match place in the ballard item in the plot selection list
    //highlight items that are clicked on

    for(auto it: airInst->n_names){
         if(it.contains(uinput))
            if(!match.contains(it))
                match.push_back(i);
         i++;
         //TODO to push dataType and position
     }
     */
}

void mySpline::appendItem(){

    //found the stats item we want, append the item or name for testing
    if(testCounter < 2 ){

        //emit appendCompleted();
        QMetaObject::invokeMethod(m_chart, "addSeries",
          //Q_ARG(QString, m_status[testCounter])
          Q_ARG(QString, QString(example[testCounter]))
          );
        testCounter++;
    }

    /*
    for(auto i :selected){
        if(!added.contains(i)){
            added.push_back(i*);
             QMetaObject::invokeMethod(m_chart, "addSeries",
                  Q_ARG(QString, QString(i->name))
               );
            }
    }

    //resize series vector
    selected.erase();
    added.erase();
    match.erase();
    //clear search text
    updateUi();
    */
}

/*
 popSeries()
 */
void mySpline::updateValues(){

    if(m_chart){
        //Generate the data
        m_data1.append(QPointF(QDateTime::currentMSecsSinceEpoch(),  QRandomGenerator::global()->generate() % 100));
        m_data2.append(QPointF(QDateTime::currentMSecsSinceEpoch(),  QRandomGenerator::global()->generate() % 100));

        QAbstractAxis *xAxis;
        //Fetch the series and x-axis from QML
        QMetaObject::invokeMethod(m_chart, "axisX", Qt::AutoConnection, Q_RETURN_ARG(QAbstractAxis*, xAxis));
        int i = 0;
        for (QSplineSeries *it : series){
            //looks for the names of each spline and update data
            //QMetaObject::invokeMethod(m_chart,(char*)m_names.at(i), Qt::AutoConnection, Q_RETURN_ARG(QSplineSeries*, it), Q_ARG(int, i));
            QMetaObject::invokeMethod(m_chart,example[i], Qt::AutoConnection, Q_RETURN_ARG(QSplineSeries*, it), Q_ARG(int, i));
            i++;
        }
        //Cast the series and axis to proper form
        //QXYSeries* xyseries1 = static_cast<QXYSeries *>(series1);
        //QXYSeries* xyseries2 = static_cast<QXYSeries *>(series2);
        QDateTimeAxis* dateTimeAxis = static_cast<QDateTimeAxis *>(xAxis);

        //int i = 0;
        //for (QSplineSeries *it : series){
        //it->replace(data.at(0));
        //i++;
        // }
        //test
        series.at(0)->replace(m_data1); //crashes
        series.at(1)->replace(m_data2);

        //set the new values to series and axises
        dateTimeAxis->setMax(QDateTime::fromMSecsSinceEpoch(m_data1.last().x()));
        dateTimeAxis->setMin(QDateTime::fromMSecsSinceEpoch(m_data1.first().x()));

    }
}
void mySpline::handleTimeout()
{
    /*
    qreal x = plotArea().width() / m_axis->tickCount();
    qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
    m_x += y;
    m_y = qrand() % 5 - 2.5;
    m_series->append(m_x, m_y);
    scroll(x, 0);
    if (m_x == 100)
        m_timer.stop();
        */
}

//QDateTime m_nextDataTime;
#if 0
void getData(){ //TODO place data series in a vector

    // The current time
    QDateTime now = QDateTime::currentDateTime();

    // This is our formula for the random number generator
    do
    {
        // We need the currentTime in millisecond resolution
        //double currentTime = Chart::chartTime2(m_nextDataTime.toTime_t())
        //                   + m_nextDataTime.time().msec() / 1000.0;
        double currentTime = 1;
        // Get a data sample
        //double p = currentTime * 4;
        double p = 1;
        double dataA = 20 + cos(p * 129241) * 10 + 1 / (cos(p) * cos(p) + 0.01);
        double dataB = 150 + 100 * sin(p / 27.7) * sin(p / 10.1);
        double dataC = 150 + 100 * cos(p / 6.7) * cos(p / 11.9);

        // Shift the values into the arrays
        for(auto it : series)
            ;//    shiftData(it, sampleSize, dataA);
        /*
        shiftData(m_dataSeriesA, sampleSize, dataA);
        shiftData(m_dataSeriesB, sampleSize, dataB);
        shiftData(m_dataSeriesC, sampleSize, dataC);
        shiftData(m_timeStamps, sampleSize, currentTime);


        m_nextDataTime = m_nextDataTime.addMSecs(DataInterval);
        */
    }
    while (m_nextDataTime < now);

    //
    // We provide some visual feedback to the latest numbers generated, so you can see the
    // data being generated.
    //
    //m_ValueA->setText(QString::number(m_dataSeriesA[sampleSize - 1], 'f', 2));
    //m_ValueB->setText(QString::number(m_dataSeriesB[sampleSize - 1], 'f', 2));
    //m_ValueC->setText(QString::number(m_dataSeriesC[sampleSize - 1], 'f', 2));

}
*/

#endif
