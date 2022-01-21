#include <stdio.h>
#include "othello_func.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOARD_SIZE 8


//-----------------------------
// função init_board - Inicializa o tabuleiro (parâmetro board) com as peças brancas e pretas iniciais.
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
//-----------------------------
void init_board (char board[BOARD_SIZE][BOARD_SIZE]){

    for(int l=0;l<BOARD_SIZE;l++){

        for(int c=0;c<BOARD_SIZE;c++){
        
            board[l][c]='.';
        }
    }

    board[3][3]='o';
    board[3][4]='x';
    board[4][4]='o';
    board[4][3]='x';
}


//-----------------------------
// função print_board - mostra o tabuleiro atual no standard output (ecrã).
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
//-----------------------------
void print_board(char board[BOARD_SIZE][BOARD_SIZE]){

    printf("\n\t  A B C D E F G H\n");
    for(int l=0;l<BOARD_SIZE;l++){

        printf("\t%d ",(l+1));

        for(int c=0;c<BOARD_SIZE;c++){

            printf("%c ", board[l][c]);
        }
        printf("\n");
    }    
    printf("\n");
}


//-----------------------------
// função verif_gameover - verifica se o jogo chegou ao fim de acordo com as regras,
// se o tabuleiro esta cheio ou se nenhum dos jogadores tem jogadas validas possiveis
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// player - cor do utilizador
// movespossible - verifica se existem jogadas possiveis de ambas as cores, 1 se sim, 0 se não
// valor de retorno:
// 1 se o jogo acabou, 0 se pode continuar, inteiro
//-----------------------------
int verif_gameover(char board[BOARD_SIZE][BOARD_SIZE], char player, int movespossible){

    int l,c,count_x=0,count_o=0;
    char winner;


    for(l=0; l<BOARD_SIZE; l++){
        for(c=0; c<BOARD_SIZE; c++){

            count_x+=(board[l][c]=='x');
            count_o+=(board[l][c]=='o');
        }
    }
    
    
    if((count_o+count_x==64)||!movespossible){
        
        printf("\n\tGAME OVER!\nPretas: %d, Brancas: %d\n",count_x,count_o);
        
        if(count_o>count_x){
            winner = 'o';

        }else if(count_o<count_x){
            winner = 'x';

        }else if(count_o==count_x){
            winner = 't';

        }


        if(winner==player){
            printf("Ganhou!\n\n");

        } else if(winner==getTurn(player)){
            printf("Perdeu! Better luck next time.\n\n");

        } else{
            printf("Empate!\n\n");
        }

        return 1;
    }

    return 0;    
}


//-----------------------------
// função playerColor - escolhe a cor do jogador no inicio do jogo
//
// Valor de retorno:
// cor do utlilizador, caracter
//-----------------------------
char playerColor (){
    
    srand(time(NULL));
    
    char color;
    int n=(rand()%2);


    if(n==0){
        color = 'x';
        printf("\n----------- JOGO OTHELLO -----------\n\nAs suas peças são as Pretas (x).\n\n");

    } else if (n==1){
        color = 'o';
        printf("\n----------- JOGO OTHELLO -----------\n\nAs suas peças são as Brancas (o).\n\n");
    }

    return color;
}


//-----------------------------
// função getTurn - recebe a cor turn e devolve a cor do oponente
//
// argumentos:
// turn - jogador atual
// Valor de retorno:
// cor do oponente, caracter
//-----------------------------
char getTurn (char turn){
    
    if(turn == 'x'){
        turn ='o';
    } else if(turn == 'o'){
        turn ='x';
    }

    return turn;
}


//-----------------------------
// função getMove - recebe a jogada do utilizador e verifica se é valida
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// color - cor do utilizador
//-----------------------------
void getMove(char board[BOARD_SIZE][BOARD_SIZE], char color){

    int line, col, count;
    char col_char;

    
    do{ 
        printf("%c - ",color);
        printf("Insira a sua jogada  (formato ex - 4C): ");
        scanf("%d%c", &line, &col_char);

        col= col_char - 'A';
        line--;

        if ((col<0||col>BOARD_SIZE-1) || (line<0||line>BOARD_SIZE-1) || ( board[line][col]!='.')){
            printf("\nPosição Inválida! Tente novamente.\n\n");
            continue;
        }


        count=flanked(board,line,col,color);
        
        if(!count){
            printf("\nJogada Inválida! Tente novamente.\n\n");
            continue;
        }
    
    } while ((!count) || ((col<0||col>BOARD_SIZE-1) || (line<0||line>BOARD_SIZE-1) || ( board[line][col]!='.')));
        
    
    play(board, line, col,color);
}


//-----------------------------
// função play - coloca uma peça de cor color na posição (line, col) e vira
// as peças do oponente de acordo com as regras indicadas na descrição do jogo.
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
// color - qual jogador está a fazer a jogada
//-----------------------------
void play(char board[BOARD_SIZE][BOARD_SIZE],int line,int col,char color ){

    board[line][col]=color;
    int count=0, coluna, linha;


    printf("Jogada - %c\n", color);

    for(int l=-1; l<2; l++){
        for(int c=-1; c<2; c++){

            if((l!=0)||(c!=0)){

                count=count_flips_dir(board,line,col,color,l,c);
                //printf(" play c%d \n",count);
                
                coluna=col+c;
                linha=line+l;
                
                while(count){
                    
                    board[linha][coluna]=color;                            
                    count--;
                    linha+=l;
                    coluna+=c;
                }                                                
            }         
        }
    }
}


//-----------------------------
// função flanked - Conta o número de peças viradas ao jogar numa certa linha ou coluna.
// Se a jogada for inválida retorna zero.
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
// color - que jogador está a fazer a jogada
// Valor de retorno:
// soma das peças viradas em todas as direçoes numa jogada, inteiro
//-----------------------------
int flanked( char board[BOARD_SIZE][BOARD_SIZE], int line,int col,char color ){

   int count,soma=0;
   
    for(int l=-1; l<2; l++){
        for(int c=-1; c<2; c++){

            if((l!=0)||(c!=0)){

                count=count_flips_dir(board,line,col,color,l,c);
                soma+=count;
                //printf(" flanked c%d s%d\n",count,soma);

            }         
        }
    }
    return soma;
}


//-----------------------------
// função count_flips_dir - Conta quantas peças serão viradas, numa certa linha, coluna e diagonal.
//(definida por delta_line e delta_col, por exemplo se delta_line=1 e
//delta_col=1, estamos a considerar a direção “baixo-direita”)
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
// color - que jogador está a fazer a jogada
// delta_line - percorrer a linha na direção desejada
// delta_col - percorrer a coluna na direção desejada
// Valor de retorno:
// numero de peças possiveis virar numa direção, 0 se invalido, inteiro
//-----------------------------
int count_flips_dir(char board[BOARD_SIZE][BOARD_SIZE], int line, int col ,char color ,int delta_line , int delta_col){

    int count_opponent=0;
    int l=line,c=col;
    char opponent;
    

    opponent=getTurn(color);
    

    while(( (l+delta_line>=0) && (l+delta_line<BOARD_SIZE) )&&((c+delta_col>=0) && (c+delta_col<BOARD_SIZE))){

        count_opponent+=(board[l][c]==opponent);        
        //printf("countflip l:%d c:%d count:%d",l,c,count_opponent);


        if((board[(l+delta_line)][(c+delta_col)])==color){
            
            return count_opponent;

        }else if((board[(l+delta_line)][(c+delta_col)]=='.')){

            return 0;

        } 
        
        c+=delta_col;
        l+=delta_line;        
    }
    return 0;
}


//-----------------------------
// função movesPossible- verifica se existem jogadas possiveis para o jogador
// atual(color).
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// color - que jogador está a fazer a jogada
// Valor de retorno:
// numero de posições validas para jogar,inteiro
//-----------------------------
int movesPossible(char board[BOARD_SIZE][BOARD_SIZE], char color){

    int count_possible=0;
    
    
    for (int l=0;l<BOARD_SIZE;l++){
        for(int c=0;c<BOARD_SIZE;c++){

            if(board[l][c]=='.'){

                if(flanked(board, l, c, color)){

                    count_possible++;
                }
            }
        }
    }

    return count_possible;
}


//--------------------------------GREEDY BOT-------------------------
// função getMoveBot - cria uma matriz com as jogadas possiveis fazer pelo computador
// e escolhe a posiçao que vira mais peças
//
// argumentos:
// board[BOARD_SIZE][BOARD_SIZE]- tabuleiro de jogo, matriz de caracteres 8*8
// color - cor do computador
//-----------------------------
void getMoveBot(char board[BOARD_SIZE][BOARD_SIZE], char color){

    int line, col, count_board[BOARD_SIZE][BOARD_SIZE], count, max=1;
    
    
    memset(count_board,0,sizeof(count_board));
    

    for (int l=0;l<BOARD_SIZE;l++){
        for(int c=0;c<BOARD_SIZE;c++){

            if(board[l][c]=='.'){

                count=flanked(board, l, c, color);
                count_board[l][c]=count;
            }
        }
    }

    
    for (int l=0;l<BOARD_SIZE;l++){
        for(int c=0;c<BOARD_SIZE;c++){

            if(max<=count_board[l][c]){

                max=count_board[l][c];
                line=l;
                col=c;
            }
        }
    }

    play(board, line, col, color);
}
