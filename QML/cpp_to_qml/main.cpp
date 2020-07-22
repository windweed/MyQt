#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "colormaker.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ColorMaker>("ColorMaker", 1, 0, "ColorMaker");

    QQmlApplicationEngine engine;

    //engine.rootContext()->setContextProperty("colorMaker", new ColorMaker);
    //rootContext()返回QQmlContext对象

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
