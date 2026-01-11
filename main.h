#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define TABLE_SIZE 101
#define MAX_WORD_LEN 50
#define MAX_FILENAME_LEN 100

typedef enum Status{
    SUCCESS,
    FAILURE
}Status;

typedef struct node{
    char filename[MAX_FILENAME_LEN];
    struct node *link;
}file_list;

typedef struct sub{
    char word[MAX_FILENAME_LEN];
    int wordcount;
    struct sub *sub_link;
}sub_node;

typedef struct main{
    char word[MAX_WORD_LEN];
    int filecount;
    struct main *main_link;
    struct sub *sub_link;

}main_node;


int help();
int validate(const char *str);
int hash_function(const char *word);
void lowercase(char *word);
void display_database(main_node *database[]);
int insert_word(main_node *database[], const char *word, const char *filename);
int create_database(file_list *head, main_node *database[]);
int search_database(main_node *database[], char *word);
int save_database(main_node *database[]);
int update_database(main_node *database[], char *filename);
int file_exist(main_node *database[], char *filename);
main_node* create_main_node(const char *word);
sub_node* create_sub_node(const char *filename);
main_node* search_word(main_node *head, const char *word);
sub_node* search_file(sub_node *head, const char *filename);
void clean_database(main_node *database[]);
void clean_list(file_list *head);

#endif

