import QtQuick 2.9
import QtQuick.Controls 2.2

HomeForm {
    ScrollView {
    anchors.fill: parent

    ListView {
        width: parent.width
        model: 20
        delegate: ItemDelegate {
            text: "Item " + (index + 1)
            width: parent.width
        }
    }
}
