#include <stdlib.h>
#include <stdio.h>

#include "ai.c"
#include "tictactoe.h"

void clear_screen() {
   #ifdef __unix__
   system("clear");
   #elif _WIN32
   system("cls");
   #endif
}

void make_a_turn(T3Board * board) {
     char   move[3];
     T3Move move_status;

     printf(">> ");
     scanf("%2s", move);
     move_status = t3_set(board, move, t3_get_turn(board));

     switch(move_status) {
        case INVALID_COORD:
           puts("Invalid coordinates!");
           make_a_turn(board);
        break;
        case INVALID_VALUE:
           puts("Invalid symbol!");
           make_a_turn(board);
        break;
        case INVALID_MOVE:
           puts("You can't play there!");
           make_a_turn(board);
        break;
        case NOT_YOUR_TURN:
           puts("Not your turn");
           make_a_turn(board);
        break;
        case SUCCESS:
           puts("OK!");
        break;
     }
}

int main() {
   T3Board * board = t3_create();
   T3Status status = t3_gamestatus(board);
   clear_screen();

   while(status == GAME_IN_PROGRESS) {
     t3_print(board);
     if(t3_get_turn(board) == 'O') {
        make_a_turn(board);
     } else {
        t3_set_pos(board, t3_ai_bestmove(board), 'X');
     }
     status = t3_gamestatus(board);
     clear_screen();
   }

   t3_print(board);
   switch(status) {
     case X_WINS: puts("X wins!");
     break;
     case O_WINS: puts("O wins!");
     break;
     case DRAW:   puts("This game is a draw!");
     break;
     case GAME_IN_PROGRESS:
     break;
   }

   t3_free(board);
   return 0;
}
