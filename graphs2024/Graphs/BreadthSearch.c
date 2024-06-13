#include "../List/list.h"
#include "../Queue/queue.h"
#include <stdio.h>

#define MAX 5

typedef bool Graph[MAX][MAX];

DEF_LIST(path, int) // Определяем список List_path с элементами типа int
DEF_LIST(of_paths,
         List_path *) // Определяем List_of_paths с элементами типа List_path
DEF_QUEUE(of_paths, List_path *) // Определяем очередь Queue_of_paths с
                                 // элементами типа List_path
void print(List_path *l) {
  printf("PATH: [ ");
  for (List_path_iterator it = List_path_begin(l);
       !List_path_equal(List_path_end(l), it); it = List_path_next(it)) {
    printf("%d ", *List_path_fetch(l, it) + 1);
  }
  printf("]\n");
}

List_path_iterator find(List_path *list, int x) {
  bool found = false;
  List_path_iterator first = List_path_begin(list), last = List_path_end(list);
  while (!found && !List_path_equal(first, last)) {
    if (*List_path_fetch(list, first) == x) {
      found = true;
    } else {
      first = List_path_next(first);
    }
  }
  return first;
}

List_of_paths *
breadth_search(Graph G, int init,
               int goal) // Возвращает список путей от init до goal
{
  List_of_paths *result = List_of_paths_create();
  List_path *p = List_path_create();
  List_path_insert(
      p, List_path_end(p),
      init); /*Создаем список Пути и вставляем в него init - начало пути*/
  Queue_of_paths *q = Queue_of_paths_create();
  Queue_of_paths_push(q,
                      List_path_copy(p)); /*Пушим текущий Путь в Очередь Путей*/

  while (!Queue_of_paths_empty(q)) /*Пока в Очереди есть незаконченные пути*/
  {
    p = *Queue_of_paths_front(q); /* Снимаем из Очереди верхний Путь */
    Queue_of_paths_pop(q);
    int v =
        *List_path_fetch(p, List_path_prev(List_path_end(
                                p))); /* Выталкиваем последний пункт в Пути */
    if (v == goal) { /* Если последний пункт - конечный пункт, значит мы нашли
                        полный Путь, и добавляем его в список путей*/
      List_of_paths_insert(result, List_of_paths_end(result),
                           List_path_copy(p));
    } else { /* Иначе смотрим в какие пункты можно попасть из данного*/
      for (int i = 0; i < MAX; i++) {
        if (G[v][i] && List_path_equal(find(p, i), List_path_end(p))) {
          List_path_iterator it = List_path_insert(
              p, List_path_end(p), i); /* Добавляем пункт в Путь */
          Queue_of_paths_push(
              q, List_path_copy(p)); /* Пушим копию Пути в конец Очереди*/
          List_path_delete( p, it); /* Удаляем последний добавленный пункт, т.к. могут быть
                              ещё пункты, в которые можно попасть из данного*/
        }
      }
    }
  }
  return result;
}

int main() {
  Graph G = {{false, true, true, false, false},
             {false, false, false, true, false},
             {false, true, false, false, true},
             {false, false, true, false, true},
             {false, false, false, false,
              false}}; /* Задаём граф через таблицу смежности*/

  List_of_paths *result = breadth_search(G, 0, 4);

  for (List_of_paths_iterator pathIt = List_of_paths_begin(result);
       !List_of_paths_equal(pathIt, List_of_paths_end(result));
       pathIt = List_of_paths_next(pathIt)) {
    print(*List_of_paths_fetch(result, pathIt));
  }
  return 0;
}
