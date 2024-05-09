import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer
import QtMultimedia

Window {
    id: root
    flags: Qt.FramelessWindowHint
    color: "transparent"

    function showRates(other) {
        stats.clear()
        for(var i=0; i<other.length; ++i)
        {
            stats.appendRate(other[i]);
        }
        root.show()
    }
    MouseArea {

        property var clickPos
        id: dragArea
        anchors.fill: parent
        propagateComposedEvents: true

        onPressed: mouse => {
                       clickPos = Qt.point(mouse.x, mouse.y)
                   }
        onPositionChanged: mouse => {
                               var delta = Qt.point(mouse.x - clickPos.x,
                                                    mouse.y - clickPos.y)
                               root.x += delta.x
                               root.y += delta.y

                           }
    }
    Rectangle {
        x: 10
        y: 10
        width: parent.width - 20
        height: parent.height - 20
        radius: 15
        ColumnLayout {
            anchors.fill: parent

            WpmStatistics {
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: stats
            }

            Button {
                text: qsTr("Awesome!")
                Layout.alignment: Qt.AlignCenter
                focus: true
                onClicked: root.close()
            }
        }
    }

}
