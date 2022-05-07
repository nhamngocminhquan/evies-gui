import QtQuick 2.9
import QtQuick.Controls 2.2
// import "qrc:/TextBanner"

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 400
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
                delegate: TextBanner {
                    name.text:  "Space " + (index + 1)
                    area.text: index * 10 + " m²"
                    dirhamsPerHour.text: (index + 1) * 150 + " Dhs"
                    review.text: index / 4 + " - " + index + " reviews"
                    frontpane.onClicked: {
                        stack.push("Item.qml", {current_index: index, current_label: qsTr("You are looking at " + name.text + " .")})
                    }
                }
//                delegate: ItemDelegate {
//                    text: "Item " + (index + 1)
//                    width: parent.width
//                    onClicked: {
//                        stack.push("Item.qml", {current_index: index})
//                    }
//                }
            }
        }
    }
}
