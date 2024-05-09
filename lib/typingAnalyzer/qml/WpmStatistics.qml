import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

Item {
    id: root
    Item
    {
        id: private_stat
        property list<typingRate> rates

    }
    property alias chart: chart
    property int yMaxDist: 40
    function clear()
    {
        chart.lineSeries.clear();
        private_stat.rates=[];
    }

    function appendRate(rate) {
        chart.lineSeries.append(rate.time, rate.cpm)
            totalWordsLbl.text = qsTr(
                        "Total words: ") + rate.wordCount
            avgWpmLbl.text = qsTr(
                        "Average WPM: ") + rate.avgWpm
            totalCharsLbl.text = qsTr(
                        "Total characters: ") + rate.charCount
            avgCpmLbl.text = qsTr(
                        "Average CPM: ") + rate.avgCpm
        private_stat.rates.push(rate);
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        WPMChart {
            id: chart
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        RowLayout {
            id: la
            Layout.alignment: Qt.AlignHCenter
            Layout.margins: 10
            Column {
                Layout.fillWidth: true
                spacing:10
                Text {
                    id: totalWordsLbl
                    anchors.left: parent.left
                    anchors.leftMargin: 50
                    text: qsTr("Total words: ")
                }
                Text {
                    id: avgWpmLbl
                    anchors.left: parent.left
                    anchors.leftMargin: 50
                    text: qsTr("Average WPM: ")
                }
            }
            Column {
                Layout.fillWidth: true
                spacing:10
                Text {
                    id: totalCharsLbl
                    anchors.right: parent.right
                    anchors.rightMargin: 50
                    text: qsTr("Total characters: ")
                }
                Text {
                    id: avgCpmLbl
                    anchors.right: parent.right
                    anchors.rightMargin: 50
                    text: qsTr("Average CPM: ")
                }
            }
        }
    }
}
