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
        oldFileSize = ftell(oldFileSize);
        rewind(oldJSONFile);

        // Allocate memory
        buff = (char*) malloc(sizeof(char)*oldFileSize);
        if (buff == NULL) {
            errnum = errno; 
            fprintf(stderr, "Memory error: %s\n", strerror(errnum));
            };

        oldJSONFileResult = size_t fread(buff, 1, oldFileSize, oldJSONFile);
        printf("this is the output %s\n", buff);
        fclose(oldJSONFile);
    }


    return 0;
}
