//
// Created by Jemima Adjenughure on 08/04/2020.
//

#ifndef FOCUS_STACK_H
#define FOCUS_STACK_H

#include<stdio.h>
#include<stdlib.h>

typedef enum PieceEnum
{
    BLUE,
    YELLOW
} Piece;

typedef struct NodeStruct {
    Piece piece;
    struct NodeStruct* next;
}Node;

typedef struct StackStruct {
    Node* head;
    int size;
}Stack;

Stack createStack();
void insert(Stack* s,Piece p);
void push(Stack* s, Piece p);
Piece pop(Stack* s);
Piece peak(Stack* s);
Piece removeLast(Stack* s);
char* getFirst5(Stack* s);

#endif //FOCUS_STACK_H
