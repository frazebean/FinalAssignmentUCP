#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;

} LLNode;

typedef struct LinkedList
{
    LLNode* head;
} LinkedList;

typedef void (*FunctionPointer)(void* data);

LinkedList* createLinkedList();

void insertFirst(void* data, LinkedList* list);
void* removeFirst(LinkedList* list);

void printInt(void* data);
void printLinkedList(LinkedList* list, FunctionPointer fp);

void freeInt(void* data);
void freeLinkedList(LinkedList* list, FunctionPointer fp);

#endif