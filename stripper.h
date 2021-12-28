#include <stdlib.h>

int valueStartFlag = 0;
char currentChar;
int i;

// Determin the size of the json object when stripped
int getStrippedSize(size_t oldJSONFileSize, char *oldJSONFilePointer)
{   
    int strippedJSONObjectSize = 0;

    for (i = 0; i < (sizeof(char) * oldJSONFileSize); i++)
    {
        currentChar = *(++oldJSONFilePointer);

        if (currentChar == '"' && valueStartFlag == 0)
        {
            valueStartFlag = 1;
        }
        else if (currentChar == '"' && valueStartFlag == 1)
        {
            valueStartFlag = 0;
        }

        if (currentChar != ' ')
        {
            ++strippedJSONObjectSize;
        }
        else if (currentChar == ' ')
        {
            if (valueStartFlag == 1)
            {
                ++strippedJSONObjectSize;
            }
        }
    }

    return strippedJSONObjectSize;
}

// Create the stripped json object
char *createStrippedJSONObject(size_t oldJSONFileSize, char *oldJSONFilePointer)
{   
    // Calculate the size of the stripped JSON object
    int strippedJSONObjectSize = getStrippedSize(oldJSONFileSize, oldJSONFilePointer);

    printf("Striped size: %i", strippedJSONObjectSize);

    // Reset the value start flag
    valueStartFlag = 0;

    // Reserve memory for the stripped JSON object
    char *stripedJSONContent = (char*) malloc(sizeof(char)*strippedJSONObjectSize);
    char *originalStrippedJSONContent = stripedJSONContent;
    
    for (i = 0; i < (sizeof(char) * oldJSONFileSize); i++)
    {
        currentChar = *(oldJSONFilePointer++);

        if (currentChar == '"' && valueStartFlag == 0)
        {
            valueStartFlag = 1;
        }
        else if (currentChar == '"' && valueStartFlag == 1)
        {
            valueStartFlag = 0;
        }

        if (currentChar != ' ')
        {
            *(stripedJSONContent++) = currentChar;
        }
        else if (currentChar == ' ')
        {
            if (valueStartFlag == 1)
            {
                *(stripedJSONContent++) = currentChar;
            }
        }
    }

    return originalStrippedJSONContent;
}