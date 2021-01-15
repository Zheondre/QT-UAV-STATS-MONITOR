#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "basestats.h"
#include "C:\Source\QT\QTGITREPO\s5\src\statsModel.h"
#include "C:\Source\QT\QTGITREPO\s5\src\favstatsmodel.h"
#include "C:\Source\QT\QTGITREPO\s5\src\FcAir\fcairstats.h"
#include "C:\Source\QT\QTGITREPO\s5\src\bluetooth\bluetooth.h"
#include "C:\Source\QT\QTGITREPO\s5\driver.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //registers c++ type as a qml type
   // qmlRegisterType<BaseStats>("basestats",1,0,"BaseStats");
    qmlRegisterType<statsModel>("StatsMdl", 1, 0, "StatsModel");
    qmlRegisterType<favStatsModel>("favStatsMdl", 1, 0, "FavStatsModel");
    qmlRegisterType<FcAirStats>("fcairsts",1,0,"FcAirStats");

    FcAirStats fcStats;

    QQmlApplicationEngine engine;
    // registers c++ variable as a qml property
    engine.rootContext()->setContextProperty(QStringLiteral("fcStats"), &fcStats);

   //TODO make a seperate thread for running bluetooth !
    bluetooth d;
    //d.addStats(&fcStats);
   // driver tsk(&d);
#ifdef Q_OS_WIN || Q_OS_LINUX

    //driver tsk(&d);
    //tsk.addStats(&fcStats);
    //tsk.run();

#else //mobile
   // QObject::connect(&d, &bluetooth::sendForceCommand, &fcStats, &FcAirStats::sendForceCommand);
     //QObject::connect(&fcStats, &FcAirStats::sendForceCommand, &d, &bluetooth::sendForceCommand);
    //QObject::connect(&d, SIGNAL(&bluetooth::inbox(const QString &result)), &fcStats, SLOT(&FcAirStats::deserialize(const QString &result)));

//tsk.run(); //thread works for android cant find bt devices
#endif

    QObject::connect(&fcStats, &FcAirStats::btrun, &d, &bluetooth::run);

   // tsk.run(); //freezes ui for windows 01-10-21
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
  engine.load(url);

  QObject* home = engine.rootObjects().first()->findChild<QObject*>("homePage");

   QObject::connect(home, SIGNAL(buttonBtSignal()), &d, SLOT(run()));
  /*
  QObject::connect(engine.findChild<QObject*>("btButton"),
           SIGNAL(clicked()),
                  &d, SLOT(run));
                  */
   // #ifdef Q_OS_ANDROID
      //  d.run(); //bt device scanner stopped working
   // #endif
     app.exec();

    return 0;
}
