#ifndef TICTACTOE_H
#define TICTACTOE_H

#define BOARD_SIZE 3

#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdbool.h"
#include "errno.h"
#include "ctype.h"
#include "time.h"
#include "assert.h"



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

typedef enum {
    DIFF_EASY,
    DIFF_MEDIUM,
    DIFF_HARD
} Difficulty;

typedef enum {
    MODE_PVP,
    MODE_PVBOT
} GameMode;

typedef struct {
    int row;
    int col;
    int score; // for minimax
} Move;

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
    Difficulty difficulty;
    GameMode mode;
    Move lastMove;
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

bool scan_safe_int(const char *prompt, int *output);
bool scan_safe_str(const char *prompt, char *output, size_t size);
void clearScreen(void);
void println(char* input);

void initGame(Game *g, GameMode m, Difficulty d);
void printBoard(const Game *g);
bool isValidMove(const Game *g, int row, int col); // Zero-indexed
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

int countEmpty(const Game *g);
Cell opponentMark(Cell m);

void resetBoard(Game *g);
GameMode chooseMode(void);
Difficulty chooseDifficulty(void);
bool playAgain(void);
void takeHumanTurn(Game *g);
void takeBotTurn(Game *g);
void takeTurn(Game *g);
Move botChooseMove(const Game *g);
Move botRandomMove(const Game *g);
bool findWinningMove(const Game *g, Cell mark, Move *out);
bool hasWon(const Game *g, Cell mark);
Move botMediumMove(const Game *g);
int minimax(Game *g, Cell turn, Cell botMark);
Move botHardMove(const Game *g);






void printResult(Game *g);
void ticTacToe(void);


#endif