import QtQuick
import QtQuick.Controls
Row {
    property font font
    TextField  {
        id: hourField
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
