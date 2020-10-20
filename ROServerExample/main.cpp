#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QQuickWindow>
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

    auto topLevelObject = engine.rootObjects().value(0);
        auto window = qobject_cast<QQuickWindow *>(topLevelObject);
        window->show();

        QObject::connect(window, &QQuickWindow::heightChanged, [&](){
        srcSwitch.setGeometry(window->geometry());
        });

        QObject::connect(window, &QQuickWindow::widthChanged, [&](){
        srcSwitch.setGeometry(window->geometry());
        });

        QObject::connect(window, &QQuickWindow::xChanged, [&](){
        srcSwitch.setGeometry(window->geometry());
        });

        QObject::connect(window, &QQuickWindow::yChanged, [&](){
        srcSwitch.setGeometry(window->geometry());
        });

    return app.exec();
}
