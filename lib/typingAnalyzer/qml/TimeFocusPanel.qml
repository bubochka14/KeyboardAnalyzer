import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

ColumnLayout {
    id: root
    property bool inputFieldsVisible: true
    property alias breakDuration : breakDurationRow.totalMs
    property alias workDuration : workDuration.totalMs
    property alias repeatCount : repeatTf.count

    visible: inputFieldsVisible
    Row {
        id: repeatCountRow
        Layout.alignment: Qt.AlignHCenter
        Label {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Repeat count:  ")
        }
        TextField {
            id: repeatTf
            property int count
            onDisplayTextChanged:{repeatTf.count =parseInt(repeatTf.displayText)}
            inputMask: "9;0"
            Component.onCompleted: text = count
        }
    }
    Row {
        Layout.alignment: Qt.AlignHCenter
        Label {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Work duration: ")
        }
        TimeField {
            id: workDuration
        }
    }
    Row {
        Layout.alignment: Qt.AlignHCenter

        Label {
            anchors.verticalCenter: parent.verticalCenter

            text: qsTr("Break duration: ")
        }
        TimeField {
            id: breakDurationRow
        }
    }
}
