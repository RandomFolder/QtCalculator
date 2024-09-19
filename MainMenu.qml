import QtQuick 2.5

Item {
    id: mainMenu

    Rectangle {
        anchors.fill: parent
        color: "#024873"
    }

    Rectangle {
        x: 0
        y: -30
        width: parent.width
        height: parent.height * 0.33
        radius: 30
        color: "#04BFAD"
    }

    UpperPanel {
        width: parent.width
        height: parent.height * 0.03
    }

    CalcDisplay {
        id: calcDisplayInput

        width: parent.width * 0.8
        height: parent.height * 0.05
        fontSize: 30
        textToDisplay: calculatorBackend.formula

        anchors {
            top: parent.top
            topMargin: parent.height * 0.1
            horizontalCenter: parent.horizontalCenter
        }
    }

    CalcDisplay {
        id: calcDisplayResult

        width: parent.width * 0.8
        height: parent.height * 0.1
        fontSize: 60
        textToDisplay: calculatorBackend.result

        anchors {
            top: calcDisplayInput.top
            topMargin: parent.height * 0.06
            horizontalCenter: parent.horizontalCenter
        }
    }

    CalcButtons {
        id: calcButtons
        width: parent.width * 0.95
        height: parent.height * 0.67

        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height * 0.03
            horizontalCenter: parent.horizontalCenter
        }
    }
}
