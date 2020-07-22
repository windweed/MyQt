import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        color: "#eeeeee"

        ListView {
            id: listView
            anchors.fill: parent

            delegate: phoneDelegate
            model: phoneModel.createObject(listView)
            header: headerView
            footer: footerView

            focus: true
            highlight: Rectangle {
                color: "lightblue"
            }

            onCurrentIndexChanged: {
                if (listView.currentIndex >= 0) {
                    var data = listView.model.get(listView.currentIndex);
                    listView.footerItem.text = data.name + " ,\
 " + data.cost + " , " + data.manufacturer;
                }
                else
                {
                    listView.footerItem.text = "";
                }
            }

            function addOne() {
                model.append(
                    {
                        "name": "MX3",
                        "cost": "1799",
                        "manufacturer": "Meizu"
                    }
                );
            }

            Component.onCompleted: {
                listView.footerItem.clean.connect(listView.model.clear)
                listView.footerItem.add.connect(listView.addOne)
            }
        }//ListView
    }

    Component {
        id: phoneModel
        ListModel {
            ListElement {
                name: "iPhone 3GS"
                cost: "1000"
                manufacturer: "Apple"
            }
            ListElement {
                name: "iPhone 5"
                cost: "1870"
                manufacturer: "Apple"
            }
            ListElement {
                name: "iPhone 6"
                cost: "1830"
                manufacturer: "Apple"
            }
            ListElement {
                name: "iPhone 7"
                cost: "18000"
                manufacturer: "Apple"
            }
        }
    }//phoneModel

    Component {
        id: headerView
        Item {
            width: parent.width
            height: 30
            RowLayout {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8
                Text {
                    text: " Name "
                    font.bold: true
                    font.pixelSize: 20
                    Layout.preferredWidth: 120
                }
                Text {
                    text: " Cost "
                    font.bold: true
                    font.pixelSize: 20
                    Layout.preferredWidth: 80
                }
                Text {
                    text: "Manufacturer"
                    font.bold: true
                    font.pixelSize: 20
                    Layout.fillWidth: true
                }
            }
        }
    }//headerView

    Component {
        id: phoneDelegate
        Item {
            id: wrapper
            width: parent.width
            height: 30

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    wrapper.ListView.view.currentIndex = index;
                    mouse.accepted = true;
                }
                onDoubleClicked: {
                    wrapper.ListView.view.model.remove(index);
                    mouse.accepted = true;
                }
            }

            RowLayout {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8
                Text {
                    id: coll
                    text: name
                    color: wrapper.ListView.isCurrentItem ? "red" : "black";
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 22 : 18;
                    Layout.preferredWidth: 120
                }

                Text {
                    text: cost
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 22 : 18
                    Layout.preferredWidth: 80
                }
                Text {
                    text: manufacturer
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 22 : 18
                    Layout.fillWidth: true
                }
            }
        }
    }//delegate

    Component {
        id: footerView
        Item {
            id: footerRootItem
            width: parent.width
            height: 30

            property alias text: txt.text
            signal clean();
            signal add();

            Text {
                id: txt
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                font.italic: true
                color: "blue"
                verticalAlignment: Text.AlignVCenter
            }

            Button {
                id: btnClearAll
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: 25
                text: "Clear"
                onClicked: footerRootItem.clean();
            }

            Button {
                id: btnAddOne
                anchors.right: btnClearAll.left
                anchors.rightMargin: 4
                anchors.verticalCenter: parent.verticalCenter
                height: 25
                text: "Add"
                onClicked: footerRootItem.add();
            }
        }
    }//footer
}
