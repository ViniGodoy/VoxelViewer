import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Window {
    width: 200
    height: 250
    title: "Settings"
    modality: Qt.ApplicationModal
    minimumHeight: height
    minimumWidth: width
    maximumHeight: height
    maximumWidth: width

    property alias backgroundColor: recBackground.color
    property alias transparencyColor: recTransparency.color
    property alias transparencyTolerance : txtTransparencyTolerance.text
    property alias voxelWidth: txtWidth.text
    property alias voxelHeight: txtHeight.text
    property alias voxelDepth: txtDepth.text
    property alias numThreads : txtThreads.text

    signal accepted

    Label {
        id: lblBackground        

        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8

        text: qsTr("Background color:")
        font.bold: true
    }

    Rectangle {
        id: recBackground

        anchors.left: lblBackground.right
        anchors.leftMargin: 8
        anchors.verticalCenter: lblBackground.verticalCenter

        width: 19
        height: 18
        color: "#ffffff"
        radius: 1
        border.color: "#000000"
        border.width: 1
        MouseArea {
            anchors.fill: parent
            onClicked: {
                dlgBackgroundColor.color = recBackground.color;
                dlgBackgroundColor.open();
            }
        }
    }

    Label {
        id: lblTransparency

        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: lblBackground.bottom
        anchors.topMargin: 15

        text: qsTr("Transparency:")
        font.bold: true
    }

    Label {
        id: lblTransparencyColor

        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: lblTransparency.bottom
        anchors.topMargin: 8

        text: qsTr("Color:")
        font.bold: false
    }

    Rectangle {
        id: recTransparency

        anchors.left: lblTransparencyColor.right
        anchors.leftMargin: 8
        anchors.verticalCenter: lblTransparencyColor.verticalCenter

        width: 19
        height: 18
        color: "#ffffff"
        radius: 1
        border.color: "#000000"
        border.width: 1
        MouseArea {
            anchors.fill: parent
            onClicked: {
                dlgTransparencyColor.color = recTransparency.color;
                dlgTransparencyColor.open();
            }
        }
    }

    Label {
        id: lblTransparencyTolerance

        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: lblTransparencyColor.bottom
        anchors.topMargin: 8

        text: qsTr("Tolerance (0 to 1):")
        font.bold: false
    }

    TextField {
        id: txtTransparencyTolerance

        anchors.left: lblTransparencyTolerance.right
        anchors.leftMargin: 3
        anchors.verticalCenter: lblTransparencyTolerance.verticalCenter

        width: 42
        height: 19
        text: "8.888"
        placeholderText: qsTr("w")

        onEditingFinished: textColor = "black";
        validator: DoubleValidator {
            bottom:0.003
            top: 1
            decimals: 3
            notation: DoubleValidator.StandardNotation
        }

    }


    Label {
        id: lblVoxelSize

        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: lblTransparencyTolerance.bottom
        anchors.topMargin: 15

        text: qsTr("Voxel size:")
        font.bold: true
    }

    TextField {
        id: txtWidth

        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: lblVoxelSize.bottom
        anchors.topMargin: 8

        width: 24
        height: 19
        text: "1"
        placeholderText: qsTr("w")
        validator: IntValidator { bottom:1; top: 99}
        onEditingFinished: textColor = "black";
    }


    Label {
        id: lblSep1

        anchors.left: txtWidth.right
        anchors.leftMargin: 8
        anchors.verticalCenter: txtWidth.verticalCenter

        width: 9
        height: 16
        text: qsTr("x")
    }


    TextField {
        id: txtHeight

        anchors.left: lblSep1.right
        anchors.leftMargin: 8
        anchors.verticalCenter: lblSep1.verticalCenter

        width: 24
        height: 19
        text: "1"
        validator: IntValidator { bottom:1; top: 99}
        onEditingFinished: textColor = "black";
    }

    Label {
        id: lblSep2

        anchors.left: txtHeight.right
        anchors.leftMargin: 8
        anchors.verticalCenter: txtHeight.verticalCenter

        width: 9
        height: 16
        text: qsTr("x")
    }

    TextField {
        id: txtDepth

        anchors.left: lblSep2.right
        anchors.leftMargin: 8
        anchors.verticalCenter: lblSep2.verticalCenter

        width: 24
        height: 19
        text: "1"
        placeholderText: qsTr("d")
        validator: IntValidator { bottom:1; top: 99}
        onEditingFinished: textColor = "black";
    }

    Text {
        id: lblThreads
        x: 9
        y: 81
        text: qsTr("Threads:")
        font.bold: true
        font.pixelSize: 12

        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: txtWidth.bottom
        anchors.topMargin: 15
    }

    TextField {
        id: txtThreads
        x: 65
        y: 81
        width: 24
        height: 19

        anchors.verticalCenter: lblThreads.verticalCenter
        anchors.left: lblThreads.right
        anchors.leftMargin: 16

        text: "4"
        validator: IntValidator { bottom:1; top: 99}
        onEditingFinished: textColor = "black";
    }

    Button {
        id: btnOk

        anchors.right: btnCancel.left
        anchors.rightMargin: 8
        anchors.verticalCenter: btnCancel.verticalCenter

        text: qsTr("Ok")
        antialiasing: false
        smooth: true
        isDefault: true
        checkable: false

        onClicked: {
            if (!txtTransparencyTolerance.acceptableInput) {
                txtTransparencyTolerance.focus = true;
                txtTransparencyTolerance.textColor = "red";
                return;
            }

            if (!txtWidth.acceptableInput) {
                txtWidth.focus = true;
                txtWidth.textColor = "red";
                return;
            }

            if (!txtHeight.acceptableInput) {
                txtHeight.focus = true;
                txtHeight.textColor = "red";
                return;
            }

            if (!txtDepth.acceptableInput) {
                txtDepth.focus = true;
                txtDepth.textColor = "red";
                return;
            }

            if (!txtThreads.acceptableInput) {
                txtThreads.focus = true;
                txtThreads.fontColor = "red";
                return;
            }

            close();
            accepted();
        }
    }

    Button {
        id: btnCancel

        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16

        text: qsTr("Cancel")
        onClicked: {
            close();
        }
    }

    ColorDialog
    {
        id: dlgBackgroundColor
        modality: Qt.ApplicationModal
        title: "Choose a background color"
        onAccepted: {
            recBackground.color = color;
            close();
        }
    }

    ColorDialog
    {
        id: dlgTransparencyColor
        modality: Qt.ApplicationModal
        title: "Choose a background color"
        onAccepted: {
            recTransparency.color = color;
            close();
        }
    }


}

