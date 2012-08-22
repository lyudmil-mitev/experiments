#ifndef TICTACTOE_H
#define TICTACTOE_H

enum t3_turn {
    X_TURN,
    O_TURN
};

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
    O_WINS
};

typedef struct T3Board T3Board;

T3Board * t3board_create();
void t3_free(T3Board * board);
void t3_print(T3Board * board);
enum t3_move t3board_set(T3Board* board, char * xy, char value);
char t3board_get(T3Board* board, char * xy);
int game_status(T3Board * board);

#endif
