#include "ticTacToe.h"

// Helper
bool scan_safe_int(const char *prompt, int *output) {
    char buffer[64]; 
    char *endptr;

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return false; 
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    errno = 0;
    long parsed_val = strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\0' || errno == ERANGE) {
        return false; 
    }

    *output = (int)parsed_val;
    return true;
}

bool scan_safe_str(const char *prompt, char *output, size_t size) {
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(output, size, stdin) == NULL) {
        return false;
    }

    if (strchr(output, '\n') == NULL && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return false;
    }

    output[strcspn(output, "\n")] = '\0';
    return true;
}

void clearScreen() {
    system("clear");
}

void println(char* input) {
    printf("%s\n", input);
}


void initGame(Game *g, GameMode m, Difficulty d) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            g->cells[i][j] = CELL_EMPTY;
        }
    }
    g->players[0].mark = CELL_X; g->players[1].mark = CELL_O;
    g->players[0].wins = 0; g->players[1].wins = 0;
    g->currentPlayer = 0;
    g->movesMade = 0; 
    g->status = GAME_IN_PROGRESS;
    g->mode = m;
    g->difficulty = d;
    if (g->mode == MODE_PVBOT) {
        g->players[0].type = PLAYER_HUMAN; g->players[1].type = PLAYER_BOT;
    } else {
        g->players[0].type = PLAYER_HUMAN; g->players[1].type = PLAYER_HUMAN;
    }
    resetBoard(g);
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
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    if (g->cells[row][col] != CELL_EMPTY) {
        return false;
    }
    return true;
}

bool placeMark(Game *g, int row, int col) {
    if (!isValidMove(g, row, col)) {
        return false;
    }
    g->cells[row][col] = g->players[g->currentPlayer].mark;
    g->movesMade++;
    return true;
}

GameStatus checkStatus(const Game *g) {
    // wins are checked before the draw, so a win on the last square counts
    if (hasWon(g, CELL_X)) {
        return GAME_X_WINS;
    }
    if (hasWon(g, CELL_O)) {
        return GAME_O_WINS;
    }
    if (countEmpty(g) == 0) {
        return GAME_DRAW;
    }
    return GAME_IN_PROGRESS;
}

void switchPlayer(Game *g) {
    g->currentPlayer = 1 - g->currentPlayer;
}


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

int countEmpty(const Game *g) {
    int result = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (g->cells[i][j] == CELL_EMPTY) {
                result++;
            }
        }
    }
    return result;
}

Cell opponentMark(Cell m) {
    Cell result = CELL_EMPTY;
    if (m == CELL_X) {
        result = CELL_O;
    } else if (m == CELL_O) {
        result = CELL_X;
    }
    return result;
}

void resetBoard(Game *g) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            g->cells[i][j] = CELL_EMPTY;
        }
    }
    g->movesMade = 0;
    g->status = GAME_IN_PROGRESS;
    g->currentPlayer = 0;
}

GameMode chooseMode(void) {
    println("What game mode?");
    println("1: PVP (Player vs Player)");
    println("2: PVBOT (Player vs Bot)");
    int gameModeNum;
    while (!(scan_safe_int("Number: ", &gameModeNum) && gameModeNum > 0 && gameModeNum < 3)) {
        println("Invalid input. Please enter a number from 1 to 2.");
    }
    GameMode result;
    if (gameModeNum == 1) {
        result = MODE_PVP;
    } else {
        result = MODE_PVBOT;
    }
    return result;
}

Difficulty chooseDifficulty(void) {
    println("What game difficulty?");
    println("1: Easy");
    println("2: Medium");
    println("3: Hard");
    int gameDifficultyNum;
    while (!(scan_safe_int("Number: ", &gameDifficultyNum) && gameDifficultyNum > 0 && gameDifficultyNum < 4)) {
        println("Invalid input. Please enter a number from 1 to 3.");
    }
    Difficulty result;
    if (gameDifficultyNum == 1) {
        result = DIFF_EASY;
    } else if (gameDifficultyNum == 2) {
        result = DIFF_MEDIUM;
    } else {
        result = DIFF_HARD;
    }
    return result;
}

bool playAgain(void) {
    char buffer[16];

    while (true) {
        if (!scan_safe_str("Play again? (y/n): ", buffer, sizeof(buffer))) {
            println("Invalid input. Please enter y or n.");
            continue;
        }
        for (int i = 0; buffer[i] != '\0'; ++i) {
            buffer[i] = (char)tolower((unsigned char)buffer[i]);
        }
        if (strcmp(buffer, "y") == 0 || strcmp(buffer, "yes") == 0) {
            return true;
        }
        if (strcmp(buffer, "n") == 0 || strcmp(buffer, "no") == 0) {
            return false;
        }
        println("Invalid input. Please enter y or n.");
    }
}

void takeHumanTurn(Game *g) {
    int row;
    int col;

    while (true) {
        if (!readMove(&row, &col)) {
            println("Invalid input. Please enter a number from 1 to 9.");
            continue;
        }
        if (!placeMark(g, row, col)) {
            println("That square is taken. Pick another.");
            continue;
        }
        return;
    }
}

void takeBotTurn(Game *g) {
    Move move = botChooseMove(g);
    bool placed = placeMark(g, move.row, move.col);
    assert(placed);   // kept outside assert() so the move is made even with NDEBUG
    (void)placed;
    printf("Bot plays %d\n", move.row * BOARD_SIZE + move.col + 1);
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 500000000;
    nanosleep(&ts, NULL); // wait for 1.5 seconds for player to recalibrate
}

void takeTurn(Game *g) {
    if (g->players[g->currentPlayer].type == PLAYER_HUMAN) {
        takeHumanTurn(g);
    } else {
        takeBotTurn(g);
    }
}

Move botChooseMove(const Game *g) {
    if (g->difficulty == DIFF_EASY) {
        return botRandomMove(g);
    } else if (g->difficulty == DIFF_MEDIUM) {
        return botMediumMove(g);
    } else {
        return botHardMove(g);
    }
}

Move botRandomMove(const Game *g) {
    Move empties[BOARD_SIZE * BOARD_SIZE];
    int count = 0;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (g->cells[r][c] == CELL_EMPTY) {
                empties[count].row = r;
                empties[count].col = c;
                count++;
            }
        }
    }

    return empties[rand() % count];
}

bool findWinningMove(const Game *g, Cell mark, Move *out) {
    const Cell (*masks)[BOARD_SIZE][BOARD_SIZE] =
        (mark == CELL_X) ? boardWinningPosX : boardWinningPosO;

    for (int i = 0; i < 8; ++i) {
        int markCount = 0;
        int emptyCount = 0;
        Move emptySquare = {0, 0};

        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                if (masks[i][r][c] != mark) {
                    continue;              
                }
                if (g->cells[r][c] == mark) {
                    markCount++;
                } else if (g->cells[r][c] == CELL_EMPTY) {
                    emptyCount++;
                    emptySquare.row = r;
                    emptySquare.col = c;
                }
            }
        }

        if (markCount == 2 && emptyCount == 1) {
            *out = emptySquare;
            return true;
        }
    }
    return false;
}

bool hasWon(const Game *g, Cell mark) {
    const Cell (*masks)[BOARD_SIZE][BOARD_SIZE] =
        (mark == CELL_X) ? boardWinningPosX : boardWinningPosO;

    for (int i = 0; i < 8; ++i) {
        bool lineFull = true;
        for (int r = 0; r < BOARD_SIZE && lineFull; ++r) {
            for (int c = 0; c < BOARD_SIZE && lineFull; ++c) {
                if (masks[i][r][c] == mark && g->cells[r][c] != mark) {
                    lineFull = false;
                }
            }
        }
        if (lineFull) {
            return true;
        }
    }
    return false;
}

Move botMediumMove(const Game *g) {
    Cell botMark = g->players[g->currentPlayer].mark;
    Move move;

    if (findWinningMove(g, botMark, &move)) {
        return move;
    }

    if (findWinningMove(g, opponentMark(botMark), &move)) {
        return move;
    }

    if (g->cells[1][1] == CELL_EMPTY) {
        move.row = 1;
        move.col = 1;
        return move;
    }

    const int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; ++i) {
        if (g->cells[corners[i][0]][corners[i][1]] == CELL_EMPTY) {
            move.row = corners[i][0];
            move.col = corners[i][1];
            return move;
        }
    }

    return botRandomMove(g);
}

int minimax(Game *g, Cell turn, Cell botMark) {
    if (hasWon(g, botMark)) {
        return 1;
    }
    if (hasWon(g, opponentMark(botMark))) {
        return -1;
    }
    if (countEmpty(g) == 0) {
        return 0;
    }

    bool botsTurn = (turn == botMark);
    int best = botsTurn ? -2 : 2;     

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (g->cells[r][c] != CELL_EMPTY) {
                continue;
            }
            g->cells[r][c] = turn;
            int score = minimax(g, opponentMark(turn), botMark);
            g->cells[r][c] = CELL_EMPTY;

            if (botsTurn && score > best) {
                best = score;
            } else if (!botsTurn && score < best) {
                best = score;
            }
        }
    }
    return best;
}

Move botHardMove(const Game *g) {
    Game copy = *g;
    Cell botMark = g->players[g->currentPlayer].mark;
    Move best = {0, 0, -2};   // score below any real minimax result

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (copy.cells[r][c] != CELL_EMPTY) {
                continue;
            }
            copy.cells[r][c] = botMark;
            int score = minimax(&copy, opponentMark(botMark), botMark);
            copy.cells[r][c] = CELL_EMPTY;

            if (score > best.score) {
                best.row = r;
                best.col = c;
                best.score = score;
            }
        }
    }
    return best;
}

void ticTacToe() {
    Game g;
    Difficulty d = DIFF_MEDIUM;
    GameMode m = MODE_PVBOT;
    initGame(&g, m, d);
    printBoard(&g);
}