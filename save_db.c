#include "inverted_search.h"

// Declare the write_database function prototype
void write_database(Wlist *head, FILE *databasefile);

// Define the save_db function
void save_db(Wlist *head[])
{
    // Prompt the user to enter the file name for saving the database
    char file_name[FNAME_SIZE];
    printf("Enter the file name where you want to save the data : ");
    scanf("%s", file_name);

    // Open the specified file for writing
    FILE *fptr = fopen(file_name, "w");
    if (fptr == NULL)
    {
        // Print an error message if the file couldn't be opened
        perror("fopen");
        return;
    }

    // Iterate over the array of Wlist pointers (assuming there are 27 elements)
    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            // Call the write_database function to write data to the file
            write_database(head[i], fptr);
        }
    }

    // Close the file
    fclose(fptr);
    
    // Print a success message
    printf("Database saved successfully\n");
}

// Define the write_database function
void write_database(Wlist *head, FILE *databasefile)
{
    // Iterate through the linked list pointed to by 'head'
    while (head != NULL)
    {
        // Write data to the specified file using fprintf
        fprintf(databasefile, "#[%d] word is [%s]: file is [%d]:files/s: file is [%s] word count is [%d]\n",
                head->file_count, head->word, head->file_count,
                head->Tlink->file_name, head->Tlink->word_count);

        // Move to the next node in the linked list
        head = head->link;
    }
}

