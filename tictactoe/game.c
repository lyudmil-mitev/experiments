#include "tictactoe.h"
#include "stdio.h"
#include <stdlib.h>

void clear_screen() {
   #ifdef __unix__
   system("clear");
   #elif _WIN32
   system("cls");
   #endif
}

int main() {
   T3Board * board = t3_create();
   enum t3_status status = t3_gamestatus(board);
   enum t3_move move_status;
   char move[3];
   char symbol;

   t3_print(board);
   while(status == GAME_IN_PROGRESS) {
     printf(">> ");
     scanf("%2s %c", move, &symbol);
     move_status = t3_set(board, move, symbol);

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
     t3_print(board);
     status = t3_gamestatus(board);
   }
   t3_free(board);
   return 0;
}
