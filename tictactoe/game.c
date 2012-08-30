#include "tictactoe.h"
#include "stdio.h"
#include <stdlib.h>
#include "ai.c"

void clear_screen() {
   #ifdef __unix__
   //system("clear");
   #elif _WIN32
   system("cls");
   #endif
}

T3Status make_a_turn(T3Board * board) {
     char move[4];
     char moves[9][2];
     char symbol;
     float bestmove;
     int i;
     T3Move move_status;


     printf(">> ");
     scanf("%2s %c", move, &symbol);
     move_status = t3_set(board, move, symbol);

     t3_ai_candidate_moves(board, moves);
     for(i = 0; i < 9; i++) {
         printf("%i: %c -- %c, ", i, moves[i][0], moves[i][1]);
     }

     switch(move_status) {
        case INVALID_COORD:
           puts("Invalid coordinates!");
        break;
        case INVALID_VALUE:
           puts("Invalid symbol!");
        break;
        case INVALID_MOVE:
           puts("You can't play there!");
        break;
        case NOT_YOUR_TURN:
           puts("Not your turn");
        break;
        case SUCCESS:
           puts("OK!");
        break;
     }
     return t3_gamestatus(board);
}

int main() {
   T3Board * board = t3_create();
   T3Status status = t3_gamestatus(board);
   clear_screen();

   while(status == GAME_IN_PROGRESS) {
     t3_print(board);
     status = make_a_turn(board);
     clear_screen();
   }

   switch(status) {
     case X_WINS:
         puts("X wins!");
     break;

     case O_WINS:
         puts("O wins!");
     break;

     case DRAW:
         puts("This game is a draw!");
     break;
   }

   t3_free(board);
   return 0;
}
