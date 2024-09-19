import QtQuick 2.5
import QtQuick.Controls

Drawer {
    id: drawer
    x: 0
    y: 0
    width: parent.width * 0.65
    height: parent.height
    interactive: false
    background: Rectangle {
        color: "grey"
    }

    Text {
        text: "Welcome to hidden menu"
        color: "black"

        anchors {
            top: parent.top
            topMargin: parent.height * 0.1
            horizontalCenter: parent.horizontalCenter
        }
    }

    Button {
        text: "Закрыть скрытое меню"
        width: parent.width * 0.8
        height: parent.height * 0.05
        flat: true
        hoverEnabled: false

        background: Rectangle {
            color: parent.pressed ? "yellow" : "#ef233c"
            radius: 360
        }

        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height * 0.2
            horizontalCenter: parent.horizontalCenter
        }

        onClicked: drawer.close();
    }
}
