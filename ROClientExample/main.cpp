#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QSharedPointer<SimpleSwitchReplica> ptr; // shared pointer to hold source replica

    QRemoteObjectNode repNode; // create remote object node
    repNode.connectToNode(QUrl(QStringLiteral("local:switch"))); // connect with remote host node

    ptr.reset(repNode.acquire<SimpleSwitchReplica>()); // acquire replica of source from host node

    Client rswitch(ptr); // create client switch object and pass reference of replica to it

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
