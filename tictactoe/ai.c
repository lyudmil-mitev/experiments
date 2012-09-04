/*
 * Implement a negamax AI for tictactoe
 */

#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

#define T3_AI_MAXDEPTH 9
#define INFINITY 999
#define MAX(x,y) x > y ? x : y
#define MIN(x,y) x < y ? x : y

short t3_ai_candidate_moves(T3Board * board, short moves[]) {
   short letter, row, i = 0;
   for(row = 0; row < 3; row++) {
      for(letter = 0; letter < 3; letter++) {
          if(t3_get_ch(board, 'A' + letter, '1' + row) == ' ') {
              moves[i] = row*3 + letter;
              i += 1;
          }
      }
   }
   return i;
}

float t3_ai_buildtree(T3Board * board, char player, short * best_moves, int depth) {

   /*
    * Recursively construct and go down a game tree.
    * Each node is a possible game state.
    * Each node is scored as either
    * +/- INFINITY for win/loose or 0 for Draw
    */

    if(depth > T3_AI_MAXDEPTH) return 0;

    T3Status status = t3_gamestatus(board);
    T3Board * board_clone;
    float score, subscore;
    short moves[9], moves_count, i;
    char  other_player, active_player = t3_get_turn(board);

    if(status == X_WINS) {
       if(active_player == 'X') return INFINITY;
       else return -INFINITY;
    } else if(status == O_WINS) {
       if(active_player == 'O') return INFINITY;
       else return -INFINITY;
    } else if(status == DRAW) {
       return 0;
    }

    if(player == 'X') other_player = 'O';
    else other_player = 'X';

    if(player == active_player) score = -INFINITY;
    else score = INFINITY;

    moves_count = t3_ai_candidate_moves(board, moves);
    for(i = 0; i < moves_count; i++) {
        board_clone = t3_clone(board);
        t3_set_pos(board_clone, moves[i], player);
        subscore = -t3_ai_buildtree(board_clone, other_player, best_moves, depth + 1);

        if(score < subscore) score = subscore;
        if(depth == 0) {
           *best_moves = moves[i];
           best_moves++;
        }

        t3_free(board_clone);
    }

    return score;
}

void shuffle(short *array, size_t n) {
 /* Source: http://benpfaff.org/writings/clc/shuffle.html */
 if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
       size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
       short t = array[j];
       array[j] = array[i];
       array[i] = t;
    }
 }
}

short t3_ai_bestmove(T3Board * board, char turn) {
    short best_moves[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i;
    size_t size = 0;

    t3_ai_buildtree(board, turn, best_moves, 0);
    for(i = 0; i < 9; i++) {
        if(best_moves[i] == -1) break;
        else size += 1;
    }
    for(i = 0; i < 9; i++) {
        printf("%i,",  best_moves[i]);
    }
    puts("");
    srandom(time( NULL ));
    shuffle(best_moves, size);
    for(i = 0; i < 9; i++) {
        printf("%i,",  best_moves[i]);
    }
    puts("");
    return best_moves[0];
}

