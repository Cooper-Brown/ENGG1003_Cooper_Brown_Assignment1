#include <stdio.h>
#include <string.h>

// This function 
int inbuiltCommandSelector();

int inbuiltCommandSelector()
{
    const char prntCommands[] = "commands",
                 task1[] = "encode -rotation -key",
                 task2[] = "decode -rotation -key",
                 task3[] = "encode -substitution -key",
                 task4[] = "decode -substitution -key",
                 task5[] = "decode -rotation",
                 task6[] = "decode -substitution";
    char command[100];
    int taskNumber = 0;

    printf("Please enter a command. (type commands for list of commands) \n> ");
    
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

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        char taskNumber = inbuiltCommandSelector();
    } else 
    {
        printf("Yahoo");
    }

  

   return 0;
}


