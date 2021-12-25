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
    int sizeOfStripedJSONFile;
    int valueStartFlag = 0;
    char *jsonFilePointer = buff;

    for(i = 0; i < (sizeof(char)*oldJSONFileResult); i++) {
        currentChar = *(++jsonFilePointer);
        
        if(currentChar == '"' && valueStartFlag == 0) {
            valueStartFlag = 1;
        }else if(currentChar == '"' && valueStartFlag == 1){
            valueStartFlag = 0;
        }

        if(valueStartFlag != 1 && currentChar != ' ') {
            ++sizeOfStripedJSONFile;
        }
    }

    jsonFilePointer = buff;
    char stripedJSONFile[sizeOfStripedJSONFile];

    for(i = 0; i < (sizeof(char)*oldJSONFileResult); i++) {
        currentChar = *(++jsonFilePointer);
        
        if(currentChar == '"' && valueStartFlag == 0) {
            valueStartFlag = 1;
        }else if(currentChar == '"' && valueStartFlag == 1){
            valueStartFlag = 0;
        }

        if(valueStartFlag != 1 && currentChar != ' ') {
            stripedJSONFile[i] = currentChar;
            printf("Stripped --> %c\n", currentChar);
        }
    }

    fclose(oldJSONFile);
    free(buff);
    return 0;
}