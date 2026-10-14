#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdbool.h"
#include "errno.h"
#include "ticTacToe.c"

// TODO: Fix the CLI stuff

// scan_safe_int, scan_safe_str, clearScreen and println come from ticTacToe.c

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
