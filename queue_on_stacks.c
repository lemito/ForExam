#include <stdlib.h>
#include <stdio.h>

#define POOL_SIZE 100

typedef struct
{
    int size;
    int data[POOL_SIZE];
} stack;

void Create(stack *s)
{
    s->size = 0;
}

bool Empty(stack *s)
{
    return s->size == 0;
}

int Size(stack *s)
{
    return s->size;
}

bool Push(stack *s, int t)
{
    if (s->size == POOL_SIZE)
    {
        return false;
    }
    s->data[s->size++] = t;
    return true;
}

bool Pop(stack *s)
{
    if (!s->size)
    {
        return false;
    }
    s->size--;
    return true;
}

int Top(stack *s)
{
    return s->data[s->size-1];
}

void Destroy(stack *s)
{
    s->size = 0;
    free(s->data);
}

int main(void){
    stack st1;
    stack st2;

    Create(&st1);
    Create(&st2);

    int8_t to_push1 = 5;
    int8_t to_push2 = 55;

    // ====== Эквивалент push ======
    Push(&st1, to_push1);
    Push(&st1, to_push2);

    Push(&st2, Top(&st1));
    Pop(&st1);
    Push(&st2, Top(&st1));
    Pop(&st1);

    printf("%d\n", Top(&st2));
    Pop(&st2);
    printf("%d\n", Top(&st2));
    Pop(&st2);
    // =============================
}
