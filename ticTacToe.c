#include "ticTacToe.h"


void initGame(Game *g) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            g->cells[i][j] = CELL_EMPTY;
        }
    }
    g->players[0].mark = CELL_X; g->players[1].mark = CELL_O;
    g->players[0].type = PLAYER_HUMAN; g->players[1].type = PLAYER_BOT;
    g->players[0].wins = 0; g->players[1].wins = 0;
    g->currentPlayer = 0;
    g->movesMade = 0; 
    g->status = GAME_IN_PROGRESS;
}

void printBoard(const Game *g) {
    system("clear");
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            Cell cell = g->cells[r][c];
            if (cell == CELL_EMPTY) printf(" %d ", r * BOARD_SIZE + c + 1);
            else                    printf(" %c ", cell);
            if (c < BOARD_SIZE - 1) printf("|");
        }
        printf("\n");
        if (r < BOARD_SIZE - 1) printf("---+---+---\n");
    }
}

bool isValidMove(const Game *g, int row, int col) {
    if (g->cells[row][col] != CELL_EMPTY) {
        return false;
    }
    return true;
}

bool placeMark(Game *g, int row, int col) {
    if (!isValidMove(g, row, col)) {
        return false;
    }
    g->cells[row][col] = (g->currentPlayer == PLAYER_HUMAN ? CELL_X : CELL_O);
    g->movesMade++;
    return true;
}

GameStatus checkStatus(const Game *g) {
    // check for draw
    int cellsEmpty = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (g->cells[i][j] == CELL_EMPTY) {
                cellsEmpty++;
            }
        }
    }
    if (cellsEmpty == BOARD_SIZE * BOARD_SIZE) {
        return GAME_DRAW;
    }
    
    for (int i = 0; i < 8; ++i) {
        if (boardWinningPosX[i] == g->cells) {
            return GAME_X_WINS;
        }
    }

    for (int i = 0; i < 8; ++i) {
        if (boardWinningPosO[i] == g->cells) {
            return GAME_O_WINS;
        }
    }


    return GAME_IN_PROGRESS;
}

void switchPlayer(Game *g) {
    g->currentPlayer = 1 - g->currentPlayer;
}


bool scan_safe_int(const char *prompt, int *output);

bool readMove(int *row, int *col) {
    int n;
    if (!scan_safe_int("Pick a square (1-9): ", &n)) {
        return false;
    }
    if (n < 1 || n > BOARD_SIZE * BOARD_SIZE) {
        return false;
    }
    *row = (n - 1) / BOARD_SIZE;
    *col = (n - 1) % BOARD_SIZE;
    return true;
}

void printResult(Game *g) {
    printBoard(g);
    const char *result;
    if (g->status == GAME_DRAW) {
        result = "It's a draw!";
    } else if (g->status == GAME_X_WINS) {
        result = "X wins!";
        g->players[0].wins++;
    } else if (g->status == GAME_O_WINS) {
        result = "O wins!";
        g->players[1].wins++;
    } else {
        return;
    }
    printf("\n%s\n", result);
}

void ticTacToe() {
    Game g;
    initGame(&g);
    printBoard(&g);
}