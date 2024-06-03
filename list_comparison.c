// в основе взято: https://github.com/lemito/MagicOfTheC/tree/main/src/linear_list_cycled
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define FREE_AND_NULL(ptr) do {free(ptr); ptr = NULL;} while(0)

typedef struct Item
{
    struct Item *next;
    char data[15];
} Item;

typedef struct Iterator
{
    Item *node;
} Iterator;

bool Equal(const Iterator *lhs, const Iterator *rhs)
{
    if (lhs != NULL && rhs != NULL)
    {
        return lhs->node == rhs->node;
    }
}

bool NotEqual(const Iterator *lhs, const Iterator *rhs)
{
    return !Equal(lhs, rhs);
}

Iterator *Next(Iterator *iterator)
{
    iterator->node = iterator->node->next;
    return iterator;
}

char *fetch(const Iterator *iterator)
{
    return iterator->node->data;
}

void Store(const Iterator *iterator, const char *t)
{
    if (iterator != NULL && iterator->node != NULL)
    {
        strncpy(iterator->node->data, t, sizeof(iterator->node->data) - 1);
        iterator->node->data[sizeof(iterator->node->data) - 1] = '\0';
    }
}

typedef struct List
{
    Item *head;
    int size;
} List;

void Create(List *list)
{
    list->head = malloc(sizeof(Item));
    list->head->next = list->head;
    list->size = 0;
}

Iterator Last(const List *list)
{
    Iterator current = {list->head};
    while (current.node->next != list->head && current.node->next != NULL)
    {
        Next(&current);
    }
    return current;
}

Iterator First(const List *list)
{
    Iterator res = {list->head};
    return res;
}

int size(const List *list)
{
    return list->size;
}

bool Empty(const List *list)
{
    Iterator first = First(list);
    Iterator last = Last(list);
    return first.node == last.node;
}

void Destroy(List *list)
{
    Iterator current = First(list);
    Iterator *next;

    while (current.node != NULL)
    {
        next = Next(&current);
        FREE_AND_NULL(current.node);
        current = *next;
    }

    FREE_AND_NULL(list->head);

    list->size = 0;
}

bool Append(List *list, int pos, const char *t)
{
    if (size(list) > 0)
        pos = pos % size(list);
    Item *newItem = malloc(sizeof(Item));
    if (pos < 0)
    {
        puts("Ай-яй-яй, num должен быть > 0");
        return false;
    }

    if (!newItem)
    {
        return false;
    }

    Iterator cur = {newItem};
    Store(&cur, t);

    if (pos == 1)
    {
        // если первый элемент -- самый первый
        if (size(list) == 0)
        {
            newItem->next = list->head;
            list->head = newItem;
        }
            // если первый элемент -- первый после прокрутки, т.е. == последний
        else
        {
            pos = size(list) + 1;
            Iterator current = First(list);
            for (int i = 0; i < pos - 2; i++)
            {
                Next(&current);
            }
            // повторка кода ниже
            Iterator tmp = {current.node->next};

            current.node->next = newItem;
            Next(&current);
            Store(&current, t);

            current.node->next = tmp.node;
            current.node->next = list->head;
        }
    }
    else
    {

        Iterator current = First(list);
        for (int i = 0; i < pos - 2; i++)
        {
            Next(&current);
        }
        Iterator tmp = {current.node->next};

        current.node->next = newItem;
        Next(&current);
        Store(&current, t);

        current.node->next = tmp.node;
    }
    list->size++;
    return true;
}

bool Remove(List *list, int user_pos)
{
    if (size(list) == 0)
    {
        return false;
    }

    Item **elem = &(list->head);
    int pos = (user_pos % size(list)) - 1;

    for (int i = 0; i < pos; i++)
    {
        elem = &((*elem)->next);
    }
    Item *next = (*elem)->next;
    free(*elem);
    *elem = next;
    list->size--;

    return true;
}

void PrintList(List *list)
{
    if (size(list) == 0 || list == NULL)
    {
        printf("Список-то пуст\n");
        return;
    }
    Iterator current = First(list);
    printf("[ ");
    int k = size(list);
    while (k != 0)
    {
        printf("%s ", fetch(&current));
        Next(&current);
        k--;
    }
    printf("]\n");
}

// время: O(n)
// память: O(1)
bool list_comparator(List* l, List* r){
    if (size(l) != size(r)) return false;
    Iterator lElem = First(l);
    Iterator rElem = First(r);

    for(size_t i = 0; i < size(l); ++i){
        // сравниваем строки, потому что я так хочу :)
        if (strcmp(fetch(&lElem), fetch(&rElem)) != 0) return false;
        Next(&lElem);
        Next(&rElem);
    }

    return true;
}