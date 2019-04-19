char get2DArrayFromFile(char *inputText)    
    FILE *inputFile;
    char inputCharacter;
    int word = 0, letter = 0;


    inputFile = fopen("inputFile.txt", "r");

    if (inputFile == NULL)
    {
        printf("Error: inputFile.txt is not in the current directory");
        return 0;
    }

    word = 0;
    letter = 0;
    while (fscanf(inputFile, "%c", &inputCharacter) == 1)
    {
        inputText[word][letter] = inputCharacter;
        if (inputCharacter == 32)
        {
            word++;
            letter = 0;
        }
        else
            letter++;
        
    }
    inputText[word][letter] = 0;
    //fclose()
    return 1;