#include "inverted_search.h"     // Include the header file "inverted_search.h"
// Function to display the database
void display_database(Wlist *head[])
{
    // Print header row with column labels
    printf("%-8s %-8s %-12s %-15s %-15s %-12s\n", "[index]", "[word]", "file_count", "file/s", "File:", "word_count");

    // Loop through the array of pointers
    for (int i = 0; i < 27; i++)
    {
        // Check if the current index of the array is not NULL
        if (head[i] != NULL)
        {
            // Call the print_word_count function for the current index
            print_word_count(head[i]);
        }
    }
}

// Function to print word count details
int print_word_count(Wlist *head)
{
    // Traverse through the linked list pointed to by 'head'
    while (head != NULL)
    {
        // Calculate the index for the word based on its first character
        // and use modulo 27 (not 97 as in the commented line)
        printf("%-8d %-8s %-12d %-15s ", tolower(head->word[0]) % 27, head->word, head->file_count, "file/s");

        Ltable *Thead = head->Tlink;  // Create a pointer to traverse the Ltable linked list

        // Traverse the Ltable linked list
        while (Thead)
        {
            // Print the file name and word count
            printf("%-15s %-12d ", Thead->file_name, Thead->word_count);
            Thead = Thead->table_link;  // Move to the next Ltable node
        }
        printf("\n");  // Print a newline to separate entries
        head = head->link;  // Move to the next word in the Wlist linked list
    }
}

