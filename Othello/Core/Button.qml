import QtQuick 1.0

Rectangle
{
 signal clicked

 property string textToUse: "None"
 property string comment: "None"
 property color previousColor: originalColor

 id: button
 width: 65
 height: 25
 color: previousColor
 radius: 10
 border.width: 2
 border.color: borderColor

 Text
 {
  id: text
  width: parent.width
  height: parent.height
  text: textToUse
  font.bold: true
  verticalAlignment: Text.AlignVCenter
  horizontalAlignment: Text.AlignHCenter
  font.pointSize: 10
 }

 MouseArea
 {
  hoverEnabled: true
  anchors.fill: parent
  onEntered: parent.color = mouseOverColor
  onExited: parent.color = previousColor
  onClicked: { clickedOnMenu(textToUse,comment); button.clicked() }
 }
}
