#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *oldJSONFile;
    char jsonChar;
    int errnum;
    char *buff;
    long oldFileSize;
    size_t oldJSONFileResult;
    
    oldJSONFile = fopen("test.json", "r");
    
    if (oldJSONFile == NULL) {
        errnum = errno;
        printf("File can not be found: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
    }else {
        // Obtain the size of the first json file
        fseek(oldJSONFile, 0, SEEK_END);
        oldFileSize = ftell(oldJSONFile);
        rewind(oldJSONFile);

        // Allocate memory
        buff = (char*) malloc(sizeof(char)*oldFileSize);
        if (buff == NULL) {
            errnum = errno; 
            fprintf(stderr, "Memory error: %s\n", strerror(errnum));
        };

        // Read the file as binary
        oldJSONFileResult = fread(buff, 1, oldFileSize, oldJSONFile);
        if (oldJSONFileResult != oldFileSize) {
            errnum = errno;
            fprintf(stderr, "Reading file error: %s\n", strerror(errnum));
        };
    }

    int i;
    char currentChar;

    for(i = 0; i < (sizeof(char)*oldJSONFileResult); i++) {
        currentChar = *(++buff);
    }

    fclose(oldJSONFile);
    free(buff);
    return 0;
}