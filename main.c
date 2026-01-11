/*
Name : Krishna V Prem
Date : 15-12-2025
Project Title : INVERTED SEARCH
Description : This project implements an inverted search system using a hash table to index words from multiple text files. 
              Each word is hashed and stored along with the list of files in which it appears and its frequency. 
              Collisions are handled using linked lists, and words are normalized to ensure consistent searching. 
              The system supports creating, searching, updating, displaying, and saving the database efficiently.
*/

#include "main.h"

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Insufficent arguments!! Please enter filenames in order\n");
        help();
        return FAILURE;
    }

    file_list *head  = NULL;
    file_list *tail  = NULL;
    int valid_files =0;
    for(int i=1;i<argc;i++){
        if(validate(argv[i])==FAILURE){
            printf("Invalid file: %s\n",argv[i]);
            help();
            return FAILURE;
        }
        if(head != NULL){
            file_list *temp = head;
            int dup =0;
            while(temp){
                if(strcmp(temp->filename,argv[i])==0){
                    printf("Duplicate file %s: ",argv[i]);
                    dup =1;
                    break;
                }
                temp = temp->link;
            }
            if(dup){
                continue;
            }
        }
        file_list *new = malloc(sizeof(file_list));
        if(new == NULL){
            printf("Memory allocation failed\n");
            clean_list(head);
            return FAILURE;
        }
        strncpy(new->filename,argv[i],MAX_FILENAME_LEN -1);
        new->filename[MAX_FILENAME_LEN-1] = '\0';
        new->link = NULL;
        if(head == NULL){
            head = tail = new;
        }
        else{
            tail->link = new;
            tail = new;
        }
        valid_files++;
    }
    if(valid_files == 0){
        printf("No valid files provided\n");
        help();
        return FAILURE;
    }
    int database_created =0;
    main_node *database[TABLE_SIZE] = {NULL};
    int option;

    do{
        printf("1. Create Database\n");
        printf("2. Search Database\n");
        printf("3. Display Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Enter the choice:");
        scanf("%d",&option);

        switch(option){
            case 1:{
                if(database_created){
                    printf("Database already created\n");
                }
                else{
                    create_database(head,database);
                    database_created = 1;
                }
                break;
            }
            case 2:{
                if(database_created ==0){
                    printf("Create database first\n");
                    break;
                }
                char word[MAX_WORD_LEN];
                printf("Enter word to search: ");
                scanf("%s",word);
                lowercase(word);
                search_database(database,word);
                break;
            }
            case 3:
                if(database_created ==0){
                    printf("Create database first\n");
                    break;
                }
                display_database(database);
                break;
            case 4:{
                if(database_created ==0){
                    printf("Create database first\n");
                    break;
                }
                char filename[MAX_FILENAME_LEN];
                printf("Enter the filename to update: ");
                scanf("%s",filename);
                if(validate(filename)==FAILURE){
                    printf("Invalid file format\n");
                }
                else{
                    update_database(database,filename);
                }
                break;
            }
            case 5:
                if(database_created ==0){
                    printf("Create database first\n");
                    break;
                }
                save_database(database);
                break;
            case 6:{
                clean_database(database);
                clean_list(head);
                return SUCCESS;
            }
        }
    }while (option != 6);

    clean_database(database);
    clean_list(head);
    return SUCCESS;
}