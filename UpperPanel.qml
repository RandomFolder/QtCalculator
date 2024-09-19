import QtQuick 2.5

Item {
    Rectangle {
        id: back
        anchors.fill: parent
        color: "#04BFAD"
    }

    Text {
        id: timeText
        text: Qt.formatTime(new Date(),"hh:mm")
        anchors {
            right: back.right
            rightMargin: 5
        }
        color: "white"
    }

    Image {
        id: batteryIcon
        source: "qrc:/battery.svg"
        anchors {
            right: timeText.left
            rightMargin: 2
        }
        sourceSize: Qt.size(parent.width * 0.04, parent.height * 0.8)
        anchors.verticalCenter: parent.verticalCenter
    }

    Image {
        id: connectionIcon
        source: "qrc:/cellular.svg"
        anchors {
            right: batteryIcon.left
        }
        sourceSize: Qt.size(parent.width * 0.05, parent.height * 0.8)
        anchors.verticalCenter: parent.verticalCenter
    }

    Image {
        id: wifiIcon
        source: "qrc:/wifi.svg"
        anchors {
            right: connectionIcon.left
        }
        sourceSize: Qt.size(parent.width * 0.05, parent.height * 0.7)
        anchors.verticalCenter: parent.verticalCenter
    }
}
