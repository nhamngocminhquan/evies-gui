import QtQuick 2.9
import QtQuick.Controls 2.2

ItemForm {
    property int current_index
    popButton.onClicked: {
        // console.log("clicked")
        stack.pop()
    }
}
