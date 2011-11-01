import QtQuick 1.0
import "Core"

Rectangle
{
 property string backgroundColor: "#1f1d21"
 property string originalColor: "slategray"
 property string alternateColor: "lightblue"
 property string mouseOverColor: "#aaaaaa"
 property string borderColor: "#777777"
 property string playerWhite: "Human"
 property string playerBlack: "Human"
 property int buttonMenuPositionX: 430
 property int buttonMenuPositionY: 15
 property int buttonMenuPositionSpacer: 30

 function clickedOnMenu(button,comment)
 {
  console.log(button,comment)

  if      (comment==="Player 1") { playerWhite=button; options.visible=false }
  else if (comment==="Player 2") { playerBlack=button; options.visible=false }

  if (button==="Start") start();
  else if (button==="Quit") Qt.quit();
 }

 function start()
 {
  list.clear()

  var p1,d1,u1,p2,d2,u2

  d1=0
  u1=0
  d2=0
  u2=0
  if      (playerWhite==="Human"    )   p1="Player"
  else if (playerWhite==="Easy"     ) { p1="Type 0"; d1=2; u1=3  }
  else if (playerWhite==="Hard"     ) { p1="Type 1"; d1=5; u1=7  }
  else if (playerWhite==="Very Hard") { p1="Type 1"; d1=7; u1=14 }

  if      (playerBlack==="Human"    )   p2="Player"//"Rand";
  else if (playerBlack==="Easy"     ) { p2="Type 0"; d2=2; u2=3  }
  else if (playerBlack==="Hard"     ) { p2="Type 1"; d2=5; u2=7  }
  else if (playerBlack==="Very Hard") { p2="Type 1"; d2=7; u2=14 }

  game.startGame(p1,u1,d1,p2,u2,d2)
 }

 function getBoard(x,y,piece)
 {
  list.getBoard(x,y,piece)
 }

 function pieceClicked(i,j)
 {
  game.Player(i,j)
 }

 function getMax(m)
 {
  progressBar.maximum=m
  progressBar.minimum=0
  progressBar.value=0
 }

 function getValue(v)
 {
  progressBar.visible=true
  progressBar.value=v
 }

 function getFinished()
 {
  progressBar.visible=false
 }

 id: main
 width: 100
 height: 62
 color: backgroundColor

 Image
 {
  source: "Engine/board.png"
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 0
  textToUse: "Start"
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 1
  textToUse: "Options"
  MouseArea
  {
   anchors.fill: parent
   onClicked: options.visible=true
  }
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 4
  previousColor: borderColor
  textToUse: "Player 1"
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 5
  previousColor: borderColor
  textToUse: playerWhite
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 6
  previousColor: borderColor
  textToUse: "Vs"
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 7
  previousColor: borderColor
  textToUse: playerBlack
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 8
  previousColor: borderColor
  textToUse: "Player 2"
 }

 Button
 {
  x: buttonMenuPositionX
  y: buttonMenuPositionY + buttonMenuPositionSpacer * 12 + 15
  textToUse: "Quit"
 }

 List
 {
  id: list
 }

 Options
 {
  id: options
  visible: false
 }

 ProgressBar
 {
  id: progressBar
 }

 Connections
 {
  target: game
  onSendBoard: main.getBoard(x,y,piece)
  onSendClear: list.clear()
  onSendMax: main.getMax(m)
  onSendValue: main.getValue(v)
  onSendFinished: main.getFinished()
 }
}
