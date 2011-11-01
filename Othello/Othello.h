#include <QtGui>
#include <QtGui>
#include <QtCore>
#include <QtDeclarative>
#include <QtOpenGL>

#ifndef Othello_H
#define Othello_H

#define size 8
#define player1White false
#define player2Black true
#define shadow 2
#define selectedWhite 3
#define selectedBlack 4
#define whitePiece 0
#define blackPiece 1
#define noPiece 2
#define noMovement false
#define hasMovement true
#define shouldNotPassTurn false
#define shouldPassTurn true

//Estrutura utilizada para montar o tabuleiro:
//p indica o jogador em uma posição do tabuleiro.
//0 para peça branca, 1 para peça preta e 2 para posição vazia.
//d[8] indica possiveis movimentos a partir desta posição do tabuleiro.
//m indica se há possivel movimento, no momento em que eh registrado
//pelo menos um movimento em d[8], o flag m é acionado.
struct pe
{
 int player, d[8];
 bool m;
};

class position//Estrutura de resultado do minimax
{
 public:
  int d[8], x, y;
  position() { this->x=this->y=this->d[0]=this->d[1]=this->d[2]=this->d[3]=this->d[4]=this->d[5]=this->d[6]=this->d[7]=0; }
  position(int x, int y, int d[8]) { this->x=x; this->y=y; if (d!=NULL) copy(d); else this->d[0]=this->d[1]=this->d[2]=this->d[3]=this->d[4]=this->d[5]=this->d[6]=this->d[7]=0; }
  ~position() { }
  position(const position &aux) { copy(aux); }
  void operator=(position aux) { copy(aux); }
  void operator=(int d[8]) { copy(d); }
  void copy(const position &aux) { this->x=aux.x; this->y=aux.y; copy(aux.d); }
  void copy(const int d[8]) { this->d[0]=d[0]; this->d[1]=d[1]; this->d[2]=d[2]; this->d[3]=d[3]; this->d[4]=d[4]; this->d[5]=d[5]; this->d[6]=d[6]; this->d[7]=d[7]; }
};

class boards//Classe boards controla o tabuleiro, distribuindo peças, fazendo movimentos
{
 //pe é o tabuleiro em si
 //ps é a quantidade de peças de cada jogador, sendo ps[0] a quantidade de peças
 //brancas e ps[1] a quantidade de peças pretas em um certo dado momento.
 //qtm é a quantidade de movimentos do jogador ativo em um dado momento.
 //t é um flag que indica se o jogador possue algum movimento ou não.
 public:
  pe b[size][size];
  int ps[2], qtm;
  bool t;

  boards();
  boards(pe tb[size][size]);

  void reset();
  void copy(pe tb[size][size]);
  void count();
  void countm();
  void clear();
  void clearm();
  void start();
  void checkturn();
  void checkboardmovement(int p);
  void movepiece(position r, int p);
};

class Minimax_FA : public QThread //Minimax com função de avaliação
{
 Q_OBJECT

 signals:
  void done(position R);
  void done(int r, position P, QString function);
  void sendStatus(QString status);
 private slots:
  void Minimax(int r, position P, QString function);
 private:
  QString Thread;
  bool Thread_firstplayer, Thread_player;
  int Thread_limit, Thread_height, Thread_alpha, Thread_beta, Thread_type,
      Thread_Child_Gone, Thread_Child_Returned, Thread_Best_Value, Thread_Difficult;
  position Thread_Best_Result, Thread_Position;
  boards Thread_engine;

  void set(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height);
  void set(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height, int alpha, int beta);
  void set(bool firstplayer, position r, bool player, pe tempboard[size][size]);
  void Minimax(bool firstplayer, pe tempboard[size][size], int type, int limit);
  void run();

  bool changePlayer(bool player);
  int MinimaxH1(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height, int alpha, int beta);
  int MinimaxH4(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height, int alpha, int beta);
  int AlfaBeta(bool firstplayer, position r, bool player, pe tempboard[size][size]);
 public:
  void set(bool firstplayer, pe tempboard[size][size], int type, int limit, int difficult);
};

class reversi : public QWidget //Classe que gerencia o jogo Othello / Reversi.
{
 Q_OBJECT

 public:
  reversi(QWidget *parent = 0);
  Q_INVOKABLE void startGame(QString PlayerWhite, int depthUpWhite, int depthDownWhite, QString PlayerBlack, int depthUpBlack, int depthDownBlack);
  Q_INVOKABLE void Player(int x, int y);

 signals:
  void sendBoard(int x, int y, int piece);
  void sendClear();
  void sendMax(int m);
  void sendValue(int v);
  void sendFinished();

 private slots:
  void Update();
  void getAIResult(position r);
  void setStatus(QString status);
  void restartGame();
  void restartCounter();

 private:
  QString PlayerWhite, PlayerBlack;
  boards engine;
  position last_Move;
  bool CurrentPlayer, shouldChangeTurn, shouldEndGame, Lock, paintShadow;
  int depthUpWhite, depthUpBlack, depthDownWhite, depthDownBlack;
  void CheckTurn();
  void ChangePlayer();
  void sendBoard();

  void AI_Random();
  void AI_Minimax(int type);
  void setWindowOptions();
 };

#endif
