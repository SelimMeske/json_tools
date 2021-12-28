#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "stripper.h"

int main()
{
    FILE *oldJSONFile;
    char jsonChar;
    int errnum;
    char *buff;
    long oldFileSize;
    size_t oldJSONFileResult;

    oldJSONFile = fopen("test.json", "rb");

    if (oldJSONFile == NULL)
    {
        errnum = errno;
        printf("File can not be found: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
    }
    else
    {
        // Obtain the size of the first json file
        fseek(oldJSONFile, 0, SEEK_END);
        oldFileSize = ftell(oldJSONFile);
        rewind(oldJSONFile);

        // Allocate memory
        buff = (char *)malloc(sizeof(char) * oldFileSize);
        if (buff == NULL)
        {
            errnum = errno;
            fprintf(stderr, "Memory error: %s\n", strerror(errnum));
        };

        // Read the file as binary
        oldJSONFileResult = fread(buff, 1, oldFileSize, oldJSONFile);
        printf("SIZE OF OJFR: %i\n SIZE OF OFZ %i\n", oldJSONFileResult, oldFileSize);
        if (oldJSONFileResult != oldFileSize)
        {
            errnum = errno;
            fprintf(stderr, "Reading file error: %s\n", strerror(errnum));
        };
    }

    int i;
    int sizeOfStripedJSONFile = 0;
    char *jsonFilePointer = buff;
    jsonFilePointer = buff;
    char *strippedJSONObject;

    
    // Create the stripped json object
    strippedJSONObject = createStrippedJSONObject(oldJSONFileResult, jsonFilePointer);
    if (strippedJSONObject == NULL) {
        printf("Error stripping the json file");
    }
    int strippedLength = getStrippedSize(oldJSONFileResult, jsonFilePointer);
    

    for (i = 0; i < (sizeof(char) * strippedLength); i++)
    {
        printf("Stripped JSON CHAR: %c\n", *(strippedJSONObject++));
    }
    
    free(buff);
    fclose(oldJSONFile);

    return 0;
}