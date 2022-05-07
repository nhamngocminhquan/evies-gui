import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Page {
    width: 600
    height: 150

    property alias name: name
    property alias primaryTag: primaryTag
    property alias secondaryTags: secondaryTags
    property alias area: area
    property alias seating: seating
    property alias numberOfPeople: numberOfPeople
    property alias catering: catering
    property alias dirhamsPerHour: dirhamsPerHour
    property alias review: review
    property alias frontpane: frontpane

    Pane {
        id: backpane
        anchors.fill: parent
        rightPadding: 0
        bottomPadding: 0
        leftPadding: 0
        topPadding: 0

        RowLayout {
            id: rowLayout
            spacing: 0
            anchors.fill: parent



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
                    anchors.bottomMargin: 45
                    anchors.top: parent.top
                    anchors.topMargin: 25

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
                x: 256
                width: 200
                Layout.preferredWidth: 225
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillWidth: false
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
                    anchors.bottomMargin: 15
                    anchors.top: parent.top
                    anchors.topMargin: 15
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
                            text: qsTr("110 m²")
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
                            id: seating
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
                            id: numberOfPeople
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
                width: 150
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                GridLayout {
                    // layoutDirection: Qt.RightToLeft
                    ColumnLayout {
                        TextArea {
                            id: dirhamsPerHour
                            text: qsTr("51 Dhs")
                            font.pointSize: 22
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            rightPadding: 12
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
                            rightPadding: 12
                            topPadding: 0
                            bottomPadding: 0
                            leftPadding: 0
                        }

                        TextArea {
                            id: review
                            text: qsTr("4.1 / 5 - 20 reviews")
                            font.weight: Font.Light
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            rightPadding: 12
                            topPadding: 0
                            bottomPadding: 0
                            font.bold: false
                            leftPadding: 0
                        }
                    }
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.bottomMargin: 25
                    rows: 2
                    anchors.topMargin: 25
                    anchors.top: parent.top
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    columns: 1
                }
            }
        }
    }

    MouseArea {
        id: frontpane
        anchors.fill: parent
    }
}
