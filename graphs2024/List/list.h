#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define DEF_LIST(Suffix, DataType)                                             \
  typedef struct List_##Suffix##_Item_                                         \
  {                                                                            \
    struct List_##Suffix##_Item_ *next;                                        \
    struct List_##Suffix##_Item_ *prev;                                        \
                                                                               \
    DataType data;                                                             \
  } List_##Suffix##_Item;                                                      \
                                                                               \
  typedef struct                                                               \
  {                                                                            \
    List_##Suffix##_Item *node;                                                \
  } List_##Suffix##_iterator;                                                  \
                                                                               \
  typedef struct                                                               \
  {                                                                            \
    List_##Suffix##_Item *head;                                                \
    size_t size;                                                               \
  } List_##Suffix;                                                             \
                                                                               \
  List_##Suffix *List_##Suffix##_create()                                      \
  {                                                                            \
    List_##Suffix *list = (List_##Suffix *)malloc(sizeof(List_##Suffix));      \
    list->head = (List_##Suffix##_Item *)malloc(sizeof(List_##Suffix##_Item)); \
                                                                               \
    list->head->next = list->head->prev = list->head;                          \
    list->size = 0;                                                            \
                                                                               \
    return list;                                                               \
  }                                                                            \
                                                                               \
  List_##Suffix##_iterator List_##Suffix##_begin(List_##Suffix *list)          \
  {                                                                            \
    List_##Suffix##_iterator it;                                               \
    it.node = list->head->next;                                                \
                                                                               \
    return it;                                                                 \
  }                                                                            \
                                                                               \
  List_##Suffix##_iterator List_##Suffix##_end(List_##Suffix *list)            \
  {                                                                            \
    List_##Suffix##_iterator it;                                               \
    it.node = list->head;                                                      \
                                                                               \
    return it;                                                                 \
  }                                                                            \
                                                                               \
  List_##Suffix##_iterator List_##Suffix##_next(List_##Suffix##_iterator it)   \
  {                                                                            \
    List_##Suffix##_iterator newIt;                                            \
    newIt.node = it.node->next;                                                \
                                                                               \
    return newIt;                                                              \
  }                                                                            \
                                                                               \
  List_##Suffix##_iterator List_##Suffix##_prev(List_##Suffix##_iterator it)   \
  {                                                                            \
    it.node = it.node->prev;                                                   \
                                                                               \
    return it;                                                                 \
  }                                                                            \
                                                                               \
  bool List_##Suffix##_equal(List_##Suffix##_iterator lhs,                     \
                             List_##Suffix##_iterator rhs)                     \
  {                                                                            \
    return (lhs.node == rhs.node);                                             \
  }                                                                            \
                                                                               \
  bool List_##Suffix##_empty(List_##Suffix *list)                              \
  {                                                                            \
    return List_##Suffix##_equal(List_##Suffix##_begin(list),                  \
                                 List_##Suffix##_end(list));                   \
  }                                                                            \
                                                                               \
  size_t List_##Suffix##_size(List_##Suffix *list) { return list->size; }      \
                                                                               \
  List_##Suffix##_iterator List_##Suffix##_insert(                             \
      List_##Suffix *list, List_##Suffix##_iterator it, DataType data)         \
  {                                                                            \
    List_##Suffix##_iterator newIt = {                                         \
        (List_##Suffix##_Item *)malloc(sizeof(List_##Suffix##_Item))};         \
    List_##Suffix##_Item *prev = it.node->prev;                                \
                                                                               \
    prev->next = newIt.node;                                                   \
    newIt.node->prev = prev;                                                   \
                                                                               \
    it.node->prev = newIt.node;                                                \
    newIt.node->next = it.node;                                                \
                                                                               \
    newIt.node->data = data;                                                   \
    ++list->size;                                                              \
    return newIt;                                                              \
  }                                                                            \
                                                                               \
  List_##Suffix##_iterator List_##Suffix##_delete(                             \
      List_##Suffix *list, List_##Suffix##_iterator it)                        \
  {                                                                            \
    if (List_##Suffix##_equal(List_##Suffix##_end(list), it) ||                \
        List_##Suffix##_empty(list))                                           \
    {                                                                          \
      return List_##Suffix##_end(list);                                        \
    }                                                                          \
                                                                               \
    List_##Suffix##_Item *itemToDelete = it.node;                              \
    List_##Suffix##_Item *prev = itemToDelete->prev;                           \
    List_##Suffix##_Item *next = itemToDelete->next;                           \
                                                                               \
    prev->next = next;                                                         \
    next->prev = prev;                                                         \
                                                                               \
    --list->size;                                                              \
    free(itemToDelete);                                                        \
                                                                               \
    List_##Suffix##_iterator res = {next};                                     \
    return res;                                                                \
  }                                                                            \
  DataType *List_##Suffix##_fetch(List_##Suffix *list,                         \
                                  List_##Suffix##_iterator it)                 \
  {                                                                            \
    if (List_##Suffix##_equal(List_##Suffix##_end(list), it))                  \
      return NULL;                                                             \
    return &it.node->data;                                                     \
  }                                                                            \
  List_##Suffix *List_##Suffix##_copy(List_##Suffix *list)                     \
  {                                                                            \
    List_##Suffix *copy = List_##Suffix##_create();                            \
    for (List_##Suffix##_iterator it = List_##Suffix##_begin(list);            \
         !List_##Suffix##_equal(it, List_##Suffix##_end(list));                \
         it = List_##Suffix##_next(it))                                        \
    {                                                                          \
      List_##Suffix##_insert(copy, List_##Suffix##_end(copy), it.node->data);  \
    }                                                                          \
    return copy;                                                               \
  }                                                                            \
                                                                               \
  void List_##Suffix##_destroy(List_##Suffix **list)                           \
  {                                                                            \
    while (!List_##Suffix##_empty(*list))                                      \
    {                                                                          \
      List_##Suffix##_delete(*list, List_##Suffix##_begin(*list));             \
    }                                                                          \
                                                                               \
    free((*list)->head);                                                       \
    *list = NULL;                                                              \
  }

#endif // !LIST_H_
