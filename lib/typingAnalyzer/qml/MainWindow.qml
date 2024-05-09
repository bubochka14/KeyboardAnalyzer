import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

ApplicationWindow {
    id: root
    property list<AppPage> pages: app.pages
    property AppPage currentPage
    function setPageIndex(index) {
        currentPage = pages[index]
        headerBar.text = currentPage.name
        stack.currentIndex = index
    }
    background: Rectangle {
        color: "grey"
    }
    onPagesChanged: {
        stack.children = []
        for (var i = 0; i < root.pages.length; ++i)
            stack.children.push(root.pages[i].getContent())
    }
    Component.onCompleted: {setPageIndex(0)}

    StackLayout {
        id: stack
        anchors.fill: parent
    }
    header: Item {
        height:50
        TabBar {
            id: headerBar
            anchors.fill: parent
            property alias text: tb.text
            TabButton {
                id: tb
            }
        }
        MenuButton {
            id: menuBtn
            anchors.top: parent.top
            anchors.margins: 10
            anchors.left: parent.left
            onClicked: drawer.open()
        }
    }
    Drawer {
        id: drawer
        signal pageSelected(int index, string name)
        onPageSelected: (index, name) => root.setPageIndex(index)
        height: root.height
        width: 200
        ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater {
                model: root.pages
                Button {
                    text: name
                    implicitWidth: drawer.width - 20
                    icon.source: iconSource
                    onClicked: drawer.pageSelected(model.index, name)
                }
            }
        }
    }
}
