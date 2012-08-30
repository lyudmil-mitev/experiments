#ifndef TICTACTOE_H
#define TICTACTOE_H

#define  T3_COORD_RESOLVE(xy) (xy[1] - '1')*3 + (xy[0] - 'A')
#define  T3_COORD_RESOLVE_CH(x,y) (y - '1')*3 + (x - 'A')

typedef struct T3Board T3Board;

typedef enum t3_move {
    SUCCESS,       /* Valid Move */
    INVALID_COORD, /* Coord is out of range */
    INVALID_VALUE, /* Value is not 'X' or 'O' */
    INVALID_MOVE,  /* Overwriting already taken coord */
    NOT_YOUR_TURN,
} T3Move;

typedef enum t3_status {
    GAME_IN_PROGRESS,
    X_WINS,
    O_WINS,
    DRAW
} T3Status;

T3Board * t3_create();
T3Board * t3_clone(T3Board * board);
T3Move    t3_set(T3Board * board, char * xy, char value);
T3Status  t3_gamestatus(T3Board * board);
void      t3_free(T3Board * board);
void      t3_print(T3Board * board);
char      t3_get(T3Board* board, char * xy);
char      t3_get_turn(T3Board * board);

#endif
