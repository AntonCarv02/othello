#include <stdio.h>
#include "othello_func.h"
#include <stdlib.h>


//-----------------------------
// função init_board - Inicializa o tabuleiro (parâmetro board) com as peças brancas e pretas iniciais.
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
//-----------------------------
void init_board (char board[8][8]){

    for(int l=0;l<8;l++){

        for(int c=0;c<8;c++){
        
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
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
//-----------------------------
void print_board(char board[8][8]){

    printf("\t  A B C D E F G H\n");
    for(int l=0;l<8;l++){

        printf("\t%d ",l);

        for(int c=0;c<8;c++){

            printf("%c ", board[l][c]);
        }

        printf("\n");
    }
    
    printf("\n");
}


//-----------------------------
// função play - coloca uma peça de cor color na posição (line, col) e vira
// as peças do adversário de acordo com as regras indicadas na descrição do jogo.
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
//-----------------------------
void play(char board[8][8],int line,int  col,char color ){

    int count=flanked(board,line,col,color);

    printf("%d\n",count);

    

    
}


//-----------------------------
// função flanked - Conta o número de peças viradas ao jogar numa certa linha, coluna e diagonal.
//Se a jogada for inválida retorna zero.
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
//-----------------------------
int flanked( char board[8][8], int line,int col,char color ){

    char opponent;

    if(color == 'x'){
        opponent = 'o';

    }else if (color == 'o'){
        opponent= 'x';

    }

    int no=count_flips_dir(board,line,col,opponent,-1,-1);
    int nn=count_flips_dir(board,line,col,opponent,-1,0);
    int ne=count_flips_dir(board,line,col,opponent,-1,1);

    int oo=count_flips_dir(board,line,col,opponent,0,-1);
    int ee=count_flips_dir(board,line,col,opponent,0,1);

    int so=count_flips_dir(board,line,col,opponent,1,-1);
    int ss=count_flips_dir(board,line,col,opponent,1,0);
    int se=count_flips_dir(board,line,col,opponent,1,1);    
    
    return (no+nn+ne+oo+ee+so+ss+se);
}


//-----------------------------
// função count_flips_dir - Conta quantas peças serão viradas, numa certa linha e coluna, e numa certa
//direção (definida por delta_line e delta_col, por exemplo se delta_line=1 e
//delta_col=1, estamos a considerar a direção “baixo-direita”)
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
//-----------------------------
int count_flips_dir(char board[8][8], int line, int col ,char color ,int delta_line , int delta_col){

    int count_opponent=0,l=line,c=col,me;
    

    if(color == 'x'){
        me = 'o';

    }else if (color == 'o'){
        me= 'x';

    }
   
    while( l>=0 &&l<8){
        while(c>=0 && c<8){
        
            count_opponent+=(board[l][c]==color);

            if(board[l+delta_line][c+delta_col]==me){

                return count_opponent;

            }else if((board[l+delta_line][c+delta_col]=='.')){
                
                return 0;
                
            }

            c+=delta_col;
        }
        
        l+=delta_line; 
    }
    
}