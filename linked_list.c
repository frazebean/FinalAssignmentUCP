#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "map_struct.h"

/* Function to initialise the linked list head pointer. */
LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;

    return list;
}

/* Function to insert data at the start of the linked list. */
void insertFirst(void* data, LinkedList* list)
{
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

/* Function to remove data at the start of the linked list. */
void* removeFirst(LinkedList* list)
{
    void* tempData = NULL;
    LLNode* tempNode;

    if(list->head != NULL)
    {
        tempNode = list->head;
        tempData = list->head->data;
        list->head = list->head->next;

        free(tempNode);
    }

    return tempData;
}

int length(LinkedList* list)
{
    int length = 0;
    LLNode* currentNode = list->head;

    while(currentNode != NULL)
    {
        length++;
        currentNode = currentNode->next;
    }

    return length;
}

void freeInt(void* data)
{
    int* d = (int*)data;
    free(d);
}
void freeChar(void* data)
{
    char* d = (char*)data;
    free(d);
}

void freeGameState(void* data) 
{
    GameState* d = (GameState*)data;

    free(d);
}

void freeLinkedList(LinkedList* list, FunctionPointer fp) {
    LLNode* currentNode = list->head;
    LLNode* nextNode;

    while (currentNode != NULL) 
    {
        nextNode = currentNode->next;  /* Track the next node. */

        fp(currentNode->data);  /* Free current node data using function pointer. */
        free(currentNode);  /* Free the current node. */

        currentNode = nextNode;
    }

    free(list);  /* Free the linked list node. */
}
