import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import KeyboardAnalyzer

Page {
    id: root
    property list<typingRate> rates: freeModePage.rates
    states: [
        State {
            name: "stopped" //when: pauseBtn.pressed  || finishBtn.pressed
            PropertyChanges {
                target: startBtn
                enabled: true
            }
            PropertyChanges {
                target: pauseBtn
                enabled: false
            }
            PropertyChanges {
                target: finishBtn
                enabled: true
            }
        },
        State {
            name: "enrolling" //when: startBtn.pressed
            PropertyChanges {
                target: startBtn
                enabled: false
            }
            PropertyChanges {
                target: pauseBtn
                enabled: true
            }
            PropertyChanges {
                target: finishBtn
                enabled: true
            }
        },
        State {
            name: "finished" //when: startBtn.pressed
            PropertyChanges {
                target: startBtn
                enabled: true
            }
            PropertyChanges {
                target: pauseBtn
                enabled: false
            }
            PropertyChanges {
                target: finishBtn
                enabled: false
            }
        }
    ]
    onRatesChanged: {
        if (rates.length)
            statistics.appendRate(rates[rates.length - 1])
        else
            statistics.clear()
    }
    ColumnLayout {
        anchors.fill: parent
        WpmStatistics {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: statistics
        }
        Row {
            spacing: 10
            Layout.alignment: Qt.AlignHCenter
            Button {
                id: startBtn
                onClicked: {
                    console.log(freeModePage.executable)
                    freeModePage.executable.start()
                    root.state = "enrolling"
                }
                text: qsTr("Start")
            }
            Button {
                id: pauseBtn
                enabled: false
                text: qsTr("Pause")
                onClicked: {
                    freeModePage.executable.stop()
                    root.state = "stopped"
                }
            }
            Button {
                id: finishBtn
                enabled: false
                text: qsTr("Finish")
                onClicked: {
                    freeModePage.executable.finish()
                    root.state = "finished"
                }
            }
        }
    }
}
