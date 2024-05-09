// Define include guards to prevent multiple inclusion of this header
#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

// Include necessary standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

// Define some macros for error codes and sizes
#define FAILURE -1
#define SUCCESS 0
#define FNAME_SIZE 15
#define WORD_SIZE 10
#define FILE_EMPTY -2
#define FILE_NOTAVAILABLE -3
#define REPEATATION -4

// Define a data type for the character type used in the data structures
typedef char data_t;

// Define a structure for the linked list of file names
typedef struct file_node
{
    data_t file_name[FNAME_SIZE];
    struct file_node *link;
} Flist;

// Define a structure for the linked list of link tables
typedef struct linkTable_node
{
    int word_count;
    data_t file_name[FNAME_SIZE];
    struct linkTable_node *table_link;
} Ltable;

// Define a structure for the linked list of words
typedef struct word_node
{
    int file_count;
    data_t word[WORD_SIZE];
    Ltable *Tlink;
    struct word_node *link;
} Wlist;

// Function prototypes

// Create a list of files
int to_create_list_of_files(Flist **f_head, char *name);

// Create the database
void create_database(Flist *f_head, Wlist *head[]);

// Read the contents of a file and update the database
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename);

// Insert a node at the end of the linked list
int insert_at_last(Wlist **head, data_t *data);

// Update the link table
int update_link_table(Wlist **head);

// Update the word count in the database
int update_word_count(Wlist **head, char *file_name);

// Print word counts in the database
int print_word_count(Wlist *head);

// Search for a word in the database
void search(Wlist *head, char *word);

// Display the database
void display_database(Wlist *head[]);

// Save the database to a file
void save_db(Wlist *head[]);

// Write data to the database file
void write_databasefile(Wlist *head, FILE *databasefile);

// Update the database based on the file list
void update_database(Wlist *head[], Flist *f_head);

// Check if a file is empty
int isFileEmpty(char *filename);

// Validate file existence and populate the file list
void file_validation_n_file_list(Flist **f_head, char *argv[]);

// Update the word count in the link table
void update_word_count_in_table(Ltable **table_head, char *file_name);

#endif // End of include guards


