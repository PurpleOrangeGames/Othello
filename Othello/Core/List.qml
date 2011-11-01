import QtQuick 1.0

Item
{
 anchors.fill: parent

 function clear()
 {
  for (var i=0;i<board.count;i++)
   board.get(i).piece=-1
 }

 function getBoard(x,y,piece)
 {
  for (var i=0;i<board.count;i++)
   if (board.get(i).i===x && board.get(i).j===y)
   {
    board.get(i).piece=piece
    return
   }

  board.append({"i":x, "j":y, "piece":piece})
 }

 ListModel
 {
  id: board
 }

 Component
 {
  id: delegate

  Item
  {
   Image
   {
    source: if (piece===0 || piece===3) "../Engine/white.png"
            else if (piece===1 || piece===4) "../Engine/black.png"
            else if (piece===2) "../Engine/shadow.png"
            else "../Engine/blank.png"
    x: 12+50*i
    y: 12+50*j

    MouseArea
    {
     hoverEnabled: true
     anchors.fill: parent
     onEntered: if (piece===2) front.source="../Engine/selected.png"
     onExited: if (piece!=3 && piece!=4) front.source="../Engine/blank.png"
     onClicked: { front.source="../Engine/blank.png"; pieceClicked(i,j) }
    }
   }

   Image
   {
    source: if (piece===3 || piece===4) "../Engine/selected.png"
            else "../Engine/blank.png"
    x: 12+50*i
    y: 12+50*j
   }

   Image
   {
    id: front
    source: "../Engine/blank.png"
    x: 12+50*i
    y: 12+50*j
   }
  }
 }

 Repeater
 {
  anchors.fill: parent
  model: board
  delegate: delegate
 }
}
