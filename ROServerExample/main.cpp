#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include "simpleswitch.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    SimpleSwitch srcSwitch; // create simple switch

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:switch"))); // create host node without Registry
    srcNode.enableRemoting(&srcSwitch); // enable remoting/sharing

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
