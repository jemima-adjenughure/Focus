//
// Created by Jemima Adjenughure on 08/04/2020.
//

#include"game.h"

// this function creates player with the specified color
Player createPlayer(Piece color) {
    Player x;
    x.playerColor = color;
    x.reservedCount = 0;
    x.capturedCount = 0;
    return x;
}

// this function creates a board according to the initial state in the document.
Board createBoard() {
    Board temp;
    int counter = 0; // this counter is responsible for deciding which color to be set in the current board slot.
    // this counter takes 4 values 0,1,2,3 and we divide it by two so the values be 0,0,1,1. converting that to the
    // colot enum results blue, blue, yellow, yellow. and this preserves the order of the pieces on the board mentioned
    // in the inital state of the board
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if (i == 0 || i == BOARDSIZE - 1 || j == 0 || j == BOARDSIZE - 1) {
                // should be an empty stack
                (temp).board[i][j] = createStack();
            } else {
                // should be a stack with a piece in it
                (temp).board[i][j] = createStack();
                push(&((temp).board[i][j]), (counter) / 2);
                counter = (counter + 1) % 4;
            }
        }
    }
    return temp;
}

// this function returns 0 if i,j is {(0,0), (0,1), (1,0), (0,5), (0,6), (1,6), (5,0), (6,0), (6,1), (5,6), (6,5), (6,6)}
int validStack(int i, int j) {
    if (i < 0 || i >= BOARDSIZE || j < 0 || j > BOARDSIZE) {
        return 0;
    }
    if (i + j <= 1 || (i == 0 && j >= BOARDSIZE - 2) || (j == BOARDSIZE - 1 && i <= 1)
        || (j == 0 && i >= BOARDSIZE - 2) || (i == BOARDSIZE - 1 && j <= 1) ||
        (i == BOARDSIZE - 1 && j >= BOARDSIZE - 2)
        || (j == BOARDSIZE - 1 && i >= BOARDSIZE - 2))
        return 0;
    return 1;
}

// this function print board with (- denoting invalid place, O empty space, B blue piece, Y yellow piece)
void printBoard(Board *b) {
    printf("\t\t   ");
    // the header
    for (int i = 0; i < BOARDSIZE; i++) {
        printf("   %d  ", i);
    }
    printf("\n");


    for (int i = 0; i < BOARDSIZE; i++) {
        // row number
        //printf("%d  ", i);
        for (int k = 1; k <= 3; k++) {
            printf("\t\t");
            if (k == 2)
                printf("%d  ", i);
            else
                printf("   ");

            for (int j = 0; j < BOARDSIZE; j++) {
                // the not valid slots => -
                // the empty slots => O
                // the slots with pieces => B or Y according to the piece on the top
                if (k != 2) {
                    if (!validStack(i, j)) {
                        if (!validStack(i, j - 1)) {
                            printf("      ");
                        } else {
                            printf("|     ");
                        }
                    } else
                        printf("|     ");

                } else {
                    if (!validStack(i, j)) {
                        if (!validStack(i, j - 1))
                            printf("      ");
                        else
                            printf("|     ");

                    } else if ((*b).board[i][j].size == 0) {
                        printf("|     ");
                    } else {
                        //printf("%c  ", (peak(&(*b).board[i][j]) == BLUE) ? 'B' : 'Y');
                        char *arr = getFirst5(&(*b).board[i][j]);
                        printf("|%5s", arr);
                    }
                }
            }
            if (validStack(i, BOARDSIZE - 1)) {
                printf("|");
            }
            printf("\n");
        }
        // print bottom boarders
        printf("\t\t");
        printf("   ");
        for (int j = 0; j < BOARDSIZE; j++) {
            if (validStack(i, j) || validStack(i + 1, j)) {
                printf("______");
            } else {
                printf("      ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

//returns 0 if player0 wins return 1 if player 1 wins and -1 otherwise.
int isEnd(Board *b, Player p[]) {
    int pieceCount0 = 0;
    int pieceCount1 = 0;
    int currentColor = -1;
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if (!validStack(i, j)) {
                continue;
            }
            if (b->board[i][j].size == 0) {
                continue;
            }

            currentColor = peak(&b->board[i][j]);
            if (currentColor == BLUE) {
                pieceCount0++;
            } else {
                pieceCount1++;
            }
        }
    }
    if (pieceCount0 == 0 && p[0].reservedCount == 0) {
        return 1;
    } else if (pieceCount1 == 0 && p[1].reservedCount == 0) {
        return 0;
    } else {
        return -1;
    }

}

// Function responsible for performing the move action from oldI, oldJ to newI ,newJ.
// also this gunction checks if the points are not valid or the distance is not valid
int playerMove(Player *p, Board *b, int oldI, int oldJ, int newI, int newJ) {
    if (!validStack(oldI, oldJ) || !validStack(newI, newJ)) {
        printf("\t\t\t\tOne of these points is not valid.\n");
        return 0;
    }
    if (peak(&b->board[oldI][oldJ]) != p->playerColor) {
        printf("\t\t\t\tYou don't own this piece.\n");
        return 0;
    }

    // calculate the distance between the start and the end point
    int distance = abs(oldI - newI) + abs(oldJ - newJ);

    // check if this distance is applicable with the current start point(size of the stack at it).
    if (distance != b->board[oldI][oldJ].size) {
        printf("\t\t\t\tYou can only travel %d moves.\n", b->board[oldI][oldJ].size);
        return 0;
    }

    // perform the action
    Piece temp;
    while (b->board[oldI][oldJ].size != 0) {
        temp = removeLast(&b->board[oldI][oldJ]);
        push(&b->board[newI][newJ], temp);
    }

    // check the stack if larger than 5
    checkStack(p, b, newI, newJ);
    return 1;
}


// function responsible of performing the action of placing a reserved piece in the player hand
int playerPlace(Player *p, Board *b, int i, int j) {
    if (!validStack(i, j)) {
        printf("\t\t\t\tThis point is not valid.\n");
        return 0;
    }
    if (p->reservedCount <= 0) {
        printf("\t\t\t\tYou don't have reserved pieces to place\n");
        return 0;
    }
    push(&b->board[i][j], p->playerColor);
    p->reservedCount--;
    checkStack(p, b, i, j);
    return 1;
}

// check if the stack has more than  elements and pop them to the player hand
void checkStack(Player *p, Board *b, int i, int j) {
    Piece temp;
    while (b->board[i][j].size > 5) {
        temp = removeLast(&b->board[i][j]);
        if (temp == p->playerColor) {
            p->reservedCount++;
        } else {
            p->capturedCount++;
        }
    }
}

// initialize the game with the two players and the board
Board initGame(Player p[]) {
    p[0] = createPlayer(BLUE);
    p[1] = createPlayer(YELLOW);
    return createBoard();
}

// check if the player has a piece of his own on the board
int hasPiece(Board b, Player p) {
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if (b.board[i][j].size != 0) {
                if (peak(&b.board[i][j]) == p.playerColor) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// prompt the user of the x,y coordinate to do the placing action mentioned earlier.
void doPlaceAction(Board *b, Player *p) {
    int x, y;
    int res;
    do {
        printf("\t\t\t\tPlease enter the coordinates(y x):");
        scanf("%d %d", &x, &y);
        res = playerPlace(p, b, x, y);
    } while (!res);
}

// prompt the user of the old x,y and new x,y coordinates to do the moving action mentioned earlier.
void doMoveAction(Board *b, Player *p) {
    int x, y;
    int res;

    // get the starting point
    do {
        res = 1;
        printf("\t\t\t\tPlease enter the source coordinates(y x): ");
        scanf("%d %d", &x, &y);
        if (!validStack(x, y)) {
            res = 0;
            printf("\t\t\t\tThis point is not valid.\n");
            continue;
        }
        if (b->board[x][y].size <= 0) {
            res = 0;
            printf("\t\t\t\tThis point is not valid.\n");
            continue;
        }
        if (peak(&b->board[x][y]) != p->playerColor) {
            res = 0;
            printf("\t\t\t\tYou don't own this piece.\n");
        }
    } while (!res);


    // get the ending point
    int i, j;
    do {
        res = 1;
        printf("\t\t\t\tPlease enter the destination coordinates(y x): ");
        scanf("%d %d", &i, &j);
        if (!validStack(x, y)) {
            res = 0;
            printf("\t\t\t\tThis point is not valid.\n");
        }
        res = playerMove(p, b, x, y, i, j);
    } while (!res);
}