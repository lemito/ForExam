#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

#define POOL_SIZE 100

typedef struct
{
    int L;
    int R;
} T;

typedef struct
{
    int size;
    T data[POOL_SIZE];
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

bool Push(stack *s, T t)
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

T Top(stack *s)
{
    return s->data[s->size-1];
}

void Destroy(stack *s)
{
    s->size = 0;
    free(s->data);
}


void QuickSortNR(int a[])
{
/* Быстрая сортировка Хоара - нерекурсивная */
/* Основной принцип: список границ требуемых разделений инвертируется
в стеке */
     /* Элемент стека - граничная пара */
    int n =7;
    stack st;/*ofT*/
    T t;
    Create(&st);
    t.L=0;
    t.R=n-1;
    Push(&st, t);
    do
    {
        int L = Top(&st).L;
        int R = Top(&st).R;
        Pop(&st);
        do
        {
            int x = a[(L+R)/2];
            int i=L;
            int j=R;
            do
            {
                while(a[i] < x)
                {
                    i++;
                }
                while(a[j] > x)
                {
                    j--;
                }
                if(i<=j)
                {
                    int w = a[i];
                    a[i] = a[j];
                    a[j] = w;
                    i++; j--;
                    }
            }while(i<=j);
            if(i < R)
            {
                t.L
                        =
                        i;
                t.R
                        =
                        R;
                Push(&st , t);
            }
            R = j;
        }while(L<R);
    } while(!Empty(&st));
}

void RecSort(int a[], int L, int R)
// 1 5 8 3 4 2 7
// |           |
// low        high
//      | pivot(1 шаг)
// low = 0; high = 6
// i = 0; j = 6
// 0 <= 6 =>> 1<3 =>> 1<=6 =>> 5!<3
// 7>3 ==> 2!>3
// меняем 5 и 2
{
    if(R-L<2){
        return;
    }
    int w, x;
    int i=L, j =R-1;
    x = a[(R+L)/2];
    do
    {
        while(a[i] < x)
        {
            i++;
        }
        while(a[j] > x)
        {
            j--;
        }
        if(i<=j)
        {
            w = a[i];
            a[i] = a[j];
            a[j] = w;
            i++; j--;
        }
    }while(i<=j);
    RecSort(a, L, j + 1);
    RecSort(a, i, R);
}

int main(){
    int my[7] = {1, 5, 8, 3, 4, 2, 7};
    int neMy[7] = {1, 5, 8, 3, 4, 2, 7};
    int N = sizeof(my)/ sizeof(int);
    printf("%d\n", N);
    RecSort(my, 0, N);
    for (int i = 0; i < N; ++i){
        printf("%d", my[i]);
    }
    printf("\n");
    QuickSortNR(neMy);
    for (int i = 0; i < N; ++i){
        printf("%d", neMy[i]);
    }
}

