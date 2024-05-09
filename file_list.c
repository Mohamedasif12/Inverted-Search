#include "inverted_search.h" // Include the header file "inverted_search.h" to access function declarations and definitions.
#include "inverted_search.h" // Include the header file "inverted_search.h" again (repeated inclusion is typically avoided, but it doesn't harm).

void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i = 1, empty; // Declare integer variables 'i' and 'empty'.

    // Loop through the command-line arguments until NULL is encountered.
    while (argv[i] != NULL)
    {
        empty = isFileEmpty(argv[i]); // Call the 'isFileEmpty' function to check if a file is empty.

        if (empty == FILE_NOTAVAILABLE) // Check if the file is not available.
        {
            printf("FIle : %s is not available \n", argv[i]); // Print a message indicating the file is not available.
            printf("Hence we are not adding that file\n"); // Print a message indicating the file won't be added.
            i++; // Increment the index 'i'.
            continue; // Continue to the next iteration of the loop.
        }
        else if (empty == FILE_EMPTY) // Check if the file is empty.
        {
            printf("FIle : %s is not having any contents in it\n", argv[i]); // Print a message indicating the file is empty.
            printf("Hence we are not adding that file\n"); // Print a message indicating the file won't be added.
            i++; // Increment the index 'i'.
            continue; // Continue to the next iteration of the loop.
        }
        else // If the file is available and not empty.
        {
            int ret_val = to_create_list_of_files(f_head, argv[i]); // Call the 'to_create_list_of_files' function to add the file to a linked list.

            if (ret_val == SUCCESS) // Check if the operation to add the file was successful.
            {
                printf("Successful : inserting the file : %s into file linked list\n ", argv[i]); // Print a success message.
                break; // Exit the loop.
            }
            else if (ret_val == REPEATATION) // Check if the file is a duplicate.
            {
                printf("This file  : %s is repeated , Hence do not add into file linked list\n", argv[i]); // Print a message indicating the file is a duplicate.
                break; // Exit the loop.
            }
            else // Handle any other failure case.
            {
                printf("Failure\n"); // Print a generic failure message.
            }
        }
    }
}

// Function to check if a file is available or not and if it's empty.
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename, "r"); // Open the file in read mode.

    if (fptr == NULL) // Check if the file couldn't be opened.
    {
        if (errno == ENOENT) // Check if the error is due to the file not being available.
        {
            return FILE_NOTAVAILABLE; // Return a constant indicating that the file is not available.
        }
    }

    fseek(fptr, 0, SEEK_END); // Move the file pointer to the end of the file.
    if (ftell(fptr) == 0) // Check if the file pointer is at the beginning (indicating an empty file).
    {
        return FILE_EMPTY; // Return a constant indicating that the file is empty.
    }
}

// Function to create a list of files.
int to_create_list_of_files(Flist **f_head, char *name)
{
    Flist *new_file = (Flist *)malloc(sizeof(Flist)); // Allocate memory for a new file node.

    if (new_file == NULL) // Check if memory allocation failed.
    {
        printf("Memory allocation failed\n"); // Print an error message.
        return -1; // Return an error code indicating failure.
    }

    // Check for duplicate file names in the linked list.
    Flist *current = *f_head;
    while (current != NULL)
    {
        if (!strcmp(current->file_name, name)) // Check if the file name matches an existing file.
        {
            free(new_file); // Free the allocated memory for the new file node.
            return REPEATATION; // Return a constant indicating that the file is a duplicate.
        }
        current = current->link; // Move to the next node in the linked list.
    }

    strcpy(new_file->file_name, name); // Copy the file name to the new file node.
    new_file->link = NULL; // Initialize the next pointer of the new file node as NULL.

    if (*f_head == NULL) // Check if the linked list is empty.
    {
        *f_head = new_file; // Set the head of the linked list to the new file node.
    }
    else
    {
        current = *f_head; // Initialize 'current' to the head of the linked list.
        while (current->link != NULL) // Traverse the linked list to find the last node.
        {
            current = current->link;
        }
        current->link = new_file; // Add the new file node to the end of the linked list.
    }

    return SUCCESS; // Return a constant indicating success.
}

