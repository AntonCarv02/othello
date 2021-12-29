#include <stdio.h>
#include "othello_func.h"
#include <stdlib.h>
#include <time.h>


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
/*
    board[3][3]='o';
    board[3][4]='x';
    board[4][4]='o';
    board[4][3]='x';*/

    board[3][3]='x';
    board[3][4]='x';
    board[3][5]='x';
    board[4][4]='o';
    board[4][3]='o';
    board[4][5]='o';
}


//-----------------------------
// função print_board - mostra o tabuleiro atual no standard output (ecrã).
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
//-----------------------------
void print_board(char board[8][8]){

    printf("\n\t  A B C D E F G H\n");
    for(int l=0;l<8;l++){

        printf("\t%d ",(l+1));

        for(int c=0;c<8;c++){

            printf("%c ", board[l][c]);
        }
        printf("\n");
    }    
    printf("\n");
}


//-----------------------------
// função verif_gameover - verifica se o jogo chegou ao fim
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
//-----------------------------
int verif_gameover(char board[8][8]){

    int l,c,count_fill=0;


    for(l=0; l<8; l++){
        for(c=0; c<8; c++){

            count_fill+=(board[l][c]!='.');
        }
    }

    return (count_fill==64);
}


//-----------------------------
// função playerColor - escolhe a cor do jogador
//
// Valor de retorno:
// area calculada, caracter
//-----------------------------
char playerColor (){
    
    srand(time(NULL));
    
    char color;
    int n=(rand()%2);
    printf(" %i",n);

    if(n==0){
        color = 'x';
        printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Pretas (x).\n\n");

    } else if (n==1){
        color = 'o';
        printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Brancas (o).\n\n");
    }

    return color;
}


//-----------------------------
// função getMove - recebe a jogada do jogador color e verifica se é valida
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// color - jogador que está a fazer a jogada
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
// função getMove - recebe a jogada do jogador color e verifica se é valida
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// color - jogador que está a fazer a jogada
//-----------------------------
void getMove(char board[8][8], char color){

    int line, col, count;
    char col_char;

    printf("%c -",color);
    do{ 

        printf("Insira a sua jogada  (formato ex - 4C): ");
        scanf("%d %c", &line, &col_char);

        col= col_char - 'A';
        line--;

        if ((col<0||col>7) || (line<0||line>7) || ( board[line][col]!='.')){
            printf("\nInválido! Tente novamente.\n");
            continue;
        }


        count=flanked(board,line,col,color);
        
        if(!count){
            printf("\nJogada inválida! Tente novamente.\n");
            continue;
        }
    
    } while ((!count) || ((col<0||col>7) || (line<0||line>7) || ( board[line][col]!='.')));
        
    
    play(board, line, col,color);
}


//-----------------------------
// função play - coloca uma peça de cor color na posição (line, col) e vira
// as peças do adversário de acordo com as regras indicadas na descrição do jogo.
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
// color - qual jogador está a fazer a jogada
//-----------------------------
void play(char board[8][8],int line,int  col,char color ){

    board[line][col]=color;
    int count;
   
    printf("\nPLAY\n");
    for(int l=-1; l<2; l++){
        for(int c=-1; c<2; c++){

            if((l!=0)||(c!=0)){

                count=count_flips_dir(board,line,col,color,l,c);
                printf(" c%d, l%d, c%d\n",count,l,c);
                

                while(count){

                    board[line+l][col+c]=color;
                    count--;
                    //line+=l;
                    //col+=c;
                    
                }                
            }         
        }
    }
}


//-----------------------------
// função flanked - Conta o número de peças viradas ao jogar numa certa linha ou coluna.
//Se a jogada for inválida retorna zero.
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
// color - que jogador está a fazer a jogada
//-----------------------------
int flanked( char board[8][8], int line,int col,char color ){

   int count,soma=0;
   
    for(int l=-1; l<2; l++){
        for(int c=-1; c<2; c++){

            if((l!=0)||(c!=0)){

                count=count_flips_dir(board,line,col,color,l,c);
                soma+=count;
                printf(" flanked c%d s%d\n",count,soma);

            }         
        }
    }

    return (soma);
}


//-----------------------------
// função count_flips_dir - Conta quantas peças serão viradas, numa certa linha, coluna e diagonal.
//(definida por delta_line e delta_col, por exemplo se delta_line=1 e
//delta_col=1, estamos a considerar a direção “baixo-direita”)
//
// argumentos:
// board[8][8]- tabuleiro de jogo, matriz de caracteres 8*8
// line - linha da matriz onde foi feita a jogada,inteiro
// col - coluna da matriz onde foi feita a jogada,inteiro
// color - que jogador está a fazer a jogada
// delta_line - percorrer a linha na direção desejada
// delta_col - percorrer a coluna na direção desejada
//-----------------------------
int count_flips_dir(char board[8][8], int line, int col ,char color ,int delta_line , int delta_col){

    int count_opponent=0;
    int l=line,c=col;
    char opponent;
    

    if(color == 'x'){
        opponent = 'o';

    } else if (color == 'o'){
        opponent= 'x';
    }
    

    while(( l>=0 &&l<8 )&&(c>=0 && c<8)){       
        
        printf("countflip l:%d c:%d",l,c);
    
        count_opponent+=(board[l][c]==opponent);        
        

        if((board[(l+delta_line)][(c+delta_col)])==color){

            return count_opponent;

        }else if((board[(l+delta_line)][(c+delta_col)]=='.')){
            
            return 0;            
        }
        
        c+=delta_col;
        l+=delta_line;        
    }
}
