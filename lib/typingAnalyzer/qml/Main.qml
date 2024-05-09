import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtCharts
import Qt.labs.platform

MainWindow {
    id: mainWindow
    width: 480
    height: 640
    visible: true
    SystemTrayIcon {
        visible: true
        icon.source: Qt.resolvedUrl("icons/chart.svg")
        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
        onActivated: {
            mainWindow.show()
            mainWindow.raise()
            mainWindow.requestActivate()
        }
    }
}
