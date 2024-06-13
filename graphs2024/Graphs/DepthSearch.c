#include <stdio.h>
#include <stdbool.h>
#include "../List/list.h"

#define MAX 5

typedef bool Graph[MAX][MAX];

DEF_LIST(path, int) // Определяем список List_path с элементами типа int
DEF_LIST(of_paths, List_path *) // Определяем List_of_paths с элементами типа List_path
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


/* DepthSearch ищет все пути между init и goal и возвращает список из найденных путей*/
List_of_paths* DepthSearch(Graph G, int init, int goal) {
  List_of_paths * result = List_of_paths_create();
	List_path* p = List_path_create();
	void search() {
		int v = *List_path_fetch(p, List_path_prev(List_path_end(p)));
		if(v == goal) {
      List_of_paths_insert(result, List_of_paths_end(result), List_path_copy(p));
    }
		else {
			for(int i = 0; i < MAX; i++) {
				if(G[v][i] && List_path_equal(find(p, i), List_path_end(p))) {
					List_path_iterator it = List_path_insert(p, List_path_end(p), i);/* Вершины в пути хранятся в обратном порядке для удобства программирования */
					search();
					List_path_delete(p, it);
				}
			}
		}
	}
	List_path_insert(p, List_path_end(p), init);// В методичке почему-то insert, а не Insert и first, а не First
	search();
	List_path_destroy(&p);
  return result;
}

int main() {
  Graph G = {{false, true, true, false, false},
             {false, false, false, true, false},
             {false, true, false, false, true},
             {false, false, true, false, true},
             {false, false, false, false,
              false}}; /* Задаём граф через таблицу смежности*/
	
	List_of_paths * result = DepthSearch(G, 0, 4);
  for (List_of_paths_iterator pathIt = List_of_paths_begin(result);
       !List_of_paths_equal(pathIt, List_of_paths_end(result));
       pathIt = List_of_paths_next(pathIt)) {
    print(*List_of_paths_fetch(result, pathIt));
  }
}
