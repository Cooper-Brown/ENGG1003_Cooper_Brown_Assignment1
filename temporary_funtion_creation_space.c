char crossReference(char **inputText, char **wordBank, char maxWords)
{ 
    char wordBankEditable[100]; // does not need clearing as it is copied to from another array

    // ___________cross references a word from input with every word in wordbank
    for (int word = 0; word < maxWords; word++)
    {
        if (inputText[word][0] == 0) // skips over the empty space left at the end of the array
            break;
        for (int wordBankWord = 0; wordBankWord < maxWords; wordBankWord++)
        {
            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], wordBank[wordBankWord]) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,".")) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,",")) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,"?")) == 0)
                return 1;

            strcpy(wordBankEditable, wordBank[wordBankWord]);
            if (strcmp(inputText[word], strcat(wordBankEditable,"!")) == 0)
                return 1;
    }
    return 0;
}






// ___________cross references a word from input with every word in wordbank
        for (int word = 0; word < maxWords; word++)
        {
            if (inputText[word][0] == 0) // skips over the empty space left at the end of the array
                break;
            for (int wordBankWord = 0; wordBankWord < maxWords; wordBankWord++)
            {
                strcpy(wordBankEditable, wordBank[wordBankWord]);
                if (strcmp(inputText[word], wordBank[wordBankWord]) == 0)
                {
                    hitFlag = 1;
                    hit++;
                    break;
                }

                strcpy(wordBankEditable, wordBank[wordBankWord]);
                if (strcmp(inputText[word], strcat(wordBankEditable,".")) == 0)
                {
                    hitFlag = 1;
                    hit++;
                    break;
                }

                strcpy(wordBankEditable, wordBank[wordBankWord]);
                if (strcmp(inputText[word], strcat(wordBankEditable,",")) == 0)
                {
                    hitFlag = 1;
                    hit++;
                    break;
                }

                strcpy(wordBankEditable, wordBank[wordBankWord]);
                if (strcmp(inputText[word], strcat(wordBankEditable,"?")) == 0)
                {
                    hitFlag = 1;
                    hit++;
                    break;
                }

                strcpy(wordBankEditable, wordBank[wordBankWord]);
                if (strcmp(inputText[word], strcat(wordBankEditable,"!")) == 0)
                {
                    hitFlag = 1;
                    hit++;
                    break;
                }
                
            }
            if (hitFlag != 1)
                noHit++;
            hitFlag = 0; 
        }