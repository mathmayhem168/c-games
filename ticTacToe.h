#ifndef TICTACTOE_H
#define TICTACTOE_H

#define BOARD_SIZE 3

#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdbool.h"
#include "errno.h"


// Models

typedef enum {
    CELL_EMPTY = ' ',
    CELL_X =     'X',
    CELL_O =     'O'
} Cell;

typedef enum {
    GAME_IN_PROGRESS,
    GAME_X_WINS,
    GAME_O_WINS,
    GAME_DRAW
} GameStatus;

typedef enum {
    PLAYER_HUMAN,
    PLAYER_BOT
} PlayerType;

typedef struct {
    Cell       mark;
    PlayerType type;
    int wins;
} Player;

typedef struct {
    Cell       cells[BOARD_SIZE][BOARD_SIZE];  
    Player     players[2];
    int        currentPlayer;
    int        movesMade;
    GameStatus status;
} Game;

// Winning positions
// Each entry is a 3x3 mask: CELL_X marks the three squares that form a line,
// CELL_EMPTY marks squares that are not part of it.
static const Cell boardWinningPosX[8][BOARD_SIZE][BOARD_SIZE] = {
    // Rows
    {{CELL_X,     CELL_X,     CELL_X    },
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY}},

    {{CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_X,     CELL_X,     CELL_X    },
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY}},

    {{CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_X,     CELL_X,     CELL_X    }},

    // Columns
    {{CELL_X,     CELL_EMPTY, CELL_EMPTY},
     {CELL_X,     CELL_EMPTY, CELL_EMPTY},
     {CELL_X,     CELL_EMPTY, CELL_EMPTY}},

    {{CELL_EMPTY, CELL_X,     CELL_EMPTY},
     {CELL_EMPTY, CELL_X,     CELL_EMPTY},
     {CELL_EMPTY, CELL_X,     CELL_EMPTY}},

    {{CELL_EMPTY, CELL_EMPTY, CELL_X    },
     {CELL_EMPTY, CELL_EMPTY, CELL_X    },
     {CELL_EMPTY, CELL_EMPTY, CELL_X    }},

    // Diagonals
    {{CELL_X,     CELL_EMPTY, CELL_EMPTY},
     {CELL_EMPTY, CELL_X,     CELL_EMPTY},
     {CELL_EMPTY, CELL_EMPTY, CELL_X    }},

    {{CELL_EMPTY, CELL_EMPTY, CELL_X    },
     {CELL_EMPTY, CELL_X,     CELL_EMPTY},
     {CELL_X,     CELL_EMPTY, CELL_EMPTY}}
};

static const Cell boardWinningPosO[8][BOARD_SIZE][BOARD_SIZE] = {
    // Rows
    {{CELL_O,     CELL_O,     CELL_O    },
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY}},

    {{CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_O,     CELL_O,     CELL_O    },
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY}},

    {{CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_EMPTY, CELL_EMPTY, CELL_EMPTY},
     {CELL_O,     CELL_O,     CELL_O    }},

    // Columns
    {{CELL_O,     CELL_EMPTY, CELL_EMPTY},
     {CELL_O,     CELL_EMPTY, CELL_EMPTY},
     {CELL_O,     CELL_EMPTY, CELL_EMPTY}},

    {{CELL_EMPTY, CELL_O,     CELL_EMPTY},
     {CELL_EMPTY, CELL_O,     CELL_EMPTY},
     {CELL_EMPTY, CELL_O,     CELL_EMPTY}},

    {{CELL_EMPTY, CELL_EMPTY, CELL_O    },
     {CELL_EMPTY, CELL_EMPTY, CELL_O    },
     {CELL_EMPTY, CELL_EMPTY, CELL_O    }},

    // Diagonals
    {{CELL_O,     CELL_EMPTY, CELL_EMPTY},
     {CELL_EMPTY, CELL_O,     CELL_EMPTY},
     {CELL_EMPTY, CELL_EMPTY, CELL_O    }},

    {{CELL_EMPTY, CELL_EMPTY, CELL_O    },
     {CELL_EMPTY, CELL_O,     CELL_EMPTY},
     {CELL_O,     CELL_EMPTY, CELL_EMPTY}}
};


// Functions

void initGame(Game *g);
void printBoard(const Game *g);
bool isValidMove(const Game *g, int row, int col); // One-indexed
bool placeMark(Game *g, int row, int col);
GameStatus checkStatus(const Game *g);
void switchPlayer(Game *g);
bool readMove(int *row, int *col);
static inline const char* markToString(Cell c) {
    switch (c) {
        case CELL_X: return "X";
        case CELL_O: return "O";
        default:     return " ";
    }
}

void printResult(Game *g);
void ticTacToe(void);


#endif