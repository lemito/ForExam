#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 100

typedef struct {
    int size;
    int data[POOL_SIZE];
} stack;

void Create(stack *s) {
    s->size = 0;
}

bool Empty(stack *s) {
    return s->size == 0;
}

int Size(stack *s) {
    return s->size;
}

bool Push(stack *s, int t) {
    if (s->size == POOL_SIZE) {
        return false;
    }
    s->data[s->size++] = t;
    return true;
}

bool Pop(stack *s) {
    if (!s->size) {
        return false;
    }
    s->size--;
    return true;
}

int Top(stack *s) {
    return s->data[s->size - 1];
}

void Destroy(stack *s) {
    s->size = 0;
}

bool is_operation(char c) {
    switch (c) {
        case '|':
        case '&':
        case '^':
        case '!':
            return true;
        default:
            return false;
    }
}

int get_op_from_stack(stack* st) {
    int res = Top(st);
    Pop(st);
    return res;
}

int main(void) {
    // пример 11|
    char* input = "11|";
    stack my;
    Create(&my);
    // Длинна = 3
    size_t sizee = strlen(input);

    /**
     * Для каждого символа в строке:
     *                        1 1 |
     * индексы соотвественно: 0 1 2
     * Если str[i] - цифра => в стек цифр;
     * Если операция => достаем из стека два операнда (сначала идет второй, потом первый) и выполняем
     * операцию, сохраняя результат в стек
     **/

    for (size_t i = 0; i <= sizee; ++i) {
        if (input[i] == '0' || input[i] == '1') {
            Push(&my, input[i] - '0');
        } else if (is_operation(input[i])) {
            if (input[i] == '!') {
                // Для отрицания необходим один операнд: !1 === 0 и !0 === 1
                int o = Top(&my);
                Push(&my,!o);
            } else if (Size(&my) >= 2) {
                // Для остальных операций их два
                int o2 = get_op_from_stack(&my);
                int o1 = get_op_from_stack(&my);

                if (input[i] == '|') Push(&my, o1 | o2);
                if (input[i] == '&') Push(&my, o1 & o2);
                if (input[i] == '^') Push(&my, o1 ^ o2);
            }
        }
    }

    int res = Top(&my);
    printf("Res = %d\n", res);

    Destroy(&my);
    return EXIT_SUCCESS;
}
