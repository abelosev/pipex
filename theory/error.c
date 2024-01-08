#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file;
    file = fopen("nonexistent_file.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Error message from strerror: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        // код для работы с файлом
        fclose(file);
    }
    return 0;
}
