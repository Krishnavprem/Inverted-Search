#include "main.h"

int hash_function(const char *word){
    unsigned int hash =0;
    while(*word){
        hash = (hash *31 +*word) % TABLE_SIZE;
        word++;
    }
    return hash;
}

main_node* create_main_node(const char *word){
    main_node *new = malloc(sizeof(main_node));
    if(new == NULL){
        printf("Memory allocation failed for main node\n");
        return NULL;
    }
    strncpy(new->word,word,MAX_WORD_LEN-1);
    new->word[MAX_WORD_LEN -1] ='\0';
    new->filecount = 1;
    new->main_link = NULL;
    new->sub_link = NULL;
    return new;
}
sub_node* create_sub_node(const char *filename){
    sub_node *new = malloc(sizeof(sub_node));
    if(new == NULL){
        printf("Memory allocation failed for sub node\n");
        return NULL;
    }
    strncpy(new->word,filename,MAX_FILENAME_LEN-1);
    new->word[MAX_FILENAME_LEN -1] = '\0';
    new->wordcount = 1;
    new->sub_link = NULL;
    return new;
}

main_node *search_word(main_node *head, const char *word){
    main_node *temp = head;
    while(temp!=NULL){
        if(strcmp(temp->word,word)==0){
            return temp;
        }
        temp = temp->main_link;
    }
    return NULL;
}
sub_node *search_file(sub_node *head , const char *filename){
    sub_node *temp = head;
    while(temp != NULL){
        if(strcmp(temp->word,filename)==0){
            return temp;
        }
        temp =temp->sub_link;

    }
    return NULL;
}

int insert_word(main_node *database[], const char *word, const char *filename){
    if(strlen(word)==0){
        return SUCCESS;
    }
    int index = hash_function(word);
    main_node *mnode = search_word(database[index],word);
    if(mnode == NULL){
        main_node *new_main = create_main_node(word);
        if(new_main==NULL){
            return FAILURE;
        }
        sub_node *new_sub = create_sub_node(filename);
        if (new_sub == NULL){
            free(new_main);
            return FAILURE;
        }

        new_main->sub_link = new_sub;
        new_main->main_link = database[index];
        database[index] = new_main;
    }
    else{
        sub_node *snode = search_file(mnode->sub_link,filename);
        if(snode != NULL){
            snode->wordcount++;
        }
        else{
            sub_node *new_sub = create_sub_node(filename);
            new_sub->sub_link = mnode->sub_link;
            mnode->sub_link = new_sub;
            mnode->filecount++;
        }
    }
    return SUCCESS;
}

int validate(const char *str)
{
    int len = strlen(str);
    if(len<4){
        return FAILURE;
    }
    if(strcmp(&str[len-4],".txt")==0){
        return SUCCESS;
    }
    return FAILURE;
}

int help(){
    printf("Correct input format: \n");
    printf("./a.out <file1.txt> <file2.txt> <file3.txt>\n");
    return SUCCESS;
}

int file_exist(main_node *database[], char *filename){
    for(int i=0;i<TABLE_SIZE;i++){
        main_node *m = database[i];
        while(m){
            sub_node *s = m->sub_link;
            while(s){
                if(strcmp(s->word,filename)==0){
                    return SUCCESS;
                }
                s = s->sub_link;
            }
            m = m->main_link;
        }
    }
    return FAILURE;
}

void clean_database(main_node *database[]){
    for(int i=0;i<TABLE_SIZE;i++){
        main_node *m = database[i];
        while(m){
            main_node *next_m = m->main_link;
            sub_node *s = m->sub_link;
            while(s){
                sub_node *next_s = s->sub_link;
                free(s);
                s =next_s;
            }
            free(m);
            m = next_m;
            database[i] = NULL;
        }
    }
}

void clean_list(file_list *head){
    file_list *temp = head;
    while(temp){
        file_list *next = temp->link;
        free(temp);
        temp =next;
    }
}

void lowercase(char *word){
    int i=0,j;
    while(word[i]){
        word[i] = tolower((unsigned char)word[i]);
        i++;
    }
    i=0;
    while(word[i] && !isalnum((unsigned char)word[i])){
        i++;
    }
    j = strlen(word)-1;
    while(j>=i && !isalnum((unsigned char)word[j])){
        j--;
    }
    int k =0;
    while(i <=j){
        word[k++] = word[i++];
    }
    word[k] = '\0';
}