#include <stdio.h>
#include <string.h>

char inbuiltCommandSelector();

char inbuiltCommandSelector()
{
    const char * prntCommands = "commands",
                 task1 = "encode -rotation -key",
                 task2 = "decode -rotation -key",
                 task3 = "encode -substitution -key",
                 task4 = "decode -substitution -key",
                 task5 = "decode -rotation",
                 task6 = "decode -substitution";
    char command[100];

    printf("Please enter a command. (type commands for list of commands) \n > ");
    
    do 
    {
        scanf("%[^\n]s", command);

        if (strcmp(command, task1) == 0)
        {
            printf("> %s          =>     prints list of commands \n", prntCommands);
            printf("> %s          =>     encodes rotation cypher with key given \n", task1);
            printf("> %s          =>     decodes rotation cypher with key given \n", task2);
            printf("> %s          =>     encodes substitution cypher with key given \n", task3);
            printf("> %s          =>     decodes substitution cypher with key given \n", task4);
            printf("> %s          =>     decodes rotation cypher without key \n", task5);
            printf("> %s          =>     decodes substitution cypher without key \n", task6);
        } //else if (strcmp(command, task2))




    } while (1 == 1);
    
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        char task_number = inbuiltCommandSelector();
    } else 
    {
        printf("Yahoo");
    }

  

   return 0;
}


