#include <stdio.h>
#include <unistd.h>

#define MAX 100

int main(){
    // ====== Ввод ======
    /**
     * Ввод:
     * 1 строка: N M - кол-во стр и стб
     * Далее - матрица NxM
     */
    FILE *matrix_source = fopen("matrix.txt", "r+");
    int matrix[MAX][MAX];
    int N, M;
    fscanf(matrix_source, "%d %d", &N, &M);

    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            fscanf(matrix_source, "%d", &matrix[i][j]);
            fprintf(stdout, "%d ", matrix[i][j]);
        }
        fprintf(stdout, "\n");
    }
    // ===================

    rewind(matrix_source);
    // функция очистки файла; мб сделаем рукописную
    ftruncate(fileno(matrix_source), 0);


    // ====== Транспонирование и запись ======
    fprintf(matrix_source, "%d %d\n", N, M);
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            fprintf(matrix_source, "%d ", matrix[j][i]);
            fprintf(stdout, "%d ", matrix[j][i]);
        }
        fprintf(matrix_source, "\n");
        fprintf(stdout, "\n");
    }



    fclose(matrix_source);
    return 0;
}