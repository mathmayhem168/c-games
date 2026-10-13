#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdbool.h"
#include "errno.h"
#include "ticTacToe.c"

// TODO: Fix the CLI stuff

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

void clearScreen() {
    system("clear");
}

void println(char* input) {
    printf("%s\n", input);
}

void endOfGame() {
    println("Press Enter to return to the menu..");
    getchar();
}

int main() {
    bool running = true;
    clearScreen();
    println("Welcome to C Games!");

    while (running) {
        println("Pick a game topic..");
        println("1: Classic Games");
        println("2: Puzzles And Logic Games");
        println("3: Other");
        int gameTopic;
        if (!scan_safe_int("Number: ", &gameTopic)) {
            println("Invalid input. Please enter a number from 1 to 3.");
            continue;
        }
        
        if (gameTopic == 1) {
            println("Pick a game..");
            println("1: Tetris");
            println("2: Snake");
            println("3: Tic-Tac-Toe");
            println("4: Pac-Man");
            println("5: Space Invaders");
            int firstGameTopic;
            if (!scan_safe_int("Number: ", &firstGameTopic)) {
                println("Invalid input. Please enter a number from 1 to 5.");
                continue;
            }
            if (firstGameTopic == 1) {

            } else if (firstGameTopic == 2) {

            } else if (firstGameTopic == 3) {
                ticTacToe();
                endOfGame();
            } else if (firstGameTopic == 4) {

            } else if (firstGameTopic == 5) {

            } else {
                println("Invalid input. Please enter a number from 1 to 5.");
                continue; 
            }
        } else if (gameTopic == 2) {

        } else if (gameTopic == 3) {

        } else {
            println("Invalid input. Please enter a number from 1 to 3.");
            continue;
        }

        
        
        clearScreen();
    }
    
    return 0;
}
