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
    LLNode* tempNode = (LLNode*)malloc(sizeof(LLNode));

    if(list->head != NULL)
    {
        tempNode = list->head;
        tempData = list->head->data;
        list->head = list->head->next;

        free(tempNode);
    }

    return tempData;
}

void printInt(void* data)
{
    /* Typecast to proper type. */
    int* d = (int*)data;
    printf("%d ", *d);
}
void printLinkedList(LinkedList* list, FunctionPointer fp)
{
    LLNode* currentNode = list->head;

    while(currentNode != NULL)
    {
        fp(currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

void freeInt(void* data) 
{
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
