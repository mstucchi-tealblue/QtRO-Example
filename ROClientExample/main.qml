import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: client.internalProcessWindowWidth
    height: client.internalProcessWindowHeight
    x: client.internalProcessWindowX
    y: client.internalProcessWindowY
    color:"blue"
    visible: true
    title: qsTr("Hello World")
}
