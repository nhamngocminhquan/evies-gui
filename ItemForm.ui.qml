import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    // property int current_index
    width: 600
    height: 400

    title: qsTr("Item " + current_index)
    // Export de_button & de_label
    property alias popButton: popButton
    property alias label: label

    Label {
        id: label
        text: qsTr("You are on Item " + (current_index + 1) + ".")
        anchors.centerIn: parent
    }

    Button {
        id: popButton
        width: 60
        height: 40
        text: qsTr("<")
        highlighted: false
        checkable: false
        transformOrigin: Item.Center
        font.weight: Font.Normal
        font.family: "Courier"
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 25
    }
}
