#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tictactoe.h"
#include "ai.c"

void static play_game(T3Board * board, const char * game_str) {
   char xy[2];
   char symbol;
   const char * pos = game_str;

   while((pos = index(pos, ',')) != NULL) {
       xy[0]  = *(pos - 4);
       xy[1]  = *(pos - 3);
       symbol = *(pos - 1);

       t3_set(board, xy, symbol);
       pos++;
   }

   /* Don't forget the last coord! */
   pos = rindex(game_str, ',');
   xy[0]  = *(pos + 2);
   xy[1]  = *(pos + 3);
   symbol = *(pos + 5);

   t3_set(board, xy, symbol);
}

void static test_ai_candidate_moves() {
    T3Board * b = t3_create();
    short * moves_target, * moves, moves_count;

    moves_target = malloc(sizeof(short)*9);
    moves        = malloc(sizeof(short)*9);
    assert(moves != NULL && moves_target != NULL);

    moves_target = (short []){0, 1, 2, 3, 4, 5, 6, 7, 8};
    moves_count  = t3_ai_candidate_moves(b, moves);
    assert(memcmp(moves_target, moves, moves_count*sizeof(short)) == 0);

    play_game(b, "A1 X, B1 O, C1 X");

    moves_target = (short []){3, 4, 5, 6, 7, 8};
    moves_count  = t3_ai_candidate_moves(b, moves);
    assert(memcmp(moves_target, moves, moves_count*sizeof(short)) == 0);

    t3_free(b);

    b = t3_create();

    play_game(b, "A1 X, B2 O, C3 X");

    moves_target = (short []){1, 2, 3, 5, 6, 7};
    moves_count  = t3_ai_candidate_moves(b, moves);
    assert(memcmp(moves_target, moves, moves_count*sizeof(short)) == 0);
}

void static test_gamestatus() {

    T3Board * b = t3_create();
    assert(t3_gamestatus(b) == GAME_IN_PROGRESS);

    play_game(b, "A1 X, A2 O, B2 X, A3 O, C3 X");
    assert(t3_gamestatus(b) == X_WINS);
    t3_free(b);

    b = t3_create();

    play_game(b, "C2 X, A3 O, A2 X, B2 O, A1 X, C1 O");
    assert(t3_gamestatus(b) == O_WINS);
    t3_free(b);

    b = t3_create();

    play_game(b, "C2 X, A1 O, A2 X, B1 O, A3 X, C1 O");
    assert(t3_gamestatus(b) == O_WINS);
    t3_free(b);

    b = t3_create();

    play_game(b, "C1 X, A1 O, C2 X, B1 O, C3 X");
    assert(t3_gamestatus(b) == X_WINS);
    t3_free(b);
}

int main() {
   test_gamestatus();
   test_ai_candidate_moves();
   puts("OK");
   return 0;
}
