#include <stdio.h>
#include <string.h>

void main()
{
    const char * instruction1 = "commands";
    char command[100];
    printf("Please enter a command. (type commands for list of commands) \n > ");
    scanf("%[^\n]s", command);
    // printf("%s", command); // for testing if the input was entered correctly
    if (strcmp(command,instruction1) == 0)
    {
        printf("commands =>     gets list of commands \n");
        printf("encode =>     gets list of commands \n");
        printf("commands =>     gets list of commands \n");
    }

    /*
	char text[100];
	printf("Enter text to process: ");
	scanf("%s", text); // alternatively &text[0]
    */

}


