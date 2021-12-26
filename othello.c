#include <stdio.h>
#include "othello_func.h"



int main( int argc, char * argv[]){

    char board[8][8], turn;

    
    if(argc==1){

        printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Pretas (x).\n\n");
    
        init_board(board);

        print_board(board);

        while(!verif_gameover(board)){

            //turn = ;
            getMove(board, turn);
        } 

    } else if(argc==2){

        FILE *f=fopen( "jogadas.txt", "r");
        
        
        init_board(board);

        print_board(board);

        while(!verif_gameover(board)){

            //turn = ;
            getMove(board, turn);
        } 
    
    } else if (argc>2){

        printf("Inválido!\n\n");
    }

    

    return 0;
}       
    