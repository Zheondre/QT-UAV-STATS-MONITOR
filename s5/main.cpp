#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//#include "C:\Source\QT\s5\basestats.h"
#include "C:\Source\QT\s5\src\statsModel.h"
#include "C:\Source\QT\s5\src\FcAir\fcairstats.h"
#include "C:\Source\QT\s5\src\bluetooth\bluetooth.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //registers c++ type as a qml type
   // qmlRegisterType<BaseStats>("basestats",1,0,"BaseStats");
    qmlRegisterType<statsModel>("StatsMdl", 1, 0, "StatsModel");
    qmlRegisterType<FcAirStats>("fcairsts",1,0,"FcAirStats");


    BaseStats favStats;
    FcAirStats fcStats;


    QQmlApplicationEngine engine;
    // registers c++ variable as a qml property
    engine.rootContext()->setContextProperty(QStringLiteral("fcStats"), &fcStats);

   //TODO make a seperate thread for running bluetooth !
    bluetooth d;
    //d.connectClicked();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
