import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    /*StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
    }*/
    StackView {
        id: stack
        initialItem: mainView
        anchors.fill: parent
    }

    Component {
        id: mainView
        ScrollView {
            anchors.fill: parent

            ListView {
                width: parent.width
                model: 20
                delegate: ItemDelegate {
                    text: "Item " + (index + 1)
                    width: parent.width
                    onClicked: {
                        stack.push("Item.qml", {current_index: index})
                    }
                }
            }
        }
    }
}
