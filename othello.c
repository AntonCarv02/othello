#include <stdio.h>
#include "othello_func.h"
#include <stdlib.h>


int main( int argc, char * argv[]){

    char board[8][8], turn;

    
    if(argc==1){


        init_board(board);

        //falta determinar quem fica com as peças pretas, colocar isto na funcao
        printf("\n----------- JOGO OTHELLO -----------\n\n\nAs suas peças são as Pretas (x).\n\n");
        
        print_board(board);

        while(!verif_gameover(board)){
            
            //turn = getTurn(turn);
            getMove(board, turn);
            print_board(board);

        }


    } else if(argc==2){


        FILE *f=fopen( "jogadas.txt", "r");
        int filecol,fileline;
        char filecol_char;
        
        
        init_board(board);

        //verificar que abre o ficheiro
        if(!(f==NULL)){
            
            //fazer as plays a partir do ficheiro
            while(!verif_gameover(board)) {
                
                fscanf( f, "%d%c", &fileline, &filecol_char);

                printf("%c ",filecol_char);
                filecol=filecol_char-'A';

                printf("l%d c%d\n",fileline,filecol);
                
                //turn
                //play(board,fileline,filecol,turn);

                if(fgetc(f)==EOF){
                    break;
                }         
            }

        }else{

            printf("Não foi possivel abrir o ficheiro!\n");
            //ver quem fica com as peças pretas
        }
        

        print_board(board);

        while(!verif_gameover(board)){

            //turn = getTurn(turn);
            getMove(board, turn);
            print_board(board);
        }

        //fechar o ficheiro jogadas
        fclose(f);


    }else if (argc>2){


        printf("\nInválido!\n\n");
    }
        
    return 0;
}       
    