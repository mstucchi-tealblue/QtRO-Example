#include "client.h"

// constructor
Client::Client(QSharedPointer<SimpleSwitchReplica> ptr) :
    QObject(nullptr),reptr(ptr)
{
    initConnections();
}

//destructor
Client::~Client()
{
}

void Client::initConnections()
{
        // initialize connections between signals and slots
       // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
        QObject::connect(reptr.data(), &SimpleSwitchReplica::geometryChanged, [&](){
            setLocalGeometry_slot(reptr.data()->geometry());
            });
}

void Client::setLocalGeometry_slot(QRect windowGeometry)
{
    qDebug() << "Geometria arrivata";
    setInternalProcessWindow(windowGeometry);
    setInternalProcessWindowHeight(getInternalProcessWindow().height()-50);
    setInternalProcessWindowWidth(getInternalProcessWindow().width());
    setInternalProcessWindowX(getInternalProcessWindow().x());
    setInternalProcessWindowY(getInternalProcessWindow().y()+50);
}

int Client::getInternalProcessWindowY() const
{
    return internalProcessWindowY;
}

void Client::setInternalProcessWindowY(int value)
{
    internalProcessWindowY = value;
     Q_EMIT internalProcessWindowYChanged();
}

int Client::getInternalProcessWindowX() const
{
    return internalProcessWindowX;
}

void Client::setInternalProcessWindowX(int value)
{
    internalProcessWindowX = value;
     Q_EMIT internalProcessWindowXChanged();
}

int Client::getInternalProcessWindowWidth() const
{
    return internalProcessWindowWidth;
}

void Client::setInternalProcessWindowWidth(int value)
{
    internalProcessWindowWidth = value;
     Q_EMIT internalProcessWindowWidthChanged();
}

int Client::getInternalProcessWindowHeight() const
{
    return internalProcessWindowHeight;
}

void Client::setInternalProcessWindowHeight(int value)
{
    internalProcessWindowHeight = value;
    Q_EMIT internalProcessWindowHeightChanged();
}

QRect Client::getInternalProcessWindow() const
{
    return internalProcessWindow;
}

void Client::setInternalProcessWindow(const QRect &value)
{
    internalProcessWindow = value;
}
