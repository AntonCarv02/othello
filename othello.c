#include <stdio.h>
#include "othello_func.h"


int main(){

    char board[8][8];
    
    
    printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Pretas (x).\n\n");

    
    init_board(board);
    
    print_board(board);

    play(board,2,1,'x');

    return 0;
}       
    