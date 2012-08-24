#include <stdio.h>
#include "tictactoe.h"
#include "assert.h"

void static test_gamestatus() {

    T3Board * b = t3_create();
    assert(t3_gamestatus(b) == GAME_IN_PROGRESS);

    t3_set(b, "A1", 'X');
    t3_set(b, "A2", 'O');
    t3_set(b, "B2", 'X');
    t3_set(b, "A3", 'O');
    t3_set(b, "C3", 'X');
    assert(t3_gamestatus(b) == X_WINS);
    t3_free(b);

    b = t3_create();

    t3_set(b, "C2", 'X');
    t3_set(b, "A3", 'O');
    t3_set(b, "A2", 'X');
    t3_set(b, "B2", 'O');
    t3_set(b, "A1", 'X');
    t3_set(b, "C1", 'O');
    assert(t3_gamestatus(b) == O_WINS);
    t3_free(b);

    b = t3_create();

    t3_set(b, "C2", 'X');
    t3_set(b, "A1", 'O');
    t3_set(b, "A2", 'X');
    t3_set(b, "B1", 'O');
    t3_set(b, "A3", 'X');
    t3_set(b, "C1", 'O');
    assert(t3_gamestatus(b) == O_WINS);
    t3_free(b);

    b = t3_create();

    t3_set(b, "C1", 'X');
    t3_set(b, "A1", 'O');
    t3_set(b, "C2", 'X');
    t3_set(b, "B1", 'O');
    t3_set(b, "C3", 'X');
    assert(t3_gamestatus(b) == X_WINS);
    t3_free(b);
}

int main() {
   test_gamestatus();
   puts("OK");
   return 0;
}
