#include <stdio.h>
#include <string.h>
#include "util.h"

char *read_line(FILE *file_pointer) {
    if (feof(file_pointer) || file_pointer == NULL) return NULL;
	
    size_t buffer_size = 32 * sizeof(char);
    char *buffer = (char *)malloc(buffer_size);

    fgets(buffer, buffer_size, file_pointer);

    while(buffer[strlen(buffer) - 1] != '\n') {
        buffer_size = buffer_size * 2;
	buffer = (char *)realloc(buffer, buffer_size);
        fgets(buffer, buffer_size, file_pointer);
    }

    return buffer;
}
