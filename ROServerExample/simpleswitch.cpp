#include "simpleswitch.h"

// constructor
SimpleSwitch::SimpleSwitch(QObject *parent) : SimpleSwitchSimpleSource(parent)
{
    qDebug() << "Source Node Started";
}

//destructor
SimpleSwitch::~SimpleSwitch()
{
}



