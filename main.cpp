#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlComponent>

#include <QApplication>
#include <QQmlContext>

#include <math.h>
#include <stdio.h>

#include "myspline.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication  app(argc, argv);

    qmlRegisterType<mySpline>("myspline", 1, 0, "MySpline");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url] (QObject *obj, const QUrl &objUrl)  {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    //engine.load(url);

    QQmlComponent component(&engine, url);

    QObject *object = component.create();


    //QObject* view = engine.findChild<QObject*>("qmlViewChart");
//    mySpline ms(component.create(), nullptr);
    mySpline ms(object, nullptr);

   // engine.rootContext()->setContextProperty("myspline", &ms);

    return app.exec();
}

