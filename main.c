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
    int sizeOfStripedJSONFile = 0;
    int valueStartFlag = 0;
    char *jsonFilePointer = buff;

    for(i = 0; i < (sizeof(char)*oldJSONFileResult); i++) {
        currentChar = *(++jsonFilePointer);
        
        if(currentChar == '"' && valueStartFlag == 0) {
            valueStartFlag = 1;
        }else if(currentChar == '"' && valueStartFlag == 1){
            valueStartFlag = 0;
        }

        if(currentChar != ' ') {
            ++sizeOfStripedJSONFile;
        }else if (currentChar == ' ') {
            if (valueStartFlag == 1) {
                ++sizeOfStripedJSONFile;
            }
        }
    }
    
    jsonFilePointer = buff;
    valueStartFlag = 0;
    char *stripedJSONContent = (char*) malloc(sizeof(char)*sizeOfStripedJSONFile);
    char const *stripedJSONContentDuplicate = stripedJSONContent;

    if(stripedJSONContent == NULL) {
        errnum = errno;
        fprintf(stderr, "Memory can't be allocated. %s", strerror(errnum));
        exit(0);
    }
    
    for(i = 0; i < (sizeof(char)*oldJSONFileResult); i++) {
        currentChar = *(jsonFilePointer++);
        
        if(currentChar == '"' && valueStartFlag == 0) {
            valueStartFlag = 1;
        }else if(currentChar == '"' && valueStartFlag == 1){
            valueStartFlag = 0;
        }

        if(currentChar != ' ') {
            *(stripedJSONContent++) = currentChar;
            printf("Adding striped content %c, at this address: %i\n", currentChar, (stripedJSONContent + i));
        }else if (currentChar == ' ') {
            if (valueStartFlag == 1) {
                *(stripedJSONContent++) = currentChar;
                printf("Adding striped content %c, at this address: %i\n", currentChar, (stripedJSONContent + i));
            }
        }
    }
    
    free(buff);
    
    for(i = 0; i < (sizeof(char)*sizeOfStripedJSONFile); i++) {
        printf("NEW STRIP -> %i --> the elem --> %c\n", (stripedJSONContentDuplicate + i), *(stripedJSONContentDuplicate + i));
    }

    fclose(oldJSONFile);
    
    return 0;
}