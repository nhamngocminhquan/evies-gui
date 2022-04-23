import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 600
    height: 400

    title: qsTr("Item 1")

    Label {
        text: qsTr("You are on Item 1.")
        anchors.centerIn: parent
    }
}
