#include "Othello.h"
#include <time.h>

reversi::reversi(QWidget *parent) : QWidget(parent)
{
 qRegisterMetaType<position>("position");
 srand(time(NULL));
 CurrentPlayer=false; //Jogador
 setWindowOptions();
 startGame("Player",0,0,"Player",0,0);
}

void reversi::setWindowOptions()
{
 QDeclarativeView *view = new QDeclarativeView;
 QGLWidget *glWidget = new QGLWidget();
 glWidget->setAutoFillBackground(false);
 view->setViewport(glWidget);

 connect(view->engine(), SIGNAL(quit()), SLOT(close()));
 view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

 view->rootContext()->setContextProperty("game",this);
 view->setSource(QUrl("qrc:/Othello.qml"));
 view->setFixedSize(500,425);

 QGridLayout *layout = new QGridLayout(this);
 layout->addWidget(view,0,0);
 layout->setMargin(0);
 layout->setSpacing(0);
}

void reversi::restartCounter()
{
 //gamePlayer1Win=0;
 //gamePlayer2Win=0;
}

void reversi::restartGame()
{
 last_Move.x=last_Move.y=-2;
 engine.start();
 Lock=false;
 CurrentPlayer=player1White;
}

void reversi::startGame(QString PlayerWhite, int depthUpWhite, int depthDownWhite, QString PlayerBlack, int depthUpBlack, int depthDownBlack)
{
 restartGame();
 this->PlayerWhite=PlayerWhite;
 this->depthUpWhite=depthUpWhite;
 this->depthDownWhite=depthDownWhite;

 this->PlayerBlack=PlayerBlack;
 this->depthUpBlack=depthUpBlack;
 this->depthDownBlack=depthDownBlack;

 sendBoard();
}

void reversi::setStatus(QString status)
{
 if (status.contains("Start"))
 {
  sendMax(status.split("|").at(1).toInt());
  sendValue(0);
 }
 else if (status.contains("Update"))
  sendValue(status.split("|").at(1).toInt());
 else if (status.contains("Done"))
  sendFinished();
}

void reversi::Update()
{
 CheckTurn();//Passa o turno
 sendBoard();
 Lock=false;

 if (CurrentPlayer==player2Black && !engine.t && !Lock)
 {
  if (PlayerBlack=="Player") return;
  if (PlayerBlack=="Type 0") AI_Minimax(0);
  if (PlayerBlack=="Type 1") AI_Minimax(1);
  if (PlayerBlack=="Rand") AI_Random();
 }
 else if (CurrentPlayer==player1White && !engine.t && !Lock)
 {
  if (PlayerWhite=="Player") return;
  if (PlayerWhite=="Type 0") AI_Minimax(0);
  if (PlayerWhite=="Type 1") AI_Minimax(1);
  if (PlayerWhite=="Rand") AI_Random();
 }
}

void reversi::sendBoard()
{
 sendClear();
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   if (engine.b[i][j].player==player1White || engine.b[i][j].player==player2Black)
   {
    if (last_Move.x==i && last_Move.y==j)
    {
     if (CurrentPlayer)
      sendBoard(last_Move.x,last_Move.y,selectedWhite);
     else
      sendBoard(last_Move.x,last_Move.y,selectedBlack);
    }
    else
     sendBoard(i,j,engine.b[i][j].player);
   }
   else if (engine.b[i][j].m && paintShadow)
    if ((CurrentPlayer==player1White && PlayerWhite=="Player")
     || (CurrentPlayer==player2Black && PlayerBlack=="Player"))
     sendBoard(i,j,shadow);
}

void reversi::ChangePlayer()
{
 if (CurrentPlayer==player2Black) CurrentPlayer=player1White; else CurrentPlayer=player2Black;//Troca o jogador
}

void reversi::CheckTurn()//Função que troca o jogador, verifica se deve passar o turno ou se deve terminar o jogo
{
 ChangePlayer();//Troca o jogador
 engine.checkboardmovement(CurrentPlayer);//Verifica Movimento

 if (engine.t==shouldPassTurn)//Sem movimentos, passa o turno
 {
  ChangePlayer();//Troca o jogador
  engine.checkboardmovement(CurrentPlayer);//Verifica Movimento
  if (engine.t==shouldPassTurn)//Sem movimentos novamente, termina o jogo
  {
   engine.count();
   qWarning()<<"player1White"<<engine.ps[player1White]<<"-"<<"player2Black"<<engine.ps[player2Black];
   //if (engine.ps[0]==engine.ps[1]) { gameDraw++; othellotitle.setText("Draw"); whoWon="Draw"; }
   //else if (engine.ps[0]>engine.ps[1]) { gamePlayer1Win++; othellotitle.setText("Player 1 won"); whoWon="White"; }
   //else if (engine.ps[0]<engine.ps[1]) { gamePlayer2Win++; othellotitle.setText("Player 2 won"); whoWon="Black"; }
  }
  else
   qWarning()<<"Skip Turn";
 }
}

void reversi::Player(int x, int y)//Função responsável por administrar as ações do jogador
{
 if (Lock) return;
 Lock=true;
 engine.checkboardmovement(CurrentPlayer);//Verifica possíveis movimentos do jogador
 if (engine.b[x][y].m)//Se o movimento pedido existe, mova a peça
 {
  last_Move=position(x,y,engine.b[x][y].d);
  engine.movepiece(position(x,y,engine.b[x][y].d),CurrentPlayer);//Mova a peça
  Update();
  return;
 }
}

void reversi::AI_Random()//Função responsável por administrar as ações do oponente randômico.
{
 if (Lock) return;
 Lock=true;
 engine.checkboardmovement(CurrentPlayer);//Verifica possíveis movimentos do jogador
 engine.countm();//Conta a quantidade de possíveis movimentos
 int rand_temp=(rand()%engine.qtm)+1, qty=0;// Gera numero randomico
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
  {
   if (engine.b[i][j].m) qty++;//Proximo possível movimento
   if (rand_temp==qty)//Acha o numero randomico dentro dos possiveis movimentos
   {
    last_Move=position(i,j,engine.b[i][j].d);
    engine.movepiece(position(i,j,engine.b[i][j].d),CurrentPlayer);//Move a peça
    Update();
    return;//Retorna
   }
  }
}

void reversi::AI_Minimax(int type)//Função responsável por direcionar o jogo a função minimax desejada.
{
 if (Lock) return;
 Lock=true;
 engine.checkboardmovement(CurrentPlayer);//Verifica possíveis movimentos do jogador
 Minimax_FA *AI=new Minimax_FA;

 if (CurrentPlayer==player1White) AI->set(CurrentPlayer,engine.b,type,depthDownWhite,depthUpWhite);//Pega o resultado do melhor movimento
 else                             AI->set(CurrentPlayer,engine.b,type,depthDownBlack,depthUpBlack);//Pega o resultado do melhor movimento

 connect(AI,SIGNAL(done(position)),this,SLOT(getAIResult(position)));
 connect(AI,SIGNAL(sendStatus(QString)),this,SLOT(setStatus(QString)));
 AI->start();
}

void reversi::getAIResult(position r)
{
 last_Move=r;
 engine.movepiece(r,CurrentPlayer);//Move a peça
 Update();
}
