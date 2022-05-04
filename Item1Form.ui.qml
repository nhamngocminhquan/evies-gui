import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Page {
    width: 600
    height: 400
    property alias score: score

    title: qsTr("Item 1")

    Pane {
        id: backpane
        width: 600
        height: 200
        rightPadding: 0
        bottomPadding: 0
        leftPadding: 0
        topPadding: 0

        Row {
            id: row
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            spacing: 0

            Pane {
                id: label
                width: 250
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                ColumnLayout {
                    width: 120
                    spacing: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 60
                    anchors.top: parent.top
                    anchors.topMargin: 60

                    TextArea {
                        id: name
                        text: qsTr("NYUAD Atrium")
                        Layout.maximumWidth: 225
                        bottomPadding: 0
                        topPadding: 0
                        font.pointSize: 20
                        font.bold: true
                    }

                    TextArea {
                        id: primaryTag
                        text: qsTr("Parks & view")
                        leftPadding: 10
                        bottomPadding: 0
                        topPadding: 0
                    }

                    TextArea {
                        id: secondaryTags
                        text: qsTr("#outdoor #party")
                        font.weight: Font.Light
                        font.pointSize: 9
                        leftPadding: 11
                        rightPadding: 6
                        bottomPadding: 0
                        topPadding: 2
                    }
                }
            }

            Pane {
                id: info
                x: 200
                width: 200
                anchors.left: label.right
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                GridLayout {
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    rows: 2
                    columns: 2

                    ColumnLayout {
                        spacing: 2

                        TextArea {
                            id: label_Area
                            text: qsTr("Area")
                            rightPadding: 0
                            bottomPadding: 0
                            leftPadding: 0
                            topPadding: 0
                            font.bold: true
                        }

                        TextArea {
                            id: area
                            text: qsTr("110 m^2")
                            leftPadding: 0
                            rightPadding: 0
                            bottomPadding: 0
                            topPadding: 0
                        }
                    }

                    ColumnLayout {
                        spacing: 2

                        TextArea {
                            id: label_seats
                            text: qsTr("Seating")
                            font.bold: true
                            leftPadding: 0
                            rightPadding: 0
                            bottomPadding: 0
                            topPadding: 0
                        }

                        TextArea {
                            id: is_seating
                            text: qsTr("Yes")
                            leftPadding: 0
                            rightPadding: 0
                            bottomPadding: 0
                            topPadding: 0
                        }
                    }

                    ColumnLayout {
                        spacing: 2

                        TextArea {
                            id: label_NOP
                            text: qsTr("No. of Ppl.")
                            leftPadding: 0
                            rightPadding: 0
                            bottomPadding: 0
                            topPadding: 0
                            font.bold: true
                        }

                        TextArea {
                            id: textArea5
                            text: qsTr("25")
                            rightPadding: 0
                            leftPadding: 0
                            bottomPadding: 0
                            topPadding: 0
                        }
                    }

                    ColumnLayout {
                        spacing: 2

                        TextArea {
                            id: label_Catering
                            text: qsTr("Catering")
                            font.bold: true
                            leftPadding: 0
                            rightPadding: 0
                            bottomPadding: 0
                            topPadding: 0
                        }

                        TextArea {
                            id: catering
                            text: qsTr("Yes")
                            rightPadding: 0
                            bottomPadding: 0
                            leftPadding: 0
                            topPadding: 0
                        }
                    }
                }
            }

            Pane {
                id: pay
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: info.right
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                GridLayout {
                    layoutDirection: Qt.RightToLeft
                    ColumnLayout {
                        TextArea {
                            id: dirhamsPerHour
                            text: qsTr("51 Dhs")
                            font.pointSize: 22
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            rightPadding: 0
                            topPadding: 0
                            bottomPadding: -4
                            font.bold: true
                            leftPadding: 0
                        }

                        TextArea {
                            id: label_PPH
                            text: qsTr("Price per hour")
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            rightPadding: 0
                            topPadding: 0
                            bottomPadding: 0
                            leftPadding: 0
                        }

                        TextArea {
                            id: score
                            text: qsTr("4.1 / 5 - 20 reviews")
                            font.weight: Font.Light
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            rightPadding: 0
                            topPadding: 0
                            bottomPadding: 0
                            font.bold: false
                            leftPadding: 0
                        }
                    }
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.bottomMargin: 20
                    rows: 2
                    anchors.topMargin: 20
                    anchors.top: parent.top
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    columns: 1
                }
            }
        }
    }
}
