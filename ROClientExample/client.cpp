#include "client.h"

// constructor
Client::Client(QSharedPointer<SimpleSwitchReplica> ptr) :
    QObject(nullptr),reptr(ptr)
{
    initConnections();
    //We can connect to SimpleSwitchReplica Signals/Slots
    //directly because our Replica was generated by repc.
}

//destructor
Client::~Client()
{
}

void Client::initConnections()
{
        // initialize connections between signals and slots
       // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
        QObject::connect(reptr.data(), &SimpleSwitchReplica::currStateChanged, this, &Client::recSwitchState_slot);

        QObject::connect(reptr.data(), &SimpleSwitchReplica::geometryChanged, [&](){
            setLocalGeometry_slot(reptr.data()->geometry());
            });

       // connect client's echoSwitchState(..) signal with replica's server_slot(..) to echo back received state
        QObject::connect(this, SIGNAL(echoSwitchState(bool)),reptr.data(), SLOT(server_slot(bool)));
}

void Client::recSwitchState_slot()
{
    qDebug() << "Received source state "<<reptr.data()->currState();
    clientSwitchState = reptr.data()->currState();

    setInternalProcessWindowHeight(getInternalProcessWindow().height());
    setInternalProcessWindowWidth(getInternalProcessWindow().width());
    setInternalProcessWindowX(getInternalProcessWindow().x());
    setInternalProcessWindowY(getInternalProcessWindow().y());

    Q_EMIT echoSwitchState(clientSwitchState); // Emit signal to echo received state back to server
}

void Client::setLocalGeometry_slot(QRect windowGeometry)
{
    qDebug() << "Geometria arrivata";
    setInternalProcessWindow(windowGeometry);

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
