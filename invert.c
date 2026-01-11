#include "main.h"

int create_database(file_list *head, main_node *database[]){
    if(head ==NULL){
        printf("No files to be processed\n");
        return FAILURE;
    }
    file_list *fptr = head;
    while(fptr!= NULL){
        FILE *fp = fopen(fptr->filename,"r");
        if(fp == NULL){
            fptr = fptr->link;
            continue;
        }
        char word[20];
        while(fscanf(fp,"%s",word)!=EOF){
            lowercase(word);
            if(strlen(word)>0){
                insert_word(database,word,fptr->filename);
            }
        }
        fclose(fp);
        fptr = fptr->link;
    }
    printf("Database created successfully\n");
    return SUCCESS;
}

int search_database(main_node *database[], char *word){
    int index = hash_function(word);
    main_node *m = database[index];
    while(m){
        if(strcmp(m->word,word)==0){
            printf("\n Word found at the index %d\n",index);
            printf("Word: %s | Files: %d \n",m->word,m->filecount);

            sub_node *s = m->sub_link;
            while(s){
                printf("   ->%s : %d\n",s->word,s->wordcount);
                s = s->sub_link;
            }
            return SUCCESS;
        }
        m = m->main_link;
    }
    printf("\nWord %s is not found in database\n",word);
    return FAILURE;
}

int update_database(main_node *database[], char *filename){
    if(file_exist(database,filename)==SUCCESS){
        printf("File %s already present in database.",filename);
        return FAILURE;
    }
    FILE *fp = fopen(filename,"r");
    if(fp == NULL){
        printf("Unable to open file %s\n",filename);
        return FAILURE;
    }
    char word[20];
    while(fscanf(fp,"%s",word)!= EOF){
        lowercase(word);
        if(strlen(word)>0){
            insert_word(database,word,filename);
        }
    }
    fclose(fp);
    printf("Database updated with file: %s\n",filename);
    return SUCCESS;
}

int save_database(main_node *database[]){
    char file[50];
    printf("Enter filename to save database: ");
    scanf("%s",file);

    FILE *fp = fopen(file,"w");
    if(fp == NULL){
        printf("Unable to create file\n");
        return FAILURE;
    }
    for(int i=0;i<TABLE_SIZE;i++){
        main_node *m = database[i];
        while(m){
            fprintf(fp,"# %d %s %d\n",i,m->word,m->filecount);
            sub_node *s = m->sub_link;
            while(s){
                fprintf(fp,"%s %d\n",s->word,s->wordcount);
                s = s->sub_link;
            }
            fprintf(fp,"\n");
            m = m->main_link;
        }
    }
    fclose(fp);
    printf("Database saved successfully to %s\n",file);
    return SUCCESS;
}

void display_database(main_node *database[]){
    printf("\n-----DATABASE-----\n");
    for(int i=0; i < TABLE_SIZE;i++){
        main_node *m = database[i];
        while(m){
            printf("%d Word: %-18s | Files: %d\n",i,m->word,m->filecount);
            sub_node *s = m->sub_link;
            while(s){
                printf("   ->%s | %d\n",s->word,s->wordcount);
                s = s->sub_link;
            }
            m = m->main_link;
        }
    }
}