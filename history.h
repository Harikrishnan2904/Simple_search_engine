#include <iostream>

using namespace std;

#define HISTORY_TXT "history.txt"

#pragma once
struct d_node
{
    char file_name[101];
    d_node *next;
};

class linked_list
{
private:
    d_node *start;
    int n;
public:
    linked_list();
    void create(char* );
    void insert_beg(char* );
    void insert_end(char* );
    void delete_mid(char* );
    void delete_pos(int );
    void delete_all();
    void display();
    void update(char* ,char* );
    int get_count();
    char* operator[](int );
    void upload();
    void download();
}history;
linked_list::linked_list()
{
    n=0;
    start=nullptr;
}
void linked_list::create(char *fn)
{
    n=1;
    d_node *N=new d_node;
    strcpy(N->file_name,fn);
    N->next=nullptr;
    start=N;
}
void linked_list::insert_beg(char *fn)
{
    d_node *N=new d_node;
    strcpy(N->file_name,fn);
    N->next=start;
    start=N;
    n++;
}
void linked_list::insert_end(char *fn)
{
    d_node *N=new d_node;
    strcpy(N->file_name,fn);
    N->next=nullptr;
    if(start==nullptr)
    {
        start=N;
        n++;
    }
    else
    {
        d_node *ptr=start;
        while(ptr->next!=nullptr)
        {
            ptr=ptr->next;
        }
        ptr->next=N;
        n++;
    }
}
void linked_list::delete_mid(char *fn)
{
    d_node *ptr1=start;
    while(start!=nullptr&&strcmp(start->file_name,fn)==0)
    {
        start=start->next;
        delete ptr1;
        ptr1=start;
        n--;
    }
    d_node *ptr2;
    if(ptr1!=nullptr)
    {
        ptr2=ptr1->next;
        while(ptr2!=NULL)
        {
            if(strcmp(ptr2->file_name,fn)==0)
            {
                ptr1->next=ptr2->next;
                delete ptr2;
                ptr2=ptr1->next;
                n--;
            }
            else
            {
                ptr2=ptr2->next;
                ptr1=ptr1->next;
            }
        }
    }
}
void linked_list::delete_pos(int x)
{
    d_node *ptr=start;
    int i;
    if(x==0)
    {
        start=start->next;
        delete ptr;
    }
    else
    {
        for(i=0;i<x-1;i++)
        {
            ptr=ptr->next;
        }
        d_node *temp;
        temp=ptr->next;
        ptr->next=ptr->next->next;
        delete temp;
    }
    n--;
}
void linked_list::delete_all()
{
    d_node *ptr=start;
    while(ptr!=nullptr)
    {
        d_node *temp=ptr;
        ptr=ptr->next;
        delete temp;
    }
    start=nullptr;
    n=0;
}
void linked_list::display()
{
    d_node *ptr=start;
    int i=1;
    while(ptr!=NULL)
    {
        cout<<i<<")"<<ptr->file_name<<"\n";
        ptr=ptr->next;
        i++;
        if(i==11)
            break;
    }
}
void linked_list::update(char *x,char *y)
{
    d_node *ptr=start;
    if(strcmp(start->file_name,x)==0)
        strcpy(start->file_name,y);
    while(ptr->next!=nullptr)
    {
        if(strcmp(ptr->next->file_name,x)==0)
            strcpy(ptr->next->file_name,y);
        ptr=ptr->next;
    }
}
char* linked_list::operator[](int x)
{
    d_node *ptr=start;
    int i;
    for(i=0;i<x;i++)
    {
        ptr=ptr->next;
    }
    return ptr->file_name;
}
int linked_list::get_count()
{
    return n;
}
void linked_list::upload()
{
    ofstream file1(HISTORY_TXT,ios::trunc);
    d_node *ptr=start;
    while(ptr!=nullptr)
    {
        file1.write((char*)&ptr->file_name,sizeof(ptr->file_name));
        ptr=ptr->next;
    }
}
void linked_list::download()
{
    ifstream file1(HISTORY_TXT);
    char file_name[101];
    if(file1)
    {
        while(!file1.eof())
        {
            file1.read((char*)&file_name,sizeof(file_name));
            insert_end(file_name);
        }
    }
}
