#ifndef TICTACTOE_H
#define TICTACTOE_H

enum t3_move {
    SUCCESS,       /* Valid Move */
    INVALID_COORD, /* Coord is out of range */
    INVALID_VALUE, /* Value is not 'X' or 'O' */
    INVALID_MOVE,  /* Overwriting already taken coord */
    NOT_YOUR_TURN,
};

enum t3_status {
    GAME_IN_PROGRESS,
    X_WINS,
    O_WINS,
    DRAW
};

typedef struct T3Board T3Board;

T3Board * t3_create();
void t3_free(T3Board * board);
void t3_print(T3Board * board);
enum t3_move t3_set(T3Board* board, char * xy, char value);
char t3_get(T3Board* board, char * xy);
enum t3_status t3_gamestatus(T3Board * board);

#endif
