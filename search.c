#include "inverted_search.h"  // Include the header file for function declarations.

void search(Wlist *head, char *word)
{   
    printf("Enter the word that you want to find : ");
    scanf("%s", word);  // Prompt the user for input and read the search word.

    // Check if the list is empty or not.
    if (head == NULL)
    {
        printf("Searching failed as the list was empty\n");
        return;
    }

    // Non-empty list - traverse the list.
    while (head)
    {
        // Compare the search word with available words in the list.
        if (!strcmp(head->word, word))
        {
            printf("Word %s is present in %d file/s\n", word,
                   head->file_count);

            // Traverse the Ltable associated with the current word.
            Ltable *Thead = head->Tlink;
            while (Thead)
            {
                printf("In file : %s  %d time/s \n", Thead->file_name,
                       Thead->word_count);
                Thead = Thead->table_link;
            }
            printf("\n");
            return;  // Word found, so exit the function.
        }
        head = head->link;  // Move to the next node in the list.
    }
    // If the loop finishes without finding the word, it's not in the list.
    printf("Search word is not found in the list\n");
}

