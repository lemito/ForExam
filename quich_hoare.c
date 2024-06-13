#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int l, int r){
    int pivot = arr[r];
    int i = l-1;
    for(int j = l; j <= r; j++){
        if (arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    return i+1;
}

void sort(int arr[], int l, int r){
    if (l < r){
        int q = partition(arr, l, r);
        sort(arr, l, q-1);
        sort(arr, q+1, r);
    }
}

int main(){
    int my[7] = {1, 5, 8, 3, 4, 2, 7};
    int N = sizeof(my)/ sizeof(int);
    printf("%d\n", N);
    sort(my, 0, N-1);
    for (int i = 0; i < N; ++i){
        printf("%d", my[i]);
    }
}

