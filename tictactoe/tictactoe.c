#include "tictactoe.h"
#include "stdlib.h"
#include "stdio.h"
#define  COORD_RESOLVE(xy) (xy[1] - '1')*3 + (xy[0] - 'A')
#define  COORD_INVALID(xy) (xy[0] - 'A') > 2 || (xy[1] - '0') > 2

struct T3Board {
     char grid[9];
     enum t3_turn turn;
};

T3Board * t3board_create() {
     int i = 0;
     T3Board * board = malloc(sizeof(T3Board));
     for(i; i < 10; i++) board->grid[i] = ' ';
     board->turn = 'X';
     return board;
}

void t3_free(T3Board * board) {
     free(board);
}

void t3_print(T3Board * board) {
     char row, letter;
     char xy[2];
     
     puts("\n  -------------");
     for(row = '3'; row >= '1'; row--) {
         for(letter = 'A'; letter <= 'C'; letter++) {
           xy[0] = letter; xy[1] = row;
           if(letter == 'A') printf("%c", row);
           printf(" | %c", board->grid[COORD_RESOLVE(xy)]);
           if(letter == 'C') {
              puts(" |");
              puts("  -------------");
           }
         }
     }
     puts("    A   B   C  ");
}

enum t3_status t3_gamestatus(T3Board * board) {
   return GAME_IN_PROGRESS;
}

char t3board_get(T3Board* board, char * xy) {
     if(COORD_INVALID(xy))
        return 0;
     else
        return board->grid[COORD_RESOLVE(xy)];
}

enum t3_move t3board_set(T3Board* board, char * xy, char value) {
     enum t3_move result = SUCCESS;
     if(board->grid[COORD_RESOLVE(xy)] != ' ') return result = INVALID_MOVE;
     if(COORD_INVALID(xy)) result = INVALID_COORD;
     if(value != 'X' && value != 'O') return result = INVALID_VALUE;
     if(board->turn != value) return result = NOT_YOUR_TURN;

     board->grid[COORD_RESOLVE(xy)] = value;
     board->turn = (value == 'X' ? 'O' : 'X');
     return result = SUCCESS;
}
