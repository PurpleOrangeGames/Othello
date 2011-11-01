#include "Othello.h"

boards::boards()//Inicializa as variaveis e o tabuleiro.
{
 reset();
}

boards::boards(pe tb[size][size])
{
 reset();
 copy(tb);
}

void boards::reset()
{
 t=shouldNotPassTurn;
 qtm=0;
 clear();
 clearm();
 ps[0]=0;
 ps[1]=0;
}

void boards::copy(pe tb[size][size])//Copia as peças de um outro tabuleiro para este.
{
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   b[i][j].player=tb[i][j].player;
}

void boards::count()//Conta a quantidade de peças de cada jogador.
{
 ps[0]=0;
 ps[1]=0;
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   if (b[i][j].player==whitePiece)
    ps[0]++;
   else if (b[i][j].player==blackPiece)
    ps[1]++;
}

void boards::countm()//Conta a quantidade de possíveis movimentos de cada jogador.
{
 qtm=0;
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   if (b[i][j].m==hasMovement)
    qtm++;
}

void boards::clear()//Limpa o tabuleiro tirando todas as peças.
{
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   b[i][j].player=noPiece;
}

void boards::clearm()//Limpa os possíveis movimentos de todas as peças.
{
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
  {
   b[i][j].m=noMovement;
   for (int k=0;k<8;k++)
    b[i][j].d[k]=0;
  }
}

void boards::start()//Limpa o tabuleiro e repõe as peças iniciais.
{
 t=shouldNotPassTurn;
 clear();
 clearm();
 b[(size/2)-1][(size/2)-1].player=blackPiece;
 b[size/2][size/2].player=blackPiece;
 b[(size/2)-1][size/2].player=whitePiece;
 b[size/2][(size/2)-1].player=whitePiece;
 ps[0]=0;
 ps[1]=0;
 checkboardmovement(0);
}

void boards::checkturn()//Verifica a quantidade de possíveis movimentos para saber se deve passar o turno ou não.
{
 t=shouldPassTurn;
 for (int i=0;i<size && t==shouldPassTurn;i++)
  for (int j=0;j<size && t==shouldPassTurn;j++)
   if (b[i][j].m==hasMovement)
    t=shouldNotPassTurn;
}

void boards::checkboardmovement(int p)//Verifica os possíveis movimentos de um jogador dado.
{
 clearm();
 for (int i=0;i<size;i++)
  for (int j=0;j<size;j++)
   if (b[i][j].player==p)
   {
    int k, l, e;
    if (p==player1White) e=player2Black; else e=player1White;

    for (l=-1;i+l>-1 && b[i+l][j].player==e;l--);
    if (i+l>-1 && l<-1 && b[i+l][j].player==noPiece)
    { b[i+l][j].d[0]=-l; b[i+l][j].m=hasMovement; }

    for (k=1, l=-1;j+k<size && i+l>-1 && b[i+l][j+k].player==e;k++, l--);
    if (j+k<size && i+l>-1 && k>1 && b[i+l][j+k].player==noPiece)
    { b[i+l][j+k].d[1]=k; b[i+l][j+k].m=hasMovement; }

    for (k=1;j+k<size && b[i][j+k].player==e;k++);
    if (j+k<size && k>1 && b[i][j+k].player==noPiece)
    { b[i][j+k].d[2]=k; b[i][j+k].m=hasMovement; }

    for (k=1, l=1;j+k<size && i+l<size && b[i+l][j+k].player==e;k++, l++);
    if (j+k<size && i+l<size && k>1 && b[i+l][j+k].player==noPiece)
    { b[i+l][j+k].d[3]=k; b[i+l][j+k].m=hasMovement; }

    for (l=1;i+l<size && b[i+l][j].player==e;l++);
    if (i+l<size && l>1 && b[i+l][j].player==noPiece)
    { b[i+l][j].d[4]=l; b[i+l][j].m=hasMovement; }

    for (k=-1, l=1;j+k>-1 && i+l<size && b[i+l][j+k].player==e;k--, l++);
    if (j+k>-1 && i+l<size && l>1 && b[i+l][j+k].player==noPiece)
    { b[i+l][j+k].d[5]=l; b[i+l][j+k].m=hasMovement; }

    for (k=-1;j+k>-1 && b[i][j+k].player==e;k--);
    if (j+k>-1 && k<-1 && b[i][j+k].player==noPiece)
    { b[i][j+k].d[6]=-k; b[i][j+k].m=hasMovement; }

    for (k=-1, l=-1;j+k>-1 && i+l>-1 && b[i+l][j+k].player==e;k--, l--);
    if (j+k>-1 && i+l>-1 && k<-1 && b[i+l][j+k].player==noPiece)
    { b[i+l][j+k].d[7]=-k; b[i+l][j+k].m=hasMovement; }
   }
 checkturn();
}

void boards::movepiece(position r, int p)//Move a peça
{
 int i, j;
 if (r.d[0]>0) for (i=1; i<r.d[0]; i++) b[r.x+i][r.y].player=p;
 if (r.d[1]>0) for (i=1,j=-1; i<r.d[1]; i++,j--) b[r.x+i][r.y+j].player=p;
 if (r.d[2]>0) for (j=-1; -j<r.d[2]; j--) b[r.x][r.y+j].player=p;
 if (r.d[3]>0) for (i=-1,j=-1; -i<r.d[3]; i--,j--) b[r.x+i][r.y+j].player=p;
 if (r.d[4]>0) for (i=-1; -i<r.d[4]; i--) b[r.x+i][r.y].player=p;
 if (r.d[5]>0) for (i=-1,j=1; j<r.d[5]; i--,j++) b[r.x+i][r.y+j].player=p;
 if (r.d[6]>0) for (j=1; j<r.d[6]; j++) b[r.x][r.y+j].player=p;
 if (r.d[7]>0) for (i=1,j=1; i<r.d[7]; i++,j++) b[r.x+i][r.y+j].player=p;
 b[r.x][r.y].player=p;
}
