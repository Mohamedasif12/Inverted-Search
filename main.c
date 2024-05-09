/*Documentation*/
/*
Name : Babu Malagaveli
Date : 09.09.2023
Desc :
The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query. Without an index, the search engine would scan every document in the corpus, which would require considerable time and computing power

Prerequisite : Hashing
	       Single linked list
*/
#include "inverted_search.h"    // Include the header file "inverted_search.h" to use its functions

int main (int argc, char *argv[])
{
    // Clear the console (commented out).
    // Initialize an array of linked list pointers with 27 elements and set them to NULL.
    Wlist *head[27] = {0};

    // Validate the command-line arguments (CLA).
    if (argc <= 1)
    {
        printf ("Enter the valid number of arguments\n");
        printf ("Usage : ./Slist.exe  f1.txt f2.txt...\n");
        return 0;
    }

    // Create a linked list to store file information.

    // Declare a pointer to the file linked list.
    Flist *f_head = NULL;

    // Validate the files specified in command-line arguments and create a file linked list.
    file_validation_n_file_list (&f_head, argv);

    // Check if no files are available in the file linked list.
    if (f_head == NULL)
    {
        printf ("No files are available in the file linked list\n");
        printf ("Hence the process is terminated\n");
        return 1;
    }

    int choice, flag = 0;
    char word[WORD_SIZE];

    do
    {
        // Display the menu options to the user.
        printf ("Select your choice among the following options:\n");
        printf ("1. Create DATABASE\n");
        printf ("2. Display Database\n");
        printf ("3. Update DATABASE\n");
        printf ("4. Search\n");
        printf ("5. Save Database\n");
        printf ("6. Exit\n");
        printf ("Enter your choice: ");
        scanf ("%d", &choice);

        // Handle user's choice using a switch statement.
        switch (choice)
        {
            case 1:
                create_database (f_head, head);  // Call a function to create a database.
                break;
            case 2:
                display_database (head);        // Call a function to display the database.
                break;
            case 3:
                update_database (head, f_head); // Call a function to update the database.
                break;
            case 4:
                search(*head, word);            // Call a function to perform a search.
                break;
            case 5:
                save_db(head);                  // Call a function to save the database.
                break;
            default:
                printf ("Invalid choice! Please select a valid option.\n");
        }

        char ch;
        printf("Do you want to continue?\nIf yes, enter Y/y; else, N/n: ");
        scanf(" %c", &ch); // Note the space before %c

        if (ch == 'Y' || ch == 'y')
        {
            flag = 1; // Set flag to 1 to continue the loop.
        }
        else if (ch == 'N' || ch == 'n')
        {
            printf("Exiting...\n");
            flag = 0; // Set flag to 0 to exit the loop.
        }
        else
        {
            printf("Invalid choice. Please enter Y/y or N/n.\n");
        }
    }
    while (flag);

    return 0;
}

