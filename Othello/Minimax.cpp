#include "Othello.h"

bool Minimax_FA::changePlayer(bool player)
{
 if (player==player1White) return player2Black; else return player1White;
}

void Minimax_FA::set(bool firstplayer, pe tempboard[size][size], int type, int limit, int difficult)
{
 Thread="Start";
 Thread_firstplayer=firstplayer;
 Thread_type=type;
 Thread_limit=limit;
 Thread_engine.copy(tempboard);
 Thread_Difficult=difficult;
}

void Minimax_FA::set(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height)
{
 Thread="Type 0";
 Thread_firstplayer=firstplayer;
 Thread_player=player;
 Thread_Position=r;
 Thread_height=height;
 Thread_limit=limit;
 Thread_alpha=-100;
 Thread_beta=100;
 Thread_engine.copy(tempboard);
}

void Minimax_FA::set(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height, int alpha, int beta)
{
 Thread="Type 1";
 Thread_firstplayer=firstplayer;
 Thread_player=player;
 Thread_Position=r;
 Thread_height=height;
 Thread_limit=limit;
 Thread_alpha=alpha;
 Thread_beta=beta;
 Thread_engine.copy(tempboard);
}

void Minimax_FA::set(bool firstplayer, position r, bool player, pe tempboard[size][size])
{
 Thread="Type AB";
 Thread_firstplayer=firstplayer;
 Thread_player=player;
 Thread_Position=r;
 Thread_engine.copy(tempboard);
}

void Minimax_FA::run()
{
 if (Thread=="Start")
  Minimax(Thread_firstplayer,Thread_engine.b,Thread_type,Thread_limit);
 else if (Thread=="Type 0")
  emit done(MinimaxH1(Thread_firstplayer,Thread_limit,Thread_Position,Thread_player,Thread_engine.b,Thread_height,Thread_alpha,Thread_beta),Thread_Position,Thread);
 else if (Thread=="Type 1")
  emit done(MinimaxH4(Thread_firstplayer,Thread_limit,Thread_Position,Thread_player,Thread_engine.b,Thread_height,Thread_alpha,Thread_beta),Thread_Position,Thread);
 else if (Thread=="Type AB")
  emit done(AlfaBeta(Thread_firstplayer,Thread_Position,Thread_player,Thread_engine.b),Thread_Position,Thread);
}

void Minimax_FA::Minimax(bool firstplayer, pe tempboard[size][size], int type, int limit)
{
 boards engine(tempboard);
 engine.checkboardmovement(firstplayer);
 Thread_Best_Value=-100;
 Thread_Child_Returned=0;
 Thread_Child_Gone=0;
 engine.countm();//Conta a quantidade de possíveis movimentos
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   if (engine.b[i][j].m)
   {
    Minimax_FA *tempThread = new Minimax_FA;
    engine.count();//Conta a quantidade de peças no tabuleiro

    if (engine.ps[0]+engine.ps[1]<64-Thread_Difficult)//Se não estiver acabando o jogo, faça Minimax Heuristico
    {
     if (type==0)
      tempThread->set(firstplayer,limit,position(i,j,engine.b[i][j].d),firstplayer,engine.b,0);
     else if (type==1)
      tempThread->set(firstplayer,limit,position(i,j,engine.b[i][j].d),firstplayer,engine.b,0,-100,100);
    }
    else//Se estiver acabando o jogo, faça Minimax Completo
     tempThread->set(firstplayer,position(i,j,engine.b[i][j].d),firstplayer,engine.b);

    Thread_Child_Gone++;
    connect(tempThread,SIGNAL(done(int,position,QString)),this,SLOT(Minimax(int,position,QString)));
    tempThread->start();
   }
 sendStatus(tr("Start|%1").arg(Thread_Child_Gone));
}

void Minimax_FA::Minimax(int r, position P, QString function)
{
 Thread_Child_Returned++;
 bool isDone=false;
 if ((function=="Type AB" || function=="Type 0") && r==1)
 {
  Thread_Best_Result=P;
  Thread_Best_Value=1;
  isDone=true;
 }
 if (r>Thread_Best_Value)
 {
  Thread_Best_Result=P;
  Thread_Best_Value=r;
 }
 else if (r==Thread_Best_Value && (((rand()%2)+1)==1))
 {
  Thread_Best_Result=P;
  Thread_Best_Value=r;
 }

 if (Thread_Child_Returned==Thread_Child_Gone)
  isDone=true;

 sendStatus(tr("Update|%1").arg(Thread_Child_Returned));

 if (isDone)
 {
  sendStatus("Done");
  emit done(Thread_Best_Result);
  this->disconnect();
 }
}

int Minimax_FA::MinimaxH1(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height, int alpha, int beta)
{
 boards engine(tempboard);

 height++;
 if (height>limit)
 {
  int ms[2];
  engine.count();
  ms[0]=engine.ps[0];
  ms[1]=engine.ps[1];

  if (firstplayer)
   return ms[1]-ms[0];
  else
   return ms[0]-ms[1];
 }

 if (r.x!=-1)
  engine.movepiece(r,player);

 player=changePlayer(player);
 engine.checkboardmovement(player);

 if (engine.t)
 {
  bool enemy;
  if (player) enemy=false; else enemy=true;
  engine.checkboardmovement(enemy);
  if (engine.t)
  {
   int ms[2];
   engine.count();
   ms[0]=engine.ps[0];
   ms[1]=engine.ps[1];

   if (firstplayer)
    return ms[1]-ms[0];
   else
    return ms[0]-ms[1];
  }
  else
   return MinimaxH4(firstplayer,limit,position(-1,-1,NULL),player,engine.b,height,alpha,beta);
 }
 else
 {
  int temp;
  if (firstplayer==player)
  {
   temp=-100;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=MinimaxH1(firstplayer,limit,position(i,j,engine.b[i][j].d),player,engine.b,height,alpha,beta);
      if (temp<temp2)
      {
       temp=temp2;
       alpha=temp;
       if (temp>beta)
        return temp;
      }
     }
  }
  else
  {
   temp=100;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=MinimaxH1(firstplayer,limit,position(i,j,engine.b[i][j].d),player,engine.b,height,alpha,beta);
      if (temp>temp2)
      {
       temp=temp2;
       beta=temp;
       if (temp<alpha)
        return temp;
      }
     }
  }
  return temp;
 }
}

int Minimax_FA::MinimaxH4(bool firstplayer, int limit, position r, bool player, pe tempboard[size][size], int height, int alpha, int beta)
{
 boards engine(tempboard);

 height++;
 if (height>limit)
 {
  int ms[2];
  engine.checkboardmovement(0);
  engine.countm();
  ms[0]=engine.qtm;
  engine.checkboardmovement(1);
  engine.countm();
  ms[1]=engine.qtm;

  if (firstplayer)
   return ms[1]-ms[0];
  else
   return ms[0]-ms[1];
 }

 if (r.x!=-1)
  engine.movepiece(r,player);

 player=changePlayer(player);
 engine.checkboardmovement(player);

 if (engine.t)
 {
  bool enemy;
  if (player) enemy=false; else enemy=true;
  engine.checkboardmovement(enemy);
  if (engine.t)
  {
   int ms[2];
   engine.checkboardmovement(0);
   engine.countm();
   ms[0]=engine.qtm;
   engine.checkboardmovement(1);
   engine.countm();
   ms[1]=engine.qtm;

   if (firstplayer)
    return ms[1]-ms[0];
   else
    return ms[0]-ms[1];
  }
  else
   return MinimaxH4(firstplayer,limit,position(-1,-1,NULL),player,engine.b,height,alpha,beta);
 }
 else
 {
  int temp;
  if (firstplayer==player)
  {
   temp=-100;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=MinimaxH4(firstplayer,limit,position(i,j,engine.b[i][j].d),player,engine.b,height,alpha,beta);
      if (temp<temp2)
      {
       temp=temp2;
       alpha=temp;
       if (temp>beta)
        return temp;
      }
     }
  }
  else
  {
   temp=100;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=MinimaxH4(firstplayer,limit,position(i,j,engine.b[i][j].d),player,engine.b,height,alpha,beta);
      if (temp>temp2)
      {
       temp=temp2;
       beta=temp;
       if (temp<alpha)
        return temp;
      }
     }
  }
  return temp;
 }
}

int Minimax_FA::AlfaBeta(bool firstplayer, position r, bool player, pe tempboard[size][size])
{
 boards engine(tempboard);

 if (r.x!=-1)
  engine.movepiece(r,player);

 player=changePlayer(player);
 engine.checkboardmovement(player);

 if (engine.t)
 {
  bool enemy;
  if (player) enemy=false; else enemy=true;
  engine.checkboardmovement(enemy);
  if (engine.t)
  {
   engine.count();
   if (engine.ps[0]==engine.ps[1])
    return 0;
   else if (firstplayer)
   {
    if (engine.ps[0]>engine.ps[1])
     return -1;
    else
     return 1;
   }
   else
   {
    if (engine.ps[0]>engine.ps[1])
     return 1;
    else
     return -1;
   }
  }
  else
   return AlfaBeta(firstplayer,position(-1,-1,NULL),player,engine.b);
 }
 else
 {
  int temp;
  if (firstplayer==player)
  {
   temp=-2;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=AlfaBeta(firstplayer,position(i,j,engine.b[i][j].d),player,engine.b);
      if (temp2==1)
       return 1;
      if (temp<temp2)
       temp=temp2;
     }
  }
  else
  {
   temp=2;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=AlfaBeta(firstplayer,position(i,j,engine.b[i][j].d),player,engine.b);
      if (temp2==-1)
       return -1;
      if (temp>temp2)
       temp=temp2;
     }
  }
  return temp;
 }
}
