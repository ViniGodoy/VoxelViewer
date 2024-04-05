import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import VoxelViewer 1.0

ApplicationWindow {
    id: window
    title: qsTr("Voxel Viewer 1.0")
    width: 800
    height: 600
    visible: true

    SettingsForm {
        id: frmSettings

        onAccepted: {
            viewer.backgroundColor = backgroundColor;
            viewer.transparencyColor = transparencyColor;
            viewer.transparencyTolerance = Number.fromLocaleString(Qt.locale(), transparencyTolerance);
            viewer.voxelSize = Qt.vector3d(voxelWidth, voxelHeight, voxelDepth);
            viewer.numThreads = numThreads;
        }
    }

    AboutForm {
        id: frmAbout
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            MenuItem {
                text: qsTr("&Open")
                onTriggered: dlgFile.open()
            }

            MenuItem {
                text: qsTr("&Settings")
                onTriggered: {
                    frmSettings.backgroundColor = viewer.backgroundColor;
                    frmSettings.transparencyColor = viewer.transparencyColor;
                    frmSettings.transparencyTolerance = viewer.transparencyTolerance.toLocaleString(Qt.locale(), "f", 3);
                    frmSettings.voxelWidth = viewer.voxelSize.x.toFixed(0);
                    frmSettings.voxelHeight = viewer.voxelSize.y.toFixed(0);
                    frmSettings.voxelDepth = viewer.voxelSize.z.toFixed(0);
                    frmSettings.numThreads = viewer.numThreads;
                    frmSettings.show();
                }
            }

            MenuItem {
                text: qsTr("&About")
                onTriggered: {
                    frmAbout.show();
                }
            }

            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit()
            }
        }
    }

    VoxelItem {
        id: viewer
        x: 0
        y: 0
        width: window.width
        height: window.height
        smooth: false
        angleX: sliAngleX.value
        angleY: sliAngleY.value
        angleZ: sliAngleZ.value
        cameraDistance: sliCamera.value
        draft: chkDraft.checked        

        Item {
            id: item1
            x: 596
            width: 300
            height: 325
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 5

            Label {
                id: lblAngleX
                x: 8
                y: 13
                color: "#ffffff"
                text: qsTr("Angle x:")
                font.pixelSize: 12
            }

            CuteSlider {
                id: sliAngleX
                y: 5
                height: 26

                anchors.top: lblAngleX.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5

                maximum: 360
            }

            Label {
                id: lblAngleY
                x: 8
                color: "#ffffff"
                anchors.top: sliAngleX.bottom
                anchors.topMargin: 10
                text: qsTr("Angle y:")
            }

            CuteSlider {
                id: sliAngleY
                height: 26
                anchors.top: lblAngleY.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5
                maximum: 360
            }

            Label {
                id: lblAngleZ
                x: 8
                color: "#ffffff"
                anchors.top: sliAngleY.bottom
                anchors.topMargin: 10
                text: qsTr("Angle z:")
            }

            CuteSlider {
                id: sliAngleZ
                height: 26
                anchors.top: lblAngleZ.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5
                maximum: 360
            }

            Label {
                id: lblCamera
                x: 8
                color: "#ffffff"
                anchors.top: sliAngleZ.bottom
                anchors.topMargin: 10
                text: qsTr("Camera distance:")
            }

            CuteSlider {
                id: sliCamera
                height: 26
                anchors.top: lblCamera.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5
                minimum: 400
                maximum: 50000
                value: 2000
            }

            CheckBox {
                id: chkDraft
                anchors.top: sliCamera.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5

                checked: true
                style: CheckBoxStyle {
                    label: Text {
                        color: "white"
                        text: qsTr("Draft")
                    }
                }
            }
        }
    }

    FileDialog {
        id: dlgFile
        visible: false
        modality: Qt.WindowModal
        title: qsTr("Chooser a folder");
        selectFolder: true
        selectMultiple: false
        selectExisting: true
        onAccepted: {
            viewer.dataPath = fileUrl
        }
    }

}
