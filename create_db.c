#include "inverted_search.h" // Include the header file for this module

char *fname; // This line is commented out, not sure why it's here, let's leave it for reference

// Function to create a database for a list of files
void create_database(Flist *f_head, Wlist *head[])
{
    while (f_head)
    {
        // Read data from a file and populate the database
        read_datafile(f_head, head, f_head->file_name);
        printf("Successful: Creation of database for file %s \n", f_head->file_name);
        f_head = f_head->link; // Move to the next file in the list
    }
}

// Function to read data from a file and populate the word list
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    FILE *fptr = fopen(filename, "r"); // Open the file for reading

    // Check if the file could be opened successfully
    if (!fptr)
    {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    fname = filename;    //store filename in the global variable fname
    int flag; // Initialize flag inside the loop
    char word[WORD_SIZE];

    // Read words from the file and insert them into the word list
    while (fscanf(fptr, "%s", word) != EOF)
    {
        int index = tolower(word[0]) % 97;
        if (!(index >= 0 && index <= 25))
            index = 26;

        flag = 1; // Reset the flag for each new word

        if (flag == 1)
        {
            insert_at_last(&head[index], word);
        }
    }
    
    fclose(fptr); // Close the file
    return NULL; // Return some meaningful value if needed
}

// Function to update the word count in a word list
int update_word_count(Wlist **head, char *file_name)
{
    Wlist *curr = *head;
    while (curr != NULL)
    {
        if (strcmp(curr->word, file_name) == 0) // Compare with file_name, not fname
        {
            update_word_count_in_table(&(curr->Tlink), file_name);
            return 1; // Found the word, return 1 to indicate success
        }
        curr = curr->link; // Move to the next word
    }
    return 0; // Word not found, return 0
}

// Function to update the word count in a table
void update_word_count_in_table(Ltable **table_head, char *file_name)
{
    Ltable *curr = *table_head;
    while (curr != NULL)
    {
        if (strcmp(curr->file_name, file_name) == 0)
        {
            curr->word_count++; // Increment the word count
            return;
        }
        curr = curr->table_link; // Move to the next table entry
    }

    // Create a new table entry if the filename is not found
    Ltable *new_node = (Ltable *)malloc(sizeof(Ltable));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(new_node->file_name, file_name); // Copy the filename
    new_node->word_count = 1; // Initialize the word count
    new_node->table_link = *table_head; // Link to the current table
    *table_head = new_node; // Update the table head
}

