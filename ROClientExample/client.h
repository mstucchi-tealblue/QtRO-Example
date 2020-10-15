#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSharedPointer>

#include "../../build-ROClientExample-Desktop_Qt_5_15_1_MSVC2015_64bit-Debug/rep_simpleswitch_replica.h"

class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int internalProcessWindowHeight READ getInternalProcessWindowHeight WRITE setInternalProcessWindowHeight NOTIFY internalProcessWindowHeightChanged)
    Q_PROPERTY(int internalProcessWindowWidth READ getInternalProcessWindowWidth WRITE setInternalProcessWindowWidth NOTIFY internalProcessWindowWidthChanged)
    Q_PROPERTY(int internalProcessWindowX READ getInternalProcessWindowX WRITE setInternalProcessWindowX NOTIFY internalProcessWindowXChanged)
    Q_PROPERTY(int internalProcessWindowY READ getInternalProcessWindowY WRITE setInternalProcessWindowY NOTIFY internalProcessWindowYChanged)


public:
    Client(QSharedPointer<SimpleSwitchReplica> ptr);
    ~Client();
    void initConnections();// Function to connect signals and slots of source and client

    QRect getInternalProcessWindow() const;
    void setInternalProcessWindow(const QRect &value);

    int getInternalProcessWindowHeight() const;
    void setInternalProcessWindowHeight(int value);

    int getInternalProcessWindowWidth() const;
    void setInternalProcessWindowWidth(int value);

    int getInternalProcessWindowX() const;
    void setInternalProcessWindowX(int value);

    int getInternalProcessWindowY() const;
    void setInternalProcessWindowY(int value);

Q_SIGNALS:
    void echoSwitchState(bool switchState);// this signal is connected with server_slot(..) on the source object and echoes back switch state received from source
    void internalProcessWindowHeightChanged();
    void internalProcessWindowWidthChanged();
    void internalProcessWindowXChanged();
    void internalProcessWindowYChanged();

public Q_SLOTS:
    void recSwitchState_slot(); // slot to receive source state
    void setLocalGeometry_slot(QRect windowGeometry);
private:
    bool clientSwitchState; // holds received server switch state
    QSharedPointer<SimpleSwitchReplica> reptr;// holds reference to replica

    QRect internalProcessWindow = QRect(50,50,300,300);
    int internalProcessWindowHeight;
    int internalProcessWindowWidth;
    int internalProcessWindowX;
    int internalProcessWindowY;

 };

#endif
