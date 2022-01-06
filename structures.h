#include <string.h>
#include <ctype.h>

#define FILES_TXT "files.txt"
#define ALPHABET_SIZE 26
#define delimiters " .,!';:()"

#pragma once
struct file_occurance
{
    char files_name[101];
    int name_occurance;
    int content_occurance;
    file_occurance *ptr;
};

struct txt_file
{
    char name[101];
    char content[2001];
};

struct node
{
    node *ptr[ALPHABET_SIZE];
    bool is_end;
    file_occurance *data;
};
node* get_node()
{
    node *t=new node;
    t->is_end=false;
    t->data=nullptr;
    int i;
    for(i=0;i<ALPHABET_SIZE;i++)
    {
        t->ptr[i]=nullptr;
    }
    return t;
}

void lower_word(char word[])
{
    int i;
    for(i=0;i<strlen(word);i++)
    {
        word[i]=tolower(word[i]);
    }
}
