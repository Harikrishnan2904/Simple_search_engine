#include <string.h>
#include <ctype.h>

#include "structures.h"

using namespace std;

#pragma once
class trie
{
private:
    node *root;
public:
    trie();
    void add_key(char []);
    bool is_key_found(char []);
    node* get_key_node(char []);
    void display(node* );
}dictionary;
trie::trie()
{
    root=get_node();
}
void trie::add_key(char word[])
{
    node *t=root;
    lower_word(word);
    int i;
    int index;
    //cout<<word;
    for(i=0;i<strlen(word);i++)
    {
        index=word[i]-'a';
        if(t->ptr[index]==nullptr)
            t->ptr[index]=get_node();
        t=t->ptr[index];
    }
    t->is_end=true;
}
bool trie::is_key_found(char word[])
{
    node *t=root;
    lower_word(word);
    int i;
    int index;
    for(i=0;i<strlen(word);i++)
    {
        index=word[i]-'a';
        if(!t->ptr[index])
            break;
        t=t->ptr[index];
    }
    if(i==strlen(word)&&t->is_end)
        return true;
    else
    {
        //cout<<"(not found)";
        return false;
    }
}
node* trie::get_key_node(char word[])
{
    node *t=root;
    lower_word(word);
    int i;
    int index;
    for(i=0;i<strlen(word);i++)
    {
        index=word[i]-'a';
        t=t->ptr[index];
    }
    return t;
}
void trie::display(node *t=nullptr)
{
    if(t==nullptr)
    {
        t=root;
    }
    int i;
    for(i=0;i<ALPHABET_SIZE;i++)
    {
        if(t->ptr[i]!=nullptr)
        {
            char c;
            c='a'+i;
            cout<<c<<".";
            display(t->ptr[i]);
        }
    }
    if(t->is_end)
        cout<<endl;
}
