//
// Created by Jemima Adjenughure on 08/04/2020.
//

#ifndef FOCUS_GAME_H
#define FOCUS_GAME_H


#include"stack.h"
#define BOARDSIZE 8
#define pNumber 2

typedef struct PlayerStruct {
    Piece playerColor;
    int reservedCount;
    int capturedCount;
}Player;

typedef struct BoardStruct {
    Stack board[BOARDSIZE][BOARDSIZE];
}Board;


Player createPlayer(Piece color);
Board createBoard();
int validStack(int i,int j);
void printBoard(Board *b);
int isEnd(Board* b, Player p[]);
int playerMove(Player* p, Board* b, int oldI,int oldJ, int newI,int newJ);
int playerPlace(Player* p, Board* b, int i, int j);
void checkStack(Player* p, Board* b, int i, int j);
Board initGame(Player p[]);

int hasPiece(Board b, Player p);
void doPlaceAction(Board* p, Player *a);
void doMoveAction(Board* p, Player* a);



#endif //FOCUS_GAME_H
