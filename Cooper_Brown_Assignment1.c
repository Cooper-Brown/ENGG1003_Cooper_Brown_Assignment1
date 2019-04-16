// ___________________________________________________ IMPORTED LIBRARIES ___________________________________________________ //
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // contains tolower() and toupper() functions

// ___________________________________________________ FUNCTION PROTOTYPES ___________________________________________________ //

char getTaskAndKey(char *rotationKey, char *substitutionKey);



// ___________________________________________________________ MAIN _________________________________________________________ //
int main()
{
    char taskNumber = 0;
    char rotationKey











    return 0;
}



// _______________________________________________________ FUNCTIONS _________________________________________________________ //

char getTaskAndKey(char *rotationKey, char *substitutionKey)
{
    FILE *keyFile;
    char command[100];
    char taskNumber = 0;
    
    keyFile = fopen("keyFile.txt", "r");

    if (keyFile == NULL)
    {
        printf("Error: keyFile.txt is not in the current directory\n");
        return 0;
    }

    fscanf(keyFile, "%s", command);
    if (tolower(command) == "encode")
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            taskNumber = 1;
        else if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
            taskNumber = 3;
        else
            printf("Error: cannot encode without a valid key.\n");
    }
    else if (tolower(command) == "decode")
    {
        if (fscanf(keyFile, "%*[^:]%*2c%2d", rotationKey) == 1)
            if (*rotationKey > 26 || *rotationKey < 0)
            {
                printf("Error: key is out of range");
                taskNumber = 0;
            }
            else
                taskNumber = 2;
        else if (fscanf(keyFile, "%*[^:]%*2c%26c", substitutionKey) == 1)
            taskNumber = 4;
        else
            printf("Could not detect a valid key. Attempting to decode without one...\n");
            taskNumber = 7;
    }
    else
        printf("1st line (the command header) of keyFile.txt is formatted incorrectly.\nIt should either be 'encode' or 'decode'.\n");
    //fclose(keyFile);
    return taskNumber;   
}