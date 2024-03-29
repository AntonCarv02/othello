#include <stdio.h>
#include "othello_func.h"
#include <stdlib.h>


int main( int argc, char * argv[]){

    char board[8][8], turn=BLACK, player_color;
    int check_possiblemove;

    if(argc==1){


        init_board(board);


        player_color=playerColor();

        print_board(board);            
            
        check_possiblemove=movesPossible(board,turn);


        while(!verif_gameover(board, player_color, check_possiblemove)){

            check_possiblemove=movesPossible(board,turn);

            if( !check_possiblemove){

                turn=getTurn(turn);
                check_possiblemove=movesPossible(board,turn);

                if( !check_possiblemove){
                    continue;
                }
            }

            if((player_color==turn)){

                getMove(board, turn);
                print_board(board);
                turn=getTurn(turn);

            } else if((player_color!=turn)){

                getMoveBot(board, turn);
                print_board(board);
                turn=getTurn(turn);

            }
        }


    } else if(argc==2){


        FILE *f=fopen( argv[1], "r");
        int filecol, fileline;
        char filecol_char;        
        
        init_board(board);

        
        if(!(f==NULL)){


            player_color=playerColor();
            check_possiblemove=movesPossible(board,turn);

            
            while(!verif_gameover(board, player_color, check_possiblemove)){
                
                fscanf( f, "%d%c", &fileline, &filecol_char);

                filecol=filecol_char-'A';

                fileline--;
                //printf("l%d c%d\n",fileline,filecol);
                
                
                play(board,fileline,filecol,turn);
                turn=getTurn(turn);

                if(fgetc(f)==EOF){
                    break;
                }
            }

            fclose(f);
            print_board(board);


        } else {


            printf("\nNão foi possivel abrir o ficheiro!\n");
            

            player_color=playerColor();

            print_board(board);
            
            check_possiblemove=movesPossible(board,turn);

        }

        
        while(!verif_gameover(board, player_color, check_possiblemove)){

            check_possiblemove=movesPossible(board,turn);

            if( !check_possiblemove){

                turn=getTurn(turn);
                check_possiblemove=movesPossible(board,turn);

                if( !check_possiblemove){
                    continue;
                }
            }

            if((player_color==turn)){

                getMove(board, turn);
                print_board(board);
                turn=getTurn(turn);

            } else if((player_color!=turn)){

                getMoveBot(board, turn);
                print_board(board);
                turn=getTurn(turn);

            }
        }
        

    } else if (argc>2){


        printf("\nInválido!\n\n");

    }
        
    return 0;
}       
    