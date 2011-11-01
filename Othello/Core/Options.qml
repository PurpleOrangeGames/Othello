import QtQuick 1.0

Rectangle
{
 width: 300
 height: 200
 x: parent.width/2-width/2
 y: parent.height/2-height/2
 color: originalColor
 radius: 10
 border.width: 5
 border.color: borderColor

 property int buttonMenuPositionX: 65
 property int buttonMenuPositionY: 20
 property int buttonMenuPositionSpacerX: 105
 property int buttonMenuPositionSpacerY: 35

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 0
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 0
  previousColor: "transparent"
  border.color: "transparent"
  textToUse: "Player 1"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 0
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 1
  previousColor: alternateColor
  textToUse: "Human"
  comment: "Player 1"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 0
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 2
  previousColor: alternateColor
  textToUse: "Easy"
  comment: "Player 1"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 0
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 3
  previousColor: alternateColor
  textToUse: "Hard"
  comment: "Player 1"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 0 -25
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 4
  previousColor: alternateColor
  textToUse: "Very Hard"
  comment: "Player 1"
  width: 90
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 1
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 0
  previousColor: "transparent"
  border.color: "transparent"
  textToUse: "Player 2"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 1
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 1
  previousColor: alternateColor
  textToUse: "Human"
  comment: "Player 2"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 1
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 2
  previousColor: alternateColor
  textToUse: "Easy"
  comment: "Player 2"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 1
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 3
  previousColor: alternateColor
  textToUse: "Hard"
  comment: "Player 2"
 }

 Button
 {
  x: buttonMenuPositionX + buttonMenuPositionSpacerX * 1
  y: buttonMenuPositionY + buttonMenuPositionSpacerY * 4
  previousColor: alternateColor
  textToUse: "Very Hard"
  comment: "Player 2"
  width: 90
 }
}
