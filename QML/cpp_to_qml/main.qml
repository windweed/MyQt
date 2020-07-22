import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

import ColorMaker 1.0

Window {
    id: root
    width:  1000
    height: 600
    visible: true

    Text {
        id: timeLabel
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        font.pixelSize: 26
    }

    ColorMaker {
        id: colormaker
        color: Qt.green
    }

    Rectangle {
        id: colorRect
        anchors.centerIn: parent
        width: 200
        height: 200
        color: "blue"
    }

    Button {
        id: startBtn
        text: qsTr("start")
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        onClicked: {
            colormaker.start();
        }
    }

    Button {
        id: stopBtn
        text: "stop"
        anchors.left: startBtn.right
        anchors.leftMargin: 4
        anchors.bottom: startBtn.bottom
        onClicked: {
            colormaker.stop();
        }
    }

    function changeAlgorithm(button, algorithm) {
        switch(algorithm)
        {
        case 0:
            button.text = "RandomRGB";
            break;
        case 1:
            button.text = "RandomRed"
            break;
        case 2:
            button.text = "RandomGreen";
            break;
        case 3:
            button.text = "RandomBlue";
            break;
        case 4:
            button.text = "LinearIncrease";
            break;
        }
    }

    Button {
        id: colorAlgorithm
        text: "RandomRGB"
        anchors.left: stopBtn.right
        anchors.leftMargin: 4
        anchors.bottom: startBtn.bottom
        onClicked: {
            var algorithm = (colormaker.algorithm() + 1) % 5;
            changeAlgorithm(colorAlgorithm, algorithm);
            colormaker.setAlgorithm(algorithm);
        }
    }

    Button {
        id: quitBtn
        text: "quit"
        anchors.left: colorAlgorithm.right
        anchors.leftMargin: 4
        anchors.bottom: startBtn.bottom
        onClicked: {
            Qt.quit();
        }
    }

    Component.onCompleted: {
        colormaker.color = Qt.rgba(0, 180, 120, 255);
        colormaker.setAlgorithm(ColorMaker.LinearIncrease);
        changeAlgorithm(colorAlgorithm, colormaker.algorithm());
    }

    Connections {
        target: colormaker
        onCurrentTime: {
            timeLabel.text = strTime;
            timeLabel.color = colormaker.timeColor;
        }
    }

    Connections {
        target: colormaker;
        onColorChanged: {
            colorRect.color = color
        }
    }

}
