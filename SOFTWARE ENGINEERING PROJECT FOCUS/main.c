

#include"game.h"
int main() {
    printf("\t\t\t    Welcome to Domination Board Game\n\n");

    // intitalize game variables
    Player p[2];
    Board b = initGame(p);
    int choice;
    int i = 0;
    int winner;

    printf("Please enter the two player name (seperated by space) > ");
    scanf("%s %s",p[0].name,p[1].name);
   // system("clear");

    // Start the game loop
    while (!(winner = isEnd(&b,p))) {
        printf("\t\t\t\tDomination Board Game\n\n");
        printBoard(&b);

        // get the choice
        do {
            printf("\t\t------------------ %s's Move (%s) ------------------\n", p[i].name,(p[i].playerColor == BLUE) ? "Blue" : "Yellow");
            printf("\t\t\t\tYou have %d pieces reserved.\n",p[i].reservedCount);
            printf("\t\t\t\t%s has %d pieces reserved.\n",p[1-i].name,p[1-i].reservedCount);

            printf("\t\tchoose an action: (1) Place a reserved piece (2) Move a piece/stack\n\t\t\t\t> ");
            scanf("%d", &choice);

            if (choice == 1 && p[i].reservedCount == 0) {
                // check validity of reserved piece mpvement
                printf("\t\t\t\tYou don't have a reserved pieces\n");
                choice = -1;
                continue;
            }
            if (choice == 2 && !hasPiece(b, p[i])) {
                // check validity of moving piece
                printf("\t\t\t\tYou don't have pieces on the board\n");
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
        system("cls");
    }

    // print the ending message
    printf("Player %d WON. with reserved pieces = %d and captured pieces = %d \n"
            ,winner,p[winner-1].reservedCount, p[winner - 1].capturedCount);
    return 0;
}






















