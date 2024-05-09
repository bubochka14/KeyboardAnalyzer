import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer
import QtMultimedia

Page {
    id: root
    property alias timePanel: tfPanel
    readonly property TimeFocusModel model: timeFocusPage.model
    Item {
        id: convert
        function toMiliseconds(h = 0, m = 0, s = 0, ms = 0) {
            return h * 3600000 + m * 60000 + s * 1000 + ms
        }
        function msToStr(mil) {
            var hours = Math.floor(mil / 3600000)
            var mins = Math.floor(mil % 3600000 / 60000)
            var s = mil % 3600000 % 60000 / 1000
            return hours + "h " + mins + "m " + (s ? (s + "s") : "")
        }
    }
    Component.onCompleted: root.apply()
    state: {
        var state = timeFocusPage.executable.state
        if (state == Executable.Finished || state == Executable.NotStarted)
            return "NotStarted"
        else
            return "Started"
    }
    function apply() {
        model.clear()
        if (TimeFocusPanel.repeatCount == 0)
            return
        model.insertRows(0, timePanel.repeatCount * 2 - 1)
        var workMs = timePanel.workDuration
        var breakMs = timePanel.breakDuration

        for (var i = 0; i < timePanel.repeatCount * 2 - 1; i += 2) {
            model.setData(model.index(i, 0), workMs, TimeFocusModel.Duration)
            model.setData(model.index(i, 0), workMs,
                          TimeFocusModel.RemainingTime)
            model.setData(model.index(i, 0), 0, TimeFocusModel.Completed)
            model.setData(model.index(i, 0), PeriodInfo.Work,
                          TimeFocusModel.Type)
            if (i != timePanel.repeatCount * 2 - 1) {
                // skip last break
                model.setData(model.index(i + 1, 0), breakMs,
                              TimeFocusModel.Duration)
                model.setData(model.index(i + 1, 0), breakMs,
                              TimeFocusModel.RemainingTime)
                model.setData(model.index(i + 1, 0), 0,
                              TimeFocusModel.Completed)
                model.setData(model.index(i + 1, 0), PeriodInfo.Break,
                              TimeFocusModel.Type)
            }
        }
    }
    padding: 20
    states: [
        State {
            name: "Started"
            PropertyChanges {
                target: tfPanel
                inputFieldsVisible: false
            }
            PropertyChanges {
                target: acceptBtn
                enabled: false
            }
            PropertyChanges {
                target: stopBtn
                enabled: true
            }
        },

        State {
            name: "NotStarted"
            PropertyChanges {
                target: acceptBtn
                enabled: true
            }
            PropertyChanges {
                target: stopBtn
                enabled: false
            }
            PropertyChanges {
                target: tfPanel
                inputFieldsVisible: true
            }
        },
        State {
            name: "Finished"
            PropertyChanges {
                target: acceptBtn
                enabled: true
            }
            PropertyChanges {
                target: stopBtn
                enabled: false
            }
            PropertyChanges {
                target: tfPanel
                inputFieldsVisible: true
            }
        }
    ]
    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        TimeFocusPanel {
            id: tfPanel
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            onBreakDurationChanged: root.apply()
            onRepeatCountChanged: root.apply()
            onWorkDurationChanged: root.apply()
            Component.onCompleted: root.apply()
            repeatCount: 3
            workDuration: 1500000
            breakDuration: 300000
        }
        GridView {
            id: timeMapView
            clip: true
            Layout.fillHeight: true
            Layout.preferredWidth: Math.min(Math.floor(root.width / cellWidth),
                                            count) * cellWidth
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            cellHeight: 150
            cellWidth: 150
            model: root.model
            delegate: Item {
                id: delegate
                height: timeMapView.cellHeight
                width: timeMapView.cellWidth
                Image {
                    id: image
                    states: [
                        State {
                            name: "ACTIVE"
                        }
                    ]
                    transitions: [
                        Transition {
                            from: "*"
                            to: "ACTIVE"
                            RotationAnimation {
                                target: image
                                from: 0
                                loops: Animation.Infinite
                                to: 360
                                duration: 6000
                            }
                        },
                        Transition {
                            from: "ACTIVE"
                            to: "*"
                            ScriptAction{script: image.rotation =0}
                        }
                    ]
                    state: {
                        if (!completed && timeFocusPage.activeIndex == index
                                && root.state == "Started")
                            return "ACTIVE"
                        else
                            return "*"
                    }
                    sourceSize.height: 100
                    sourceSize.width: 100
                    source: {
                        if (completed)
                            source: Qt.resolvedUrl("pics/completed")
                        else if (type === PeriodInfo.Break)
                            source: Qt.resolvedUrl("pics/coffee")
                        else if (type === PeriodInfo.Work)
                            source: Qt.resolvedUrl("pics/typewriter")
                        else
                            source: Qt.resolvedUrl("pics/typewriter")
                    }
                    anchors{
                        horizontalCenter: parent.horizontalCenter
                        top:parent.top
                        topMargin: 15
                    }
                    MouseArea {
                        enabled: (rates.length && completed) ? true : false
                        anchors.fill: parent
                        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                        onClicked: statsDial.showRates(rates)
                    }
                }
                Label {
                    font.pixelSize: 14
                    text: {
                        if (completed)
                            text: "Completed " + rates[rates.length - 1].charCount
                        else
                            text: convert.msToStr(remainingTime)
                    }
                    anchors{
                        horizontalCenter: parent.horizontalCenter
                        bottom: parent.bottom
                        bottomMargin: 10
                    }
                }
            }
        }

        Row {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
            Button {
                id: acceptBtn
                text: "Accept"
                focus: true
                onClicked: {
                    timeFocusPage.executable.start()
                }
            }
            Button {
                id: stopBtn
                text: "Stop"
                enabled: false
                onClicked: {
                    timeFocusPage.executable.finish()
                }
            }
        }
    }
    StatisticsDialog {
        id: statsDial
        height: 600
        width: 500
    }
}
