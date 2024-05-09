#include "inverted_search.h"      // Include the header file "inverted_search.h" for function prototypes and declarations.

void update_database(Wlist *head[], Flist *f_head)
{
    // Prompt the user to enter the name of the file to update the database.
    char file_name[FNAME_SIZE];
    printf("Enter the file name to update the db: ");
    scanf("%s", file_name);
    //fgets(file_name, FNAME_SIZE, stdin); // Use fgets for safer input

    file_name[strcspn(file_name, "\n")] = '\0'; // Remove newline character if present.

    // Initialize a variable to count the number of iterations.
    int i;

    // Check if the file is empty or not available.
    int empty = isFileEmpty(file_name);
    if (empty == FILE_NOTAVAILABLE) {
        printf("File: %s is not available\n", file_name);
        printf("Hence we are not adding that file\n");
        i++;
        // continue; // This is commented out; there's no loop to continue.
    } else if (empty == FILE_EMPTY) {
        printf("File: %s is not having any contents in it\n", file_name);
        printf("Hence we are not adding that file\n");
        i++;
        // continue; // This is commented out; there's no loop to continue.
    } else {
        // Attempt to create a list of files and check the return value.
        int ret_val = to_create_list_of_files(&f_head, file_name);

        if (ret_val == SUCCESS) {
            printf("Successful: Inserting the file: %s into the file linked list\n", file_name);
            // break; // This is commented out; there's no loop to break.
        } else if (ret_val == REPEATATION) {
            printf("This file: %s is repeated, hence do not add it to the file linked list\n", file_name);
            // break; // This is commented out; there's no loop to break.
            return; // Exit the function in case of repetition.
        } else {
            printf("Failure\n");
        }
    }

    // Iterate over the file linked list.
    while (f_head) {
        if (strcmp(f_head->file_name, file_name) == 0) {
            FILE *file = fopen(file_name, "r");
            if (file) {
                create_database(f_head, head); // Pass f_head directly to create_database.
                fclose(file);
                break; // Exit the loop after processing the desired file.
            } else {
                // perror("Error opening file");
                perror("Error opening file"); // Display an error message using perror.
            }
        }
        f_head = f_head->link; // Move to the next node in the linked list.
    }
}

