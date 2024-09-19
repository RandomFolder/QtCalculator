import QtQuick 2.5
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2


Window {
    id: window
    minimumWidth: 360
    maximumWidth: 360
    minimumHeight: 640
    maximumHeight: 640
    visible: true
    title: qsTr("Calculator")
    flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowCloseButtonHint | Qt.Dialog

    HiddenMenu {
        id: secondMenu

        Connections {
            target: calculatorBackend
            onHiddenMenuVisibleChanged: {
                secondMenu.open();
            }
        }
    }

    MainMenu {
        height: parent.height

        anchors.fill: parent
    }
}
