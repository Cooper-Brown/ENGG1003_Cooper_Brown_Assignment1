#include <stdio.h>
#include <string.h>

// This function 
int inbuiltCommandSelector();

int getRotationKey();

int getRotationKey()
{
    // it is specified that the key will be between -26 and 26. 27 is outside this range,
    // so key is invalid by default. Key only becomes valid if a valid key is entered
    __int128_t fileData[3];
    char fileData[10] = '0';
    char *fileDataIndicator;
    char key = 0;

    FILE *keyFile;

    keyFile = fopen("keyFile.txt", "r");
    fscanf(keyFile, "%s", fileData);
    fclose(keyFile);

    printf("%s", fileData);

    
    key = (char) atoi(fileData);

    return key;
}






int cliCommandSelector(int argc, char *argv[]);

char encodeRotationWithKey();


/*
char encodeRotationWithKey()
{

    char lineOfInput[400], key=0;
    FILE *inputFile;

    key = caesarKeyFromFile();
    printf("Before returns");

    if ((key < -26) || (key > 26))
    {
        return 0;
    }


    inputFile = fopen("inputFile.txt", "r");
    printf("Before Loop");
    while (!feof(inputFile))
    {
        fscanf(inputFile, "%s", lineOfInput);
        printf("File Contents: %d", lineOfInput);
    }
    
    fclose(inputFile);

    return 1;
}
*/

int main(int argc, char *argv[])
{

    char taskNumber = 1;

    //taskNumber = inbuiltCommandSelector();

    switch (taskNumber) {
        case 1 :
            ; // declarations cannot be placed directly after a label
            char key = 0;
            key = getRotationKey();
            /*
            if (encryptFileR(key) == 1)
                printf("Encryption Successful\n");
            else
                printf("Encryption Failed\n");
            break;
            */
    return 0;

    }
    
    










    

  

   return 0;
}













int inbuiltCommandSelector()
{
    const char prntCommands[] = "-arguements",
                 task1[] = "-encode -rotation -key",
                 task2[] = "-decode -rotation -key",
                 task3[] = "-encode -substitution -key",
                 task4[] = "-decode -substitution -key",
                 task5[] = "-decode -rotation",
                 task6[] = "-decode -substitution";
    char command[100];
    int taskNumber = 0;

    printf("Arguements not given/incorrect. Please enter them here instead. (type -arguements for list of options) \n> ");
    
    do 
    {
        // takes input up until a newline character
        // Note space in front to ensure the last newline character isn't read
        scanf(" %[^\n]s", command);
            
        // strcmp(command, prntCommands) == 0 when the strings command and prntCommands are equal
        if (strcmp(command, prntCommands) == 0)
        {
            printf("\n \n");
            printf("> %s          =>     prints list of commands \n \n", prntCommands);
            printf("> %s          =>     encodes rotation cypher with key given \n \n", task1);
            printf("> %s          =>     decodes rotation cypher with key given \n \n", task2);
            printf("> %s          =>     encodes substitution cypher with key given \n \n", task3);
            printf("> %s          =>     decodes substitution cypher with key given \n \n", task4);
            printf("> %s          =>     decodes rotation cypher without key \n \n", task5);
            printf("> %s          =>     decodes substitution cypher without key \n \n", task6);
            printf("> ");
        } else if (strcmp(command, task1) == 0)
            taskNumber = 1;
        else if (strcmp(command, task2) == 0)
            taskNumber = 2;
        else if (strcmp(command, task3) == 0)
            taskNumber = 3;
        else if (strcmp(command, task4) == 0)
            taskNumber = 4;
        else if (strcmp(command, task5) == 0)
            taskNumber = 5;
        else if (strcmp(command, task6) == 0)
            taskNumber = 6;
        else 
            printf("Invalid Command \n> ");
        
    } while (taskNumber == 0);
    
    return taskNumber;
}

int cliCommandSelector(int argc, char *argv[])
{
    const char  ARG1[] = "-encode",
                ARG2[] = "-decode",
                ARG3[] = "-substitution",
                ARG4[] = "-rotation",
                ARG5[] = "-key",
                ARG6[] = "-nokey";


    if (argc == 1)
    {
        char taskNumber = inbuiltCommandSelector();
    } else 
    {
        //do something with the arguements
    }


    return 0;
}
