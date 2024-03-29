#define BOARD_SIZE 8
#define EMPTY '.'
#define WHITE 'o'
#define BLACK 'x'

void init_board (char board[8][8]);

void print_board(char board[8][8]);

char playerColor();

void play(char board[8][8],int line,int  col,char color );

int flanked( char board[8][8], int line,int col,char color );

int count_flips_dir(char board[8][8], int line, int col ,char color ,int delta_line , int delta_col);

int verif_gameover(char board[8][8], char player,int movespossible);

void getMove(char board[8][8], char color);

char getTurn (char color);

void getMoveBot(char board[8][8], char color);

int movesPossible(char board[8][8], char color);
