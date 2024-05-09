import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
Frame {
    id: root
    signal menuRequested()
    signal modeSwitched
    MenuButton
    {
        id:menuBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        onClicked: menuRequested()
    }
    contentItem: TabBar
        {
            id: tabBar
            width: root.width
            anchors.fill: parent
            TabButton
            {
                id: freeButtonTab
                text: qsTr("Free Mode")
            }
            TabButton
            {
                id:timeFocusTab
                text: qsTr("Time Focus")
            }
        }


}
