#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(void) {
    FILE *first = fopen("1.txt", "r");
    FILE *second = fopen("2.txt", "r");

    char buffer1[MAX_LINE_LENGTH];
    char buffer2[MAX_LINE_LENGTH];

    while (!feof(first) && !feof(second)) {
        if (fgets(buffer1, MAX_LINE_LENGTH, first) == NULL) {
            break;
        }
        if (fgets(buffer2, MAX_LINE_LENGTH, second) == NULL) {
            break;
        }

        buffer1[strcspn(buffer1, "\n")] = '\0';
        buffer2[strcspn(buffer2, "\n")] = '\0';

        if (strcmp(buffer1, buffer2) != 0) {
            printf("1> %s\n", buffer1);
            printf("2> %s\n", buffer2);
            puts("--");
        }
    }

    while (!feof(first)) {
        if (fgets(buffer1, MAX_LINE_LENGTH, first) == NULL) {
            break;
        }
        printf("1> %s", buffer1);
    }

    while (!feof(second)) {
        if (fgets(buffer2, MAX_LINE_LENGTH, second) == NULL) {
            break;
        }
        printf("2> %s", buffer2);
    }

    fclose(first);
    fclose(second);
    return 0;
}
