
#include <stdio.h>
#include "game.h"
int main() {
    printf("Welcome to Domination Board Game\n");

    // intitalize game variables
    Player p[2];
    Board b = initGame(p);
    int choice;
    int i = 0;
    int winner;

    // Start the game loop
    while (!(winner = isEnd(&b,p))) {
        printBoard(&b);

        // get the choice
        do {
            printf("%s player choose an action: \n\t1- Place a reserved piece\n\t2-Move a piece/stack\nchoice: ",
                   (p[i].playerColor == BLUE) ? "Blue" : "Yellow");
            scanf("%d", &choice);

            if (choice == 1 && p[i].reservedCount == 0) {
                // check validity of reserved piece mpvement
                printf("You don't have a reserved pieces\n");
                choice = -1;
                continue;
            }
            if (choice == 2 && !hasPiece(b, p[i])) {
                // check validity of moving piece
                printf("You don't have pieces on the board\n");
                choice = -1;
                continue;
            }
        } while (choice != 1 && choice != 2);

        // Perform the action
        switch (choice)
        {
            case 1:
                doPlaceAction(&b,&p[i]);
                break;
            case 2:
                doMoveAction(&b, &p[i]);
                break;
        }
        // switch players
        i = (i+1) % 2;
    }

    // print the ending message
    printf("Player %d WON. with reserved pieces = %d and captured pieces = %d \n"
            ,winner,p[winner-1].reservedCount, p[winner - 1].capturedCount);
    return 0;
}
