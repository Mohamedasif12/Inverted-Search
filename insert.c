#include "inverted_search.h"  // Include the header file inverted_search.h
char *fname;
int insert_at_last(Wlist **head, data_t *data)
{
    // Create a new node for Wlist
    Wlist *new = malloc(sizeof(Wlist));

    // Check if memory allocation was successful
    if (new == NULL)
        return FAILURE;

    // Update the new node with data
    new->file_count = 1;
    strcpy(new->word, data);
    new->Tlink = NULL;
    new->link = NULL;

    // Call the update_link_table function to update the link table

    update_link_table(&new);

    // Check if WList is empty or not

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    // Non-empty case

    Wlist *temp = *head;

    // Traverse through WList

    while (temp->link)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int update_link_table(Wlist **head)
{
    // Create a new node for Ltable
    Ltable *new = malloc(sizeof(Ltable));

    // Check if memory allocation was successful

    if (new == NULL)
        return FAILURE;

    // Update the new node with data
    new->word_count = 1;

    // Set the file_name for the new Ltable node (example: me holds "file1.txt")
    strcpy(new->file_name, fname);

    new->table_link = NULL;

    // Update the Tlink of the head node in WList to point to the new Ltable node
    (*head)->Tlink = new;
    return SUCCESS;
}

