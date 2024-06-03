// за основу взят queue из https://github.com/lemito/MagicOfTheC/blob/main/src/queue/queue_dyn_lib.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Item
{
    char data[25];
    struct Item *next;
};

typedef struct dequeue
{
    struct Item *first;
    struct Item *last;
    int size;
} dequeue;

void Create(dequeue *q)
{
    q->first = q->last = malloc(sizeof(struct Item));
    q->size = 0;
}

bool Empty(dequeue *q)
{
    return q->first == q->last;
}

int Size(dequeue *q)
{
    return q->size;
}

bool PushFront(dequeue *q, const char* t)
{
    struct Item *newItem = malloc(sizeof(struct Item));
    if (!newItem)
        return false;

    strcpy(newItem->data, t);
    newItem->next = q->first;
    q->first = newItem;
    q->size++;
    return true;
}

bool PushBack(dequeue *q, const char* t) {
    struct Item *newItem = malloc(sizeof(struct Item));
    if (!newItem)
        return false;

    strcpy(newItem->data, t);
    newItem->next = NULL;

    if (q->last!= NULL) {
        q->last->next = newItem;
    } else {
        q->first = newItem;
    }
    q->last = newItem;
    q->size++;
    return true;
}


bool PopFront(dequeue *q)
{
    if (q->first == q->last)
        return false;
    struct Item *pi = q->first;
    q->first = q->first->next;
    q->size--;
    free(pi);
    return true;
}

bool PopBack(dequeue *q)
{
    if (q->first == q->last)
        return false;
    struct Item *current = q->first;
    while (current->next!= q->last)
    {
        current = current->next;
    }
    free(q->last);
    q->last = current;
    q->last->next = NULL;
    q->size--;
    return true;
}

char* Front(const dequeue *q)
{
    if (q->first!= q->last)
        return q->first->data;
    return NULL;
}

char* Back(const dequeue *q)
{
    if (q->first!= q->last)
        return q->last->data;
    return NULL;
}

void Destroy(dequeue *q)
{
    while (!Empty(q))
    {
        struct Item *pi = q->first;
        q->first = q->first->next;
        if (pi->data!= NULL) {
            free(pi->data);
        }
        free(pi);
    }
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}


// Время: O(n)
// память: O(1)
void Reverse(dequeue *q) {
    if (!Empty(q)) {
        char *t = strdup(Front(q));
        PopFront(q);
        Reverse(q);
        PushBack(q, t);
        free(t);
    }
}

void PrintQueue(const dequeue *q) {
    if (Empty(q)) {
        return;
    }
    struct Item *current = q->first;
    printf("[ ");
    while (current!= NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("]\n");
}

int main(void) {
    dequeue q;
    Create(&q);

    PushFront(&q, "First");
    PushBack(&q, "Second");
    PushFront(&q, "Third");
    PushBack(&q, "Fourth");
    printf("%d", q.size);

    printf("До реверса:\n");
    PrintQueue(&q);

    Reverse(&q);

    printf("После реверса:\n");
    PrintQueue(&q);
    printf("\n");

    Destroy(&q);

    return 0;
}