#include <stdlib.h>
#include <stdio.h>

#include "tictactoe.h"

#define  COORD_INVALID(xy) (xy[0] - 'A') > 2 || (xy[1] - '1') > 2
#define  COORD_INVALID_2(x, y) (x - 'A') > 2 || (y - '1') > 2
#define  EQUAL_3(x,y,z) (x == y) && (x == z) && (y == z)

struct T3Board {
     char grid[3][3];
     char turn;
};


static T3Board * _t3_alloc() {
     T3Board * board = (T3Board *) malloc(sizeof(T3Board));
     return board;
}

static void _t3_init(T3Board * board) {
     int i;
     for(i = 0; i < 10; i++) {
        ((char *) board->grid)[i] = ' ';
     }
     board->turn = 'X';
}

T3Board * t3_create() {
     T3Board * board = _t3_alloc();
     _t3_init(board);
     return board;
}

T3Board * t3_clone(T3Board * board) {
     int i;
     T3Board * clone = _t3_alloc();
     clone->turn = board->turn;

     for(i = 0; i < 10; i++) {
        ((char *) clone->grid)[i] = ((char *) board->grid)[i];
     }

     return clone;
}

void t3_free(T3Board * board) {
     free(board);
}

void t3_print(T3Board * board) {
     char row, letter;

     puts("\n  -------------");
     for(row = '3'; row >= '1'; row--) {
         for(letter = 'A'; letter <= 'C'; letter++) {
           if(letter == 'A') printf("%c", row);
           printf(" | %c", t3_get_ch(board, letter, row));
           if(letter == 'C') {
              puts(" |");
              puts("  -------------");
           }
         }
     }
     puts("    A   B   C  ");
}

T3Status t3_gamestatus(T3Board * board) {
   int row, letter;
   int i;

   /* Check columns */
   for(letter = 0; letter < 3; letter++) {
        if(EQUAL_3(
               board->grid[letter][0],
               board->grid[letter][1],
               board->grid[letter][2])
          ) {
           if(board->grid[letter][0] == 'X')      return X_WINS;
           else if(board->grid[letter][0] == 'O') return O_WINS;
        }
   }

   /* Check rows */
   for(row = 0; row < 3; row++) {
        if(EQUAL_3(
               board->grid[0][row],
               board->grid[1][row],
               board->grid[2][row])
          ) {
           if(board->grid[0][row] == 'X')      return X_WINS;
           else if(board->grid[0][row] == 'O') return O_WINS;
        }
   }

   /* Check left diagonal */
   if(EQUAL_3(
          board->grid[0][0],
          board->grid[1][1],
          board->grid[2][2])
     ) {
      if(board->grid[0][0] == 'X')
         return X_WINS;
      else if(board->grid[0][0] == 'O')
         return O_WINS;
   }

   /* Check right diagonal */
   if(EQUAL_3(
          board->grid[0][2],
          board->grid[1][1],
          board->grid[2][0])
     ) {
      if(board->grid[0][2] == 'X')
         return X_WINS;
      else if(board->grid[0][2] == 'O')
         return O_WINS;
   }

   for(i = 0; i < 9; i++) {
      /* If we find an empty cell, the game is still in progress */
      if(((char *) board->grid)[i] == ' ') return GAME_IN_PROGRESS;
   }

   /* Otherwise it's a draw */
   return DRAW;
}

char t3_get(T3Board * board, char * xy) {
    return t3_get_ch(board, xy[0], xy[1]);
}

char t3_get_ch(T3Board * board, char x, char y) {
     if(COORD_INVALID_2(x, y))
        return 0;
     else
        return board->grid[x - 'A'][y - '1'];
}

char t3_get_turn(T3Board * board) {
     return board->turn;
}

T3Move t3_set(T3Board * board, char * xy, char value) {
     T3Move result = SUCCESS;

     if(t3_get(board, xy) != ' ')     return result = INVALID_MOVE;
     if(COORD_INVALID(xy))            return result = INVALID_COORD;
     if(value != 'X' && value != 'O') return result = INVALID_VALUE;
     if(board->turn != value)         return result = NOT_YOUR_TURN;

     board->grid[xy[0] - 'A'][xy[1] - '1'] = value;
     board->turn = (value == 'X' ? 'O' : 'X');

     return result;
}

T3Move t3_set_pos(T3Board * board, short pos, char value) {
     char xy[2];
     xy[0] = 'A' + pos % 3;
     xy[1] = '1' + pos / 3;

     return t3_set(board, xy, value);
}

