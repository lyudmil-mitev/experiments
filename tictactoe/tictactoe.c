#include "tictactoe.h"
#include "stdlib.h"
#include "stdio.h"

#define  COORD_INVALID(xy) (xy[0] - 'A') > 2 || (xy[1] - '0') > 2
#define  EQUAL_3(x,y,z) (x == y) && (x == z) && (y == z)

struct T3Board {
     char grid[9];
     char turn;
};


static T3Board * _t3_alloc() {
     T3Board * board = (T3Board *) malloc(sizeof(T3Board));
     return board;
}

static void _t3_init(T3Board * board) {
     int i;
     for(i = 0; i < 10; i++) board->grid[i] = ' ';
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
        clone->grid[i] = board->grid[i];
     }

     return clone;
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
           printf(" | %c", board->grid[T3_COORD_RESOLVE(xy)]);
           if(letter == 'C') {
              puts(" |");
              puts("  -------------");
           }
         }
     }
     puts("    A   B   C  ");
}

T3Status t3_gamestatus(T3Board * board) {
   char row, letter;
   int i;

   /* Check columns */
   for(letter = 'A'; letter <= 'C'; letter++) {
        if(EQUAL_3(
               board->grid[T3_COORD_RESOLVE_CH(letter, '1')],
               board->grid[T3_COORD_RESOLVE_CH(letter, '2')],
               board->grid[T3_COORD_RESOLVE_CH(letter, '3')])
          ) {
           if(board->grid[T3_COORD_RESOLVE_CH(letter, '1')] == 'X')
              return X_WINS;
           else if(board->grid[T3_COORD_RESOLVE_CH(letter, '1')] == 'O')
              return O_WINS;
        }
   }

   /* Check rows */
   for(row = '1'; row <= '3'; row++) {
        if(EQUAL_3(
               board->grid[T3_COORD_RESOLVE_CH('A', row)],
               board->grid[T3_COORD_RESOLVE_CH('B', row)],
               board->grid[T3_COORD_RESOLVE_CH('C', row)])
          ) {
           if(board->grid[T3_COORD_RESOLVE_CH('A', row)] == 'X')
              return X_WINS;
           else if(board->grid[T3_COORD_RESOLVE_CH('A', row)] == 'O')
              return O_WINS;
        }
   }

   /* Check left diagonal */
   if(EQUAL_3(
          board->grid[T3_COORD_RESOLVE_CH('A', '1')],
          board->grid[T3_COORD_RESOLVE_CH('B', '2')],
          board->grid[T3_COORD_RESOLVE_CH('C', '3')])
     ) {
      if(board->grid[T3_COORD_RESOLVE_CH('A', '1')] == 'X')
         return X_WINS;
      else if(board->grid[T3_COORD_RESOLVE_CH('A', '1')] == 'O')
         return O_WINS;
   }

   /* Check right diagonal */
   if(EQUAL_3(
          board->grid[T3_COORD_RESOLVE_CH('A', '3')],
          board->grid[T3_COORD_RESOLVE_CH('B', '2')],
          board->grid[T3_COORD_RESOLVE_CH('C', '1')])
     ) {
      if(board->grid[T3_COORD_RESOLVE_CH('A', '3')] == 'X')
         return X_WINS;
      else if(board->grid[T3_COORD_RESOLVE_CH('A', '3')] == 'O')
         return O_WINS;
   }

   for(i = 0; i < sizeof(board->grid) - sizeof(board->grid[0]); i++) {
      /* If we find an empty cell, the game is still in progress */
      if(board->grid[i] == ' ') return GAME_IN_PROGRESS;
   }

   /* Otherwise it's a draw */
   return DRAW;
}

char t3_get(T3Board * board, char * xy) {
     if(COORD_INVALID(xy))
        return 0;
     else
        return board->grid[T3_COORD_RESOLVE(xy)];
}

char t3_get_turn(T3Board * board) {
     return board->turn;
}

T3Move t3_set(T3Board * board, char * xy, char value) {
     T3Move result = SUCCESS;
     if(board->grid[T3_COORD_RESOLVE(xy)] != ' ') return result = INVALID_MOVE;
     if(COORD_INVALID(xy)) result = INVALID_COORD;
     if(value != 'X' && value != 'O') return result = INVALID_VALUE;
     if(board->turn != value) return result = NOT_YOUR_TURN;

     board->grid[T3_COORD_RESOLVE(xy)] = value;
     board->turn = (value == 'X' ? 'O' : 'X');
     return result = SUCCESS;
}
