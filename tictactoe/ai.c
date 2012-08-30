/*
 * Implement a negamax AI for tictactoe
 */

#include <math.h>
#include "tictactoe.h"
#include "assert.h"

#define T3_AI_MAXDEPTH 6

void t3_ai_candidate_moves(T3Board * board, char moves[9][2]) {
   char letter, row;
   char xy[2];
   int i = 0;

   for(letter = 'A'; letter <= 'C'; letter++) {
      for(row = '1'; row <= '3'; row++, i++) {
         printf("i=%i\n", i);
         xy[0] = letter, xy[1] = row;
         if(t3_get(board, xy) == ' ') {
             moves[i][0] = letter;
             moves[i][1] = row;
             i++;
         }
      }
   }
}

float t3_ai_buildtree(T3Board * board, int depth) {
    if(depth > T3_AI_MAXDEPTH) return 0;

    T3Status status = t3_gamestatus(board);
    T3Board * board_clone;
    char moves[9][2];
    int i, salist_i = 0;
    float salist[9];
    float alpha = -INFINITY, subalpha;

    switch(status) {
        case X_WINS:
            if(t3_get_turn(board) == 'X') return INFINITY;
            else return -INFINITY;
        break;
        case O_WINS:
            if(t3_get_turn(board) == 'O') return -INFINITY;
            else return INFINITY;
        break;
        case DRAW:
            return 0;
        break;
    }

    t3_ai_candidate_moves(board, moves);
    for(i = 0; i < 9; i++) {
        board_clone = t3_clone(board);
        t3_set(board_clone, moves[i], t3_get_turn(board));
        subalpha = -t3_ai_buildtree(board_clone, depth+1);
        t3_free(board_clone);
        if(alpha < subalpha) alpha = subalpha;

        if(depth == 0) {
             salist[salist_i] = subalpha;
             salist_i += 1;
             assert(salist_i < 9);
        }
    }

    if(depth == 0) {
       for(i = 0; i < salist_i; i++) {
           /* XXX: Randomize */
           if(salist[i] == alpha) return alpha;
       }
    }

    return alpha;
}

float t3_ai_bestmove(T3Board * board) {
    return t3_ai_buildtree(board, 0);
}

