import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer
Page {
    id: root
    property int settingNameWidth: 150
    padding: 15
    ListView {
        id: listView
        spacing: 10
        anchors.fill: parent
        model: settingsPage.headers
        delegate: GroupBox {
            id: gb
            title: modelData
            width: listView.width
            ColumnLayout {
                id: delegateRow
                anchors.fill: parent
                spacing:3
                Repeater {
                    id: rep
                    model: settingsPage.addedSettings(modelData)
                    RowLayout {
                        spacing: 10
                        id: row
                        Item {
                            Layout.fillWidth: true
                            height: nameTxt.height
                            Text {
                                id: nameTxt
                                anchors.right: parent.right
                                text: modelData.name
                            }
                        }
                        Item {
                            id:proxy
                            property int contentHeight:50
                            Layout.fillWidth: true
                            Layout.preferredHeight: contentHeight
                            Component.onCompleted: {
                                var obj = modelData.getContent()
                                proxy.children.push(obj)
                                proxy.contentHeight= obj.height
                            }
                        }
                    }
                }
            }
        }
    }
}
