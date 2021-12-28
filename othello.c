#include <stdio.h>
#include "othello_func.h"
#include <stdlib.h>


int main( int argc, char * argv[]){

    char board[8][8], turn, filemove[2];

    
    if(argc==1){

        init_board(board);

        printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Pretas (x).\n\n");
        
        print_board(board);
        
        turn = getTurn(turn);
        
        while(!verif_gameover(board)){
            
            getMove(board, turn);
        } 

    } else if(argc==2){

        FILE *f=fopen( "jogadas.txt", "r");
        
        //verificar que abre o ficheiro

        init_board(board);

        //fazer as plays a partir do ficheiro
        while(feof(f)) {
            
            for(int i=0;i<2;i++){
                filemove[i]= fgetc(f);
            }
            
        }

        print_board(board);

        while(!verif_gameover(board)){

            //turn = getTurn;
            getMove(board, turn);
        }

        //fechar o ficheiro jogadas
        fclose(f);

    } else if (argc>2){

        printf("\nInválido!\n\n");
    }
        
    return 0;
}       
    