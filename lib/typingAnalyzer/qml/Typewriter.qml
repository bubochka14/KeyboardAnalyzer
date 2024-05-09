import QtQuick
import QtQuick.Controls
Image {
    property date timeInterval
    property alias durationSring: textField.text
    source: Qt.resolvedUrl("pics/typewriter")
    sourceSize.height: 100
    sourceSize.width: 100
 TextField  {
        id: textField
        anchors.top: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: "00:00"
        inputMethodHints: Qt.ImhDigitsOnly
        onActiveFocusChanged:{
                    inputMask="99:99"
            }
        background: Rectangle{
            opacity:    0
        }
    }
}
