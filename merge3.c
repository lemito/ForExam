#include <stdio.h>

// время: O(n)
// память: O(1)
int main(void)
{
    FILE *first = fopen("first.txt", "r");
    FILE *second = fopen("second.txt", "r");
    FILE *third = fopen("third.txt", "r");
    FILE *new = fopen("new.txt", "w");

    if (first == NULL || second == NULL || third == NULL || new == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int c;
    while ((c = fgetc(first)) != EOF) {
        fputc(c, new);
    }
    fclose(first);

    while ((c = fgetc(second)) != EOF) {
        fputc(c, new);
    }
    fclose(second);

    while ((c = fgetc(third)) != EOF) {
        fputc(c, new);
    }
    fclose(third);

    fclose(new);

    puts("\nDone!");
    return 0;
}
