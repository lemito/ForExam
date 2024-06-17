#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEF_QUEUE(Suffix, DataType)                                       \
  typedef struct Queue_##Suffix##_Item_                                   \
  {                                                                       \
    DataType data;                                                        \
    struct Queue_##Suffix##_Item_ *next;                                  \
  } Queue_##Suffix##_Item;                                                \
                                                                          \
  typedef struct                                                          \
  {                                                                       \
    Queue_##Suffix##_Item *first;                                         \
    Queue_##Suffix##_Item *last;                                          \
    size_t size;                                                          \
  } Queue_##Suffix;                                                       \
                                                                          \
  Queue_##Suffix *Queue_##Suffix##_create()                               \
  {                                                                       \
    Queue_##Suffix *q = (Queue_##Suffix *)malloc(sizeof(Queue_##Suffix)); \
    q->first = q->last =                                                  \
        (Queue_##Suffix##_Item *)malloc(sizeof(Queue_##Suffix##_Item));   \
    q->size = 0;                                                          \
    return q;                                                             \
  }                                                                       \
                                                                          \
  bool Queue_##Suffix##_empty(Queue_##Suffix *q) { return q->size == 0; } \
                                                                          \
  int Queue_##Suffix##_size(Queue_##Suffix *q) { return q->size; }        \
                                                                          \
  bool Queue_##Suffix##_push(Queue_##Suffix *q, const DataType value)     \
  {                                                                       \
    if (!(q->last->next = (Queue_##Suffix##_Item *)malloc(                \
              sizeof(Queue_##Suffix##_Item))))                            \
    {                                                                     \
      return false;                                                       \
    }                                                                     \
                                                                          \
    q->last->data = value;                                                \
    q->last = q->last->next;                                              \
    q->size++;                                                            \
    return true;                                                          \
  }                                                                       \
                                                                          \
  bool Queue_##Suffix##_pop(Queue_##Suffix *q)                            \
  {                                                                       \
    if (Queue_##Suffix##_empty(q))                                        \
    {                                                                     \
      return false;                                                       \
    }                                                                     \
                                                                          \
    Queue_##Suffix##_Item *temp = q->first;                               \
    q->first = q->first->next;                                            \
    q->size--;                                                            \
    free(temp);                                                           \
                                                                          \
    return true;                                                          \
  }                                                                       \
                                                                          \
  DataType *Queue_##Suffix##_front(Queue_##Suffix *q)                     \
  {                                                                       \
    if (!Queue_##Suffix##_empty(q))                                       \
    {                                                                     \
      return &q->first->data;                                             \
    }                                                                     \
    return NULL;                                                          \
  }                                                                       \
                                                                          \
  void Queue_##Suffix##_destroy(Queue_##Suffix *q)                        \
  {                                                                       \
    while (!Queue_##Suffix##_empty(q))                                    \
    {                                                                     \
      Queue_##Suffix##_pop(q);                                            \
    }                                                                     \
                                                                          \
    free(q->first);                                                       \
    q->first = NULL;                                                      \
    q->last = NULL;                                                       \
    q->size = 0;                                                          \
  }
#endif
