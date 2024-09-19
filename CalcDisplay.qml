import QtQuick 2.5
import QtQuick.Controls

Item {
    id: calcDisplay
    property int fontSize
    property string textToDisplay

    Label {
        anchors.fill: parent

        minimumPixelSize: 1
        font.pixelSize: calcDisplay.fontSize
        fontSizeMode: Text.Fit

        text: calcDisplay.textToDisplay
        color: "white"

        font.weight: Font.DemiBold
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }
}
