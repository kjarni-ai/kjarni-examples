import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import KjarniChat

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "Local chat"

    LocalChat { id: chat }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            TextArea {
                text: chat.transcript
                readOnly: true
                wrapMode: TextEdit.Wrap
            }
        }

        RowLayout {
            TextField {
                id: input
                Layout.fillWidth: true
                placeholderText: "Ask something"
                onAccepted: send.clicked()
            }
            Button {
                text: "Clear"
                enabled: chat.ready && !chat.generating
                onClicked: chat.clear()
            }
            Button {
                id: send
                text: chat.generating ? "Stop" : "Send"
                enabled: chat.ready
                onClicked: {
                    if (chat.generating) {
                        chat.stop()
                    } else {
                        chat.send(input.text)
                        input.clear()
                    }
                }
            }
        }

        Label { text: chat.status }
    }
}
