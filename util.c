#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "util.h"

char *read_line(FILE *fp) {
    size_t current_size = 32;
    char * line = NULL;
    while(1) {
	line = realloc(line, current_size);

	// file has ended
	if(ungetc(getc(fp), fp) == EOF) {
	    free(line);
	    return NULL;
	}

	// read into allocated
	fgets(line, current_size, fp);

        // is there an end of line on out string?
        char * point = strstr(line, "\n");
        
	if (point) {
	    // if end of line, make it into end of string.
	    *point = '\0';
	    return line;
	}else {
	    // end of line not contained, but it is end of file
	    if (ungetc(getc(fp), fp) == EOF) {
	        return line;
	    } else {
		assert(fseek(fp, 1-current_size, SEEK_CUR) == 0); // fgets advanced fp with current size - 1, we need to step back by (current size - 1) 
		current_size *= 2;
	    }
	}
    }
}
