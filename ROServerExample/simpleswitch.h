#ifndef SIMPLESWITCH_H
#define SIMPLESWITCH_H

#include <QTimer>
#include "rep_simpleswitch_source.h"

class SimpleSwitch : public SimpleSwitchSimpleSource
{
    Q_OBJECT
public:
    SimpleSwitch(QObject *parent = nullptr);
    ~SimpleSwitch();
    virtual void server_slot(bool clientState);
public Q_SLOTS:
    void timeout_slot();
private:
    QTimer *stateChangeTimer;
};

#endif // SIMPLESWITCH_H
