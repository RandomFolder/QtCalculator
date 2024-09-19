import QtQuick 2.5
import QtQuick.Layouts
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Item {
    id: calcButtons
    visible: true

    property int rowCount: 5
    property int colCount: 4

    property real buttonTextSize: Math.min(width, height)
    property real buttonWidth: width * 0.05
    property real buttonHeight: buttonWidth

    property real colSpacingAllocation: width - (buttonWidth * colCount)
    property real rowSpacingAllocation: height - (buttonHeight * rowCount)

    property real rowSpacing: rowSpacingAllocation / (rowCount - 1)
    property real colSpacing: colSpacingAllocation / (colCount - 1)


    Timer {
        id: countdownTimer
        interval: 4000
        running: false
        repeat: false
        onTriggered: {
            secondTimer.restart();
            toast.show("У вас 5 секунд", 3000);
            calculatorBackend.enableCodeEnter();
        }
    }


    Timer {
        id: secondTimer
        interval: 5000
        running: false
        repeat: false
        onTriggered: {
            calculatorBackend.disableCodeEnter();
        }
    }


    ToolTip {
        id: toast
        delay: 1000
        timeout: 5000
        x: (parent.width - width) / 2
        y: parent.height * 0.95

        background: Rectangle {
            color: "pink"
            radius: 360
        }
    }


    GridLayout {
        rows: calcButtons.rowCount
        columns: calcButtons.colCount

        anchors.fill: parent


        Repeater {
            model: [
                {"buttonText": "()", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/bkt.png"},
                {"buttonText": "⁺∕₋", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/plus_minus.png"},
                {"buttonText": "%", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/percent.png"},
                {"buttonText": "÷", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/division.png"},
                {"buttonText": "7", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/seven.svg"},
                {"buttonText": "8", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/eight.svg"},
                {"buttonText": "9", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/nine.svg"},
                {"buttonText": "×", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/multiplication.png"},
                {"buttonText": "4", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/four.svg"},
                {"buttonText": "5", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/five.svg"},
                {"buttonText": "6", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/six.svg"},
                {"buttonText": "-", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/minus.png"},
                {"buttonText": "1", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/one.svg"},
                {"buttonText": "2", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/two.svg"},
                {"buttonText": "3", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/three.svg"},
                {"buttonText": "+", "buttonColor": "#0889A6", "textColor": "white", "pressedButtonColor": "#F7E425", "actionIcon": "qrc:/plus.png"},
                {"buttonText": "C", "buttonColor": "pink", "textColor": "white", "pressedButtonColor": "#F25E5E", "actionIcon": "qrc:/erase.svg"},
                {"buttonText": "0", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/zero.svg"},
                {"buttonText": ".", "buttonColor": "#B0D1D8", "textColor": "#024873", "pressedButtonColor": "#04BFAD", "actionIcon": "qrc:/dot.svg"}
            ]

            Button {
                Layout.fillWidth: false
                Layout.fillHeight: false
                Layout.preferredWidth: Math.min(parent.width, parent.height) * 0.18
                Layout.preferredHeight: Layout.preferredWidth
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: calculatorBackend.doAction(modelData.buttonText);
                flat: true
                hoverEnabled: false


                background: Rectangle {
                    radius: 360
                    color: parent.pressed ? modelData.pressedButtonColor : modelData.buttonColor

                    Image {
                        source: modelData.actionIcon
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        antialiasing: true
                        smooth: true

                        ColorOverlay {
                            anchors.fill: parent
                            source: parent
                            color: parent.parent.parent.pressed ? "white" : modelData.textColor
                        }
                    }
                }
            }
        }

        Button {
            Layout.fillWidth: false
            Layout.fillHeight: false
            Layout.preferredWidth: Math.min(parent.width, parent.height) * 0.18
            Layout.preferredHeight: Layout.preferredWidth
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: calculatorBackend.doAction("=");
            onPressed: countdownTimer.restart();
            onReleased: countdownTimer.stop();
            flat: true
            hoverEnabled: false

            background: Rectangle {
                radius: 360
                color: parent.pressed ? "#F7E425" : "#0889A6"

                Image {
                    source: "qrc:/equal.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    ColorOverlay {
                        anchors.fill: parent
                        source: parent
                        color: "white"
                    }
                }
            }
        }
    }
}
