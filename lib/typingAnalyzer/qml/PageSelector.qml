import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {
    id: root
    property list<MainWindowPage> pagesToSelect
    signal pageSelected(index : int, name: string)
    ColumnLayout{
        anchors.horizontalCenter: parent.horizontalCenter
        Repeater
        {
            model: root.pagesToSelect
            Button{
                text: name
                implicitWidth: root.width-20
                icon.source: iconSource
                onClicked: root.pageSelected(model.index,name)
            }
        }
    }
}
