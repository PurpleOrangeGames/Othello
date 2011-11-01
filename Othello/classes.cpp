#include <QtCore>

#ifndef classes_H
#define classes_H

#define size 8

//Estrutura utilizada para montar o tabuleiro:
//p indica o jogador em uma posição do tabuleiro.
//0 para peça branca, 1 para peça preta e 2 para posição vazia.
//d[8] indica possiveis movimentos a partir desta posição do tabuleiro.
//m indica se há possivel movimento, no momento em que eh registrado
//pelo menos um movimento em d[8], o flag m é acionado.
struct pe
{
 int p, d[8];
 bool m;
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

  boards()//Inicializa as variaveis e o tabuleiro.
  {
   t=false;
   qtm=0;
   clear();
   clearm();
   ps[0]=0;
   ps[1]=0;
  }

  void copy(pe tb[size][size])//Copia as peças de um outro tabuleiro para este.
  {
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     b[i][j].p=tb[i][j].p;
  }

  void count()//Conta a quantidade de peças de cada jogador.
  {
   ps[0]=0;
   ps[1]=0;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (b[i][j].p==0)
      ps[0]++;
     else if (b[i][j].p==1)
      ps[1]++;
  }

  void countm()//Conta a quantidade de possíveis movimentos de cada jogador.
  {
   qtm=0;
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (b[i][j].m)
      qtm++;
  }

  void clear()//Limpa o tabuleiro tirando todas as peças.
  {
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     b[i][j].p=2;
  }

  void clearm()//Limpa os possíveis movimentos de todas as peças.
  {
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
    {
     b[i][j].m=false;
     for (int k=0;k<8;k++)
      b[i][j].d[k]=0;
    }
  }

  void start()//Limpa o tabuleiro e repõe as peças iniciais.
  {
   t=false;
   clear();
   clearm();
   b[(size/2)-1][(size/2)-1].p=1;
   b[size/2][size/2].p=1;
   b[(size/2)-1][size/2].p=0;
   b[size/2][(size/2)-1].p=0;
   ps[0]=0;
   ps[1]=0;
  }

  void checkturn()//Verifica a quantidade de possíveis movimentos para saber se deve passar o turno ou não.
  {
   t=true;
   for (int i=0;i<size && t==true;i++)
    for (int j=0;j<size && t==true;j++)
     if (b[i][j].m)
      t=false;
  }

  void checkboardmovement(int p)//Verifica os possíveis movimentos de um jogador dado.
  {
   clearm();
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (b[i][j].p==p)
     {
      int k, l, e;
      if (p==0) e=1; else e=0;

      for (l=-1;i+l>-1 && b[i+l][j].p==e;l--);
      if (i+l>-1 && l<-1 && b[i+l][j].p==2)
      { b[i+l][j].d[0]=-l; b[i+l][j].m=true; }

      for (k=1, l=-1;j+k<size && i+l>-1 && b[i+l][j+k].p==e;k++, l--);
      if (j+k<size && i+l>-1 && k>1 && b[i+l][j+k].p==2)
      { b[i+l][j+k].d[1]=k; b[i+l][j+k].m=true; }

      for (k=1;j+k<size && b[i][j+k].p==e;k++);
      if (j+k<size && k>1 && b[i][j+k].p==2)
      { b[i][j+k].d[2]=k; b[i][j+k].m=true; }

      for (k=1, l=1;j+k<size && i+l<size && b[i+l][j+k].p==e;k++, l++);
      if (j+k<size && i+l<size && k>1 && b[i+l][j+k].p==2)
      { b[i+l][j+k].d[3]=k; b[i+l][j+k].m=true; }

      for (l=1;i+l<size && b[i+l][j].p==e;l++);
      if (i+l<size && l>1 && b[i+l][j].p==2)
      { b[i+l][j].d[4]=l; b[i+l][j].m=true; }

      for (k=-1, l=1;j+k>-1 && i+l<size && b[i+l][j+k].p==e;k--, l++);
      if (j+k>-1 && i+l<size && l>1 && b[i+l][j+k].p==2)
      { b[i+l][j+k].d[5]=l; b[i+l][j+k].m=true; }

      for (k=-1;j+k>-1 && b[i][j+k].p==e;k--);
      if (j+k>-1 && k<-1 && b[i][j+k].p==2)
      { b[i][j+k].d[6]=-k; b[i][j+k].m=true; }

      for (k=-1, l=-1;j+k>-1 && i+l>-1 && b[i+l][j+k].p==e;k--, l--);
      if (j+k>-1 && i+l>-1 && k<-1 && b[i+l][j+k].p==2)
      { b[i+l][j+k].d[7]=-k; b[i+l][j+k].m=true; }
     }
   checkturn();
  }

  void movepiece(int d[8], int x, int y, int p)//Move a peça
  {
   int i, j;
   if (d[0]>0) for (i=1; i<d[0]; i++) b[x+i][y].p=p;
   if (d[1]>0) for (i=1,j=-1; i<d[1]; i++,j--) b[x+i][y+j].p=p;
   if (d[2]>0) for (j=-1; -j<d[2]; j--) b[x][y+j].p=p;
   if (d[3]>0) for (i=-1,j=-1; -i<d[3]; i--,j--) b[x+i][y+j].p=p;
   if (d[4]>0) for (i=-1; -i<d[4]; i--) b[x+i][y].p=p;
   if (d[5]>0) for (i=-1,j=1; j<d[5]; i--,j++) b[x+i][y+j].p=p;
   if (d[6]>0) for (j=1; j<d[6]; j++) b[x][y+j].p=p;
   if (d[7]>0) for (i=1,j=1; i<d[7]; i++,j++) b[x+i][y+j].p=p;
   b[x][y].p=p;
  }

  void undomovement(int d[8], int x, int y, int p)
  {
   int i, j, e;
   if (p==0) e=1; else e=0;
   if (d[0]>0) for (i=1; i<d[0]; i++) b[x+i][y].p=e;
   if (d[1]>0) for (i=1,j=-1; i<d[1]; i++,j--) b[x+i][y+j].p=e;
   if (d[2]>0) for (j=-1; -j<d[2]; j--) b[x][y+j].p=e;
   if (d[3]>0) for (i=-1,j=-1; -i<d[3]; i--,j--) b[x+i][y+j].p=e;
   if (d[4]>0) for (i=-1; -i<d[4]; i--) b[x+i][y].p=e;
   if (d[5]>0) for (i=-1,j=1; j<d[5]; i--,j++) b[x+i][y+j].p=e;
   if (d[6]>0) for (j=1; j<d[6]; j++) b[x][y+j].p=e;
   if (d[7]>0) for (i=1,j=1; i<d[7]; i++,j++) b[x+i][y+j].p=e;
   b[x][y].p=2;
  }
};

struct result//Estrutura de resultado do minimax
{
 int d[8], x, y;
};

class reversi//Classe que gerencia o jogo Othello / Reversi.
{
 private:
  bool CurrentPlayer, shouldChangeTurn, shouldEndGame;
  int gamePlayer1Win, gamePlayer2Win, gameDraw;
 public:
  boards engine;

  reversi();

  void CheckTurn();

  void Player(int X, int Y);

  void AI_Random();

  void AI_Minimax(int type, int difficult);
};

reversi Projeto;

class Minimax_FA//Minimax com função de avaliação
{
 public:
  Minimax_FA()
  {

  }

  result Minimax(bool player, pe tempboard[size][size], int type, int difficult, reversi *tempProjeto)
  {
   boards engine;
   firstplayer=player;
   engine.copy(tempboard);
   engine.checkboardmovement(player);
   Projeto=tempProjeto;

   int temp=-100;
   result r;

   limit=difficult;//Limite d emovimentos que podem ser feitos antes do Minimax parar e voltar o resultado

   engine.countm();//Conta a quantidade de possíveis movimentos

   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
     if (engine.b[i][j].m)
     {
      int temp2=0;
      engine.count();//Conta a quantidade de peças no tabuleiro
      if (engine.ps[0]+engine.ps[1]<51)//Se não estiver acabando o jogo, faça Minimax Heuristico
      {
       if (type==0) temp2=MinimaxH1(engine.b[i][j].d,i,j,player,engine.b,0);
       else if (type==1) temp2=MinimaxH4(engine.b[i][j].d,i,j,player,engine.b,0,-100,100);
      }
      else//Se estiver acabando o jogo, faça Minimax Completo
      {
       temp2=AlfaBeta(engine.b[i][j].d,i,j,player,engine.b);
       if (temp2==1)//Se for possível vencer, faça este movimento
       {
        r.x=i; r.y=j; r.d[0]=engine.b[i][j].d[0]; r.d[1]=engine.b[i][j].d[1];
        r.d[2]=engine.b[i][j].d[2]; r.d[3]=engine.b[i][j].d[3]; r.d[4]=engine.b[i][j].d[4];
        r.d[5]=engine.b[i][j].d[5]; r.d[6]=engine.b[i][j].d[6]; r.d[7]=engine.b[i][j].d[7];
        return r;
       }
      }

      if (temp<temp2)//Verifica melhor resultado e deixe o melhor movimento armazenado
      {
       temp=temp2;
       r.x=i; r.y=j; r.d[0]=engine.b[i][j].d[0]; r.d[1]=engine.b[i][j].d[1];
       r.d[2]=engine.b[i][j].d[2]; r.d[3]=engine.b[i][j].d[3]; r.d[4]=engine.b[i][j].d[4];
       r.d[5]=engine.b[i][j].d[5]; r.d[6]=engine.b[i][j].d[6]; r.d[7]=engine.b[i][j].d[7];
      }
      if ((type==0 || type==1) && temp==1)//Se houver chance de vencer, pode parar
       return r;
     }
   return r;//Senão retorne o melhor resultado encontrado
  }

 private:
  bool firstplayer;
  int limit;
  reversi *Projeto;

  int MinimaxH1(int d[8], int x, int y, bool player, pe tempboard[size][size], int height)
  {
   boards engine;
   engine.copy(tempboard);

   height++;
   if (height>limit)
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

   if (x!=-1)
    engine.movepiece(d,x,y,player);

   if (player)
    player=false;
   else
    player=true;
   engine.checkboardmovement(player);

   if (engine.t)
   {
    bool enemy;
    if (player)
     enemy=false;
    else
     enemy=true;
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
     return MinimaxH1(NULL,-1,-1,player,engine.b,height);
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
        int temp2=MinimaxH1(engine.b[i][j].d,i,j,player,engine.b,height);
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
        int temp2=MinimaxH1(engine.b[i][j].d,i,j,player,engine.b,height);
        if (temp2==-1)
         return -1;
        if (temp>temp2)
         temp=temp2;
       }
    }
    return temp;
   }
  }

  int MinimaxH4(int d[8], int x, int y, bool player, pe tempboard[size][size], int height, int alpha, int beta)
  {
   boards engine;
   engine.copy(tempboard);

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

   if (x!=-1)
    engine.movepiece(d,x,y,player);

   if (player)
    player=false;
   else
    player=true;
   engine.checkboardmovement(player);

   if (engine.t)
   {
    bool enemy;
    if (player)
     enemy=false;
    else
     enemy=true;
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
     return MinimaxH4(NULL,-1,-1,player,engine.b,height,alpha,beta);
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
        int temp2=MinimaxH4(engine.b[i][j].d,i,j,player,engine.b,height,alpha,beta);
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
        int temp2=MinimaxH4(engine.b[i][j].d,i,j,player,engine.b,height,alpha,beta);
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

  int AlfaBeta(int d[8], int x, int y, bool player, pe tempboard[size][size])
  {
   boards engine;
   engine.copy(tempboard);

   if (x!=-1)
    engine.movepiece(d,x,y,player);

   if (player)
    player=false;
   else
    player=true;
   engine.checkboardmovement(player);

   if (engine.t)
   {
    bool enemy;
    if (player)
     enemy=false;
    else
     enemy=true;
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
     return AlfaBeta(NULL,-1,-1,player,engine.b);
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
        int temp2=AlfaBeta(engine.b[i][j].d,i,j,player,engine.b);
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
        int temp2=AlfaBeta(engine.b[i][j].d,i,j,player,engine.b);
        if (temp2==-1)
         return -1;
        if (temp>temp2)
         temp=temp2;
       }
    }
    return temp;
   }
  }
};

reversi::reversi()
{
 srand(time(NULL));
 CurrentPlayer=false; //Jogador
 shouldChangeTurn=false; //Flag para passar o turno
 shouldEndGame=false; //Flag para fim de jogo
 gamePlayer1Win=0;  //Contador de vitórias do jogador 1
 gamePlayer2Win=0;  //Contador de vitórias do jogador 2
 gameDraw=0;  //Contador de empates
}

  void reversi::CheckTurn()//Função que troca o jogador, verifica se deve passar o turno e se deve terminar o jogo
  {
   if (CurrentPlayer) CurrentPlayer=false; else CurrentPlayer=true;//Troca o jogador
   engine.checkboardmovement(CurrentPlayer);//Verifica Movimento
   shouldChangeTurn=false;
   if (engine.t)//Sem movimentos, passa o turno
   {
    shouldChangeTurn=true;
    if (CurrentPlayer) CurrentPlayer=false; else CurrentPlayer=true;//Troca o jogador
    engine.checkboardmovement(CurrentPlayer);//Verifica Movimento
    if (engine.t)//Sem movimentos novamente, termina o jogo
    {
     shouldChangeTurn=false;
     shouldEndGame=true;
     engine.count();
     if (engine.ps[0]==engine.ps[1]) gameDraw++;//Empate
     else if (engine.ps[0]>engine.ps[1]) gamePlayer1Win++;//Jogador 1 venceu
     else if (engine.ps[0]<engine.ps[1]) gamePlayer2Win++;//Jogador 2 venceu
    }
   }
  }

  void reversi::Player(int X, int Y)//Função responsável para administrar as ações do jogador
  {
   engine.checkboardmovement(CurrentPlayer);//Verifica possíveis movimentos do jogador
   if (engine.b[X][Y].m)//Se o movimento pedido existe, mova a peça
   {
    engine.movepiece(engine.b[X][Y].d,X,Y,CurrentPlayer);//Mova a peça
    CheckTurn();//Passe o turno
   }
  }

  void reversi::AI_Random()//Função responsável para administrar as ações do oponente randômico.
  {
   engine.checkboardmovement(CurrentPlayer);//Verifica possíveis movimentos do jogador
   engine.countm();//Conta a quantidade de possíveis movimentos
   int rand_temp=(rand()%engine.qtm)+1, qty=0;// Gera numero randomico
   for (int i=0;i<size;i++)
    for (int j=0;j<size;j++)
    {
     if (engine.b[i][j].m) qty++;//Proximo possível movimento
     if (rand_temp==qty)//Acha o numero randomico dentro dos possiveis movimentos
     {
      engine.movepiece(engine.b[i][j].d,i,j,CurrentPlayer);//Move a peça
      CheckTurn();//Passa o turno
      return;//Retorna
     }
    }
  }

  void reversi::AI_Minimax(int type, int difficult)//Função responsável por direcionar o jogo a função minimax desejada.
  {
   engine.checkboardmovement(CurrentPlayer);//Verifica possíveis movimentos do jogador
   Minimax_FA AI;//Cria uma instancia do Minimax
   result r=AI.Minimax(CurrentPlayer,engine.b,type,difficult,&Projeto);//Pega o resultado do melhor movimento
   engine.movepiece(r.d,r.x,r.y,CurrentPlayer);//Move a peça
   CheckTurn();//Passa o turno
  }

#endif
