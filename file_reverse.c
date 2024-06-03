#include <stdio.h>

// Время: O(n)
// память: O(n)
int main(void)
{
    FILE *first = fopen("first.txt", "r+");

    if (first == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    fseek(first, 0, SEEK_END);
    long long file_size = ftell(first);
    rewind(first);

    char buffer[file_size];
    fread(buffer, sizeof(char), file_size, first);

    rewind(first);

    // хз, но я делал так, чтобы менялись местами не только строки, но и символы: qwerty\nqq -> qq\nytrewq
    for (long long i = file_size - 1; i >= 0; --i) {
        fputc(buffer[i], first);
    }

    fclose(first);


    puts("\nDone!");
    return 0;
}
