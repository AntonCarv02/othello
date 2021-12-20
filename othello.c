#include <stdio.h>
#include "othello_func.h"


int main( int argc){

    char board[8][8], turn;
    
    
    printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Pretas (x).\n\n");

    
    init_board(board);
    
    print_board(board);

    while(!verif_gameover(board)){
        
        //turn = ;
        getMove(board, turn);
    }

    return 0;
}       
    