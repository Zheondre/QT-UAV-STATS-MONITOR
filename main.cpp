#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlComponent>

#include <QApplication>
//#include <QButtonGroup>
//#include <QIcon>
//#include <QPushButton>
//#include <QComboBox>
//#include <QDateTime>

//#include <QDialog>
//#include <QTimer>
#//include <QLabel>

//#include "realtimedemo.h"
//#include "chartdir.h"
#include <math.h>
#include <stdio.h>

#include "myspline.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication  app(argc, argv);

    qmlRegisterType<mySpline>("myspline", 1, 0, "myspline");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

   // QQmlEngine engine;
     QQmlComponent component(&engine, "qml/untitled/main.qml");
     //QObject *object = component.create();


    //QObject* view = engine.findChild<QObject*>("qmlViewChart");
    mySpline ms(component.create(), nullptr);

    //view->rootContext()->setContextProperty("myspline", &ms);
    //engine.rootObjects().at(0)->findChild

    return app.exec();
}

