import QtQuick 2.0

import QtQuick.Controls 1.3

Rectangle {
    id: container
    width: 275
    height: 26
    color: "#33ffffff"
    opacity: 1

    property alias backgroundColor: container.color
    property alias value: slider.value
    property alias step: slider.stepSize
    property alias minimum: slider.minimumValue
    property alias maximum: slider.maximumValue
    property alias pressed: slider.pressed
    property alias updateValueWhileDragging: slider.updateValueWhileDragging

    Label {
        id: lblMinimum
        height: 16
        color: "#ffffff"
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        text: slider.minimumValue
    }

    Slider {
        id: slider        
        anchors.left: lblMinimum.right
        anchors.leftMargin: 5
        anchors.right: lblValue.left
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        id: lblValue
        anchors.right: lblBar.left
        anchors.verticalCenter: parent.verticalCenter
        width: 35
        height: 16
        color: "#ffffff"
        text: slider.value.toFixed(0)
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Label {
        id: lblBar
        height: 16
        color: "#ffffff"
        anchors.right: lblMaximum.left
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("/")
    }

    Label {
        id: lblMaximum
        height: 16
        color: "#ffffff"
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        text: slider.maximumValue
    }

}

