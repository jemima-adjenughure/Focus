//
// Created by Jemima Adjenughure on 08/04/2020.
//

#include"stack.h"

// This function creates a pre initialized stack
Stack createStack (){
    Stack temp;
    temp.head = NULL;
    temp.size = 0;
    return temp;
}

// this function inserts a new piece p in the stack s
void insert(Stack *s, Piece p)
{
    s->size++;
    if (s->head == NULL) {
        // insert at first
        s->head = (Node*)malloc(sizeof(Node*));
        s->head->piece = p;
        s->head->next = NULL;
        return;
    }
    // insert at the end
    Node* current = s->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (Node*)malloc(sizeof(Node*));
    current->next->piece = p;
    current->next->next = NULL;
}

// this function inserts an element as the first node
void push(Stack* s, Piece p)
{
    s->size++;
    if (s->head == NULL) {
        // empty list-> insert as head and the next to null
        s->head = (Node*)malloc(sizeof(Node*));
        s->head->piece = p;
        s->head->next = NULL;
        return;
    }
    // non-empty list-> insert as head and the next to old head
    Node* temp = s->head;
    s->head = (Node*)malloc(sizeof(Node*));
    s->head->piece = p;
    s->head->next = temp;
}


// this functions removes the first element and return its data
Piece pop(Stack* s)
{
    // if stack is empty. Exit with an error
    if (s->size <= 0) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }

    s->size--;
    Node* x = s->head;
    Piece p = s->head->piece;
    s->head = s->head->next;
    //free(x);
    return p;
}

// this function return the data in the first element.
Piece peak(Stack* s)
{
    // prints an error if the stack is empty
    if (s->size <= 0) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }
    return s->head->piece;
}

// this function remove the element at the end of the stack and return its data
Piece removeLast(Stack* s)
{
    // prints an error if the stack is empty
    if (s->size <= 0) {
        fprintf(stderr, "Stack is empty\n");
        exit(-1);
    }
    s->size--;
    Piece temp;
    if (s->head->next == NULL) {
        // remove first node and set head to null
        temp = s->head->piece;
//		free(s->head);
        s->head = NULL;
        return temp;
    }

    // remove the last node
    Node* current = s->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    Piece p = current->next->piece;
    //free(current->next);
    current->next = NULL;
    return p;
}

char* getFirst5(Stack* s)
{
    char* temp = malloc(6 * sizeof(char));
    Node* cur = s->head;
    int i = 0;
    while (cur != NULL && i <= 4) {
        temp[i++] = (cur->piece== BLUE)?'B':'Y';
        cur = cur->next;
    }
    temp[i] = '\0';
    return temp;
}




