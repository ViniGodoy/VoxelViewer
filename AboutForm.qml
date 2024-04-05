import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

Window {
    width: 315
    height: 300
    title: "About this application"
    minimumHeight: height
    minimumWidth: width
    maximumHeight: height
    maximumWidth: width


    Image {
        id: imgLogo

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        width: 92
        height: 104
        sourceSize.width: 300
        antialiasing: true
        fillMode: Image.Stretch
        source: "qrc:///logo_pucpr.jpg"
    }

    Text {
        id: lblAppName

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        text: qsTr("VoxelViewer")
        font.bold: true
        font.pixelSize: 20
    }

    Text {
        id: lblAppVersionTitle

        anchors.top: lblAppName.bottom
        anchors.topMargin: 7
        anchors.left: parent.left
        anchors.leftMargin: 10

        text: qsTr("Version")
        font.pixelSize: 12
    }

    Text {
        id: lblAppVersion

        anchors.top: lblAppName.bottom
        anchors.topMargin: 7
        anchors.left: lblAppVersionTitle.right
        anchors.leftMargin: 2

        text: qsTr("1.0.1")
        font.pixelSize: 12
    }

    Text {
        id: lblProducedByTitle

        anchors.top: lblAppVersionTitle.bottom
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 10

        text: qsTr("Produced by:")
        font.bold: true
        textFormat: Text.AutoText
        font.pixelSize: 12
    }

    Text {
        id: lblAuthor

        anchors.top: lblProducedByTitle.bottom
        anchors.topMargin: 7
        anchors.left: parent.left
        anchors.leftMargin: 20

        text: qsTr("Vinícius Godoy de Mendonça")
        font.pixelSize: 12
    }

    Text {
        id: lblTeam

        anchors.top: lblAuthor.bottom
        anchors.topMargin: 7
        anchors.left: parent.left
        anchors.leftMargin: 20

        text: qsTr("Image Processing Group")
        font.pixelSize: 12
    }

    Text {
        id: lblCopyright

        anchors.top: lblTeam.bottom
        anchors.topMargin: 27
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        height: 61
        text: qsTr("Copyright 2015 PUCPR. All rights reserved. This program is free software: you can redistribute it and/or modify it under the terms of the GPL v3.");
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        font.pixelSize: 12
    }

    Button {
        id: btnClose

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        text: qsTr("Close")
        isDefault: true
        onClicked: close()
    }
}

