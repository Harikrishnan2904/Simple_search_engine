#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>

#include "history.h"
#include "trie.h"

#define FILES_TXT "files.txt"
#define TEMP_TXT "temp.txt"

#pragma once
using namespace std;

bool is_word(char []);              //Checks if a word is qualified to be entered into dictionary
void read_file(char [],char []);    //Function to read files and insert data into dictionary
void remove_file(char [],char []);  //Function to read files and delete dat from dictionary
void read_all_files();              //Starter function: Reads all existing files(structure txt_file) and initialises the dictionary
bool is_file_found(char* );         //checks if file name already exists
void open_file(txt_file );          //Opens file given its structure

void create_file()
{
    txt_file temp;
    cout<<"Enter file name:";
    char n[1000];
    cin.ignore();
    cin.get(n,1000);cin.get();
    while(1)
    {
        if(strlen(n)>100)
        {
            cout<<"Name must have less than 100 characters...re-enter:";
            cin.get(n,1000);cin.get();
        }
        else if(is_file_found(n))
        {
            cout<<"Name already exists...re-enter:";
            cin.get(n,1000);cin.get();
        }
        else
        {
            break;
        }
    }
    strcpy(temp.name,n);
    cout<<"Enter content:\n";
    char c[3000];
    cin.get(c,3000);cin.get();
    while(strlen(c)>2000)
    {
        cout<<"Content must contain less than 2000 characters...re-enter:";
        cin.get(c,3000);cin.get();
    }
    strcpy(temp.content,c);
    read_file(n,c);
    cout<<"1";
    ofstream file1(FILES_TXT,ios::app);
    file1.write((char*)&temp,sizeof(temp));
    cout<<"File added!!!\nEnter any key to continue...";
    cin.get();
}

void search_file()
{
    cout<<"Enter search query:";
    char query[1000];
    cin.ignore();
    cin.get(query,1000);cin.get();
    char *word;
    file_occurance *temp,*temp_crawl;
    temp=nullptr;
    word=strtok(query,delimiters);
    while(word!=nullptr)
    {
        if(dictionary.is_key_found(word))
        {
            node *t=dictionary.get_key_node(word);
            if(t->data!=nullptr)
            {
                temp=new file_occurance;
                strcpy(temp->files_name,t->data->files_name);
                temp->name_occurance=0;
                temp->content_occurance=0;
                temp->ptr=nullptr;
                //cout<<temp->files_name<<endl<<t->data->files_name<<endl;
                break;
            }
        }
        word=strtok(nullptr,delimiters);
    }
    while(word!=nullptr)
    {
        node *t;
        file_occurance *crawl;
        if(dictionary.is_key_found(word))
        {
            t=dictionary.get_key_node(word);
            crawl=t->data;
            while(crawl!=nullptr)
            {
                temp_crawl=temp;
                while(temp_crawl!=nullptr)
                {
                    if(strcmp(temp_crawl->files_name,crawl->files_name)==0)
                    {
                        temp_crawl->name_occurance+=crawl->name_occurance;
                        temp_crawl->content_occurance+=crawl->content_occurance;
                        break;
                    }
                    else if(temp_crawl->ptr==nullptr)
                    {
                        temp_crawl->ptr=new file_occurance;
                        strcpy(temp_crawl->ptr->files_name,crawl->files_name);
                        temp_crawl->ptr->name_occurance=crawl->name_occurance;
                        temp_crawl->ptr->content_occurance=crawl->content_occurance;
                        temp_crawl->ptr->ptr=nullptr;
                    }
                    temp_crawl=temp_crawl->ptr;
                }
                crawl=crawl->ptr;
            }
        }
        word=strtok(nullptr,delimiters);
    }
    file_occurance priorty[5];
    int i;
    for(i=0;i<5;i++)
    {
        strcpy(priorty[i].files_name,"_empty_");
        priorty[i].name_occurance=0;
        priorty[i].content_occurance=0;
    }
    while(temp!=nullptr)
    {
        for(i=0;i<5;i++)
        {
            //cout<<temp->files_name<<"----"<<priorty[i].files_name<<endl;
            if(temp->name_occurance>priorty[i].name_occurance)
            {
                char temp_name[101];
                int temp_name_occurance;
                int temp_content_occurance;
                strcpy(temp_name,temp->files_name);
                temp_name_occurance=temp->name_occurance;
                temp_content_occurance=temp->content_occurance;
                strcpy(temp->files_name,priorty[i].files_name);
                temp->name_occurance=priorty[i].name_occurance;
                temp->content_occurance=priorty[i].content_occurance;
                strcpy(priorty[i].files_name,temp_name);
                priorty[i].name_occurance=temp_name_occurance;
                priorty[i].content_occurance=temp_content_occurance;
            }
            else if(temp->name_occurance==priorty[i].name_occurance&&temp->content_occurance>priorty[i].content_occurance)
            {
                char temp_name[51];
                int temp_name_occurance;
                int temp_content_occurance;
                strcpy(temp_name,temp->files_name);
                temp_name_occurance=temp->name_occurance;
                temp_content_occurance=temp->content_occurance;
                strcpy(temp->files_name,priorty[i].files_name);
                temp->name_occurance=priorty[i].name_occurance;
                temp->content_occurance=priorty[i].content_occurance;
                strcpy(priorty[i].files_name,temp_name);
                priorty[i].name_occurance=temp_name_occurance;
                priorty[i].content_occurance=temp_content_occurance;
            }
        }
        temp=temp->ptr;
    }
    if(priorty[0].name_occurance==0&&priorty[0].content_occurance==0)
    {
        cout<<"No files match your search query...\nEnter any key to continue...";
        cin.get();cin.get();
    }
    else
    {
        for(i=0;i<5;i++)
        {
            if(priorty[i].name_occurance==0&&priorty[i].content_occurance==0)
                break;
            cout<<i+1<<")"<<priorty[i].files_name<<endl;
        }
        cout<<"0)Back\nOption:";
        int opt;
        cin>>opt;
        while(opt<0||opt>5||(opt!=0&&strcmp(priorty[opt-1].files_name,"_empty_")==0))
        {
            cout<<"Invalid option!!!re-enter:";
            cin>>opt;
        }
        if(opt)
        {
            opt--;
            ifstream file1(FILES_TXT);
            txt_file f;
            //cout<<priorty[opt].files_name;
            while(!file1.eof())
            {
                file1.read((char*)&f,sizeof(f));
                if(strcmp(f.name,priorty[opt].files_name)==0)
                {
                    open_file(f);
                    break;
                }
            }
        }
    }
}
void open_file(txt_file temp)
{
    history.insert_beg(temp.name);
    while(true)
    {
        system("cls");
        cin.ignore();
        cout<<temp.name<<"\n----\n1)Display file\n2)Edit file\n3)Delete file\n4)back\nOption:";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            int i;
            cout<<"\n  "<<temp.name<<"\n  ";
            for(i=0;i<strlen(temp.name);i++)
            {
                cout<<"-";
            }
            cout<<endl<<temp.content<<"\n\nEnter any key to continue...";
            cin.get();cin.get();
        }
        else if(opt==2)
        {
            cout<<"----------\n1)Change title\n2)Change content\nOption:";
            int opt1;
            cin>>opt1;
            if(opt1==1)
            {
                char word[101];
                strcpy(word,temp.name);
                cout<<"Enter New Title:";
                cin.ignore();
                cin.get(temp.name,101);cin.get();
                while(is_file_found(temp.name))
                {
                    cout<<"Name already exists...re-enter:";
                    cin.get(temp.name,101);cin.get();
                }
                remove_file(word,temp.content);
                read_file(temp.name,temp.content);
                txt_file t;
                fstream file1(FILES_TXT);
                file1.read((char*)&t,sizeof(txt_file));
                while(!file1.eof())
                {
                    cout<<t.name;
                    if(strcmp(t.name,word)==0)
                    {
                        int length;
                        length=file1.tellp();
                        cout<<"1";
                        file1.seekp(length-1*sizeof(t));
                        cout<<"2";
                        file1.write((char*)&temp,sizeof(txt_file));
                        cout<<"3";
                        break;
                    }
                    file1.read((char*)&t,sizeof(txt_file));
                }
                cout<<"4";
                file1.close();
                history.update(word,temp.name);
                cout<<"Title updated!!!\nEnter to continue...";
                cin.get();cin.get();
            }
            else if(opt1==2)
            {
                //system("cls");
                char word[2001];
                strcpy(word,temp.content);
                cout<<"Enter New Content:";
                cin.ignore();
                cin.get(temp.content,2001);cin.get();
                //cout<<"1";
                remove_file(temp.name,word);
                //cout<<"2";
                read_file(temp.name,temp.content);
                //cout<<"3";
                txt_file t;
                fstream file1(FILES_TXT);
                file1.read((char*)&t,sizeof(txt_file));
                while(!file1.eof())
                {
                    if(strcmp(t.name,temp.name)==0)
                    {
                        file1.seekp(-1*sizeof(txt_file),ios::cur);
                        file1.write((char*)&temp,sizeof(txt_file));
                    }
                    file1.read((char*)&t,sizeof(txt_file));
                }
                file1.close();
                cout<<"Content updated!!!\nEnter to continue...";
                cin.get();cin.get();
            }
            else
            {
                cout<<"Invalid option!!!\nEnter any key to continue...";
                cin.get();
            }
        }
        else if(opt==3)
        {
            remove_file(temp.name,temp.content);
            history.delete_mid(temp.name);
            txt_file t;
            ifstream file1(FILES_TXT);
            ofstream file2(TEMP_TXT);
            file1.read((char*)&t,sizeof(txt_file));
            while(!file1.eof())
            {
                if(strcmp(t.name,temp.name)!=0)
                {
                    cout<<t.name<<"==="<<t.content<<endl;
                    file2.write((char*)&t,sizeof(txt_file));
                }
                file1.read((char*)&t,sizeof(txt_file));
            }
            file1.close();
            file2.close();
            remove(FILES_TXT);
            rename(TEMP_TXT,FILES_TXT);
            cout<<"File deleted!!!\nEnter to continue...";
            cin.get();cin.get();
            break;
        }
        else if(opt==4)
        {
            break;
        }
        else
        {
            cout<<"Invalid option!!!\nEnter any key to continue...";
            cin.get();
        }
    }
}
void access_history()
{
    history.display();
    cout<<"\n-1)Clear search history\n0)back\nOption:";
    int opt;
    cin>>opt;
    while(opt<-1||opt>10||opt>history.get_count())
    {
        cout<<"Invalid option...re-enter:";
        cin>>opt;
    }
    if(opt)
    {
        if(opt==-1)
        {
            history.delete_all();
            cout<<"Search history cleared!!!\nPress any key to continue...";
            cin.get();cin.get();
        }
        else
        {
            while(1)
            {
                cout<<"File name:"<<history[opt-1]<<endl;
                cout<<"1)Access file\n2)Delete from history\n3)Delete all history of this file\n4)back\nOption:";
                int opt1;
                cin>>opt1;
                if(opt1==1)
                {
                    ifstream file1(FILES_TXT);
                    txt_file temp;
                    while(!file1.eof())
                    {
                        file1.read((char*)&temp,sizeof(temp));
                        if(strcmp(temp.name,history[opt-1])==0)
                        {
                            open_file(temp);
                            break;
                        }
                    }
                    break;
                }
                else if(opt1==2)
                {
                    history.delete_pos(opt-1);
                    cout<<"Deleted!!!\nPress any key to continue...";
                    cin.get();cin.get();
                    break;
                }
                else if(opt1==3)
                {
                    history.delete_mid(history[opt-1]);
                    cout<<"Deleted!!!\nPress any key to continue...";
                    cin.get();cin.get();
                    break;
                }
                else if(opt1==4)
                {
                    break;
                }
                else
                {
                    cout<<"Invalid option!!!\nPress any key to continue...";
                    cin.get();cin.get();
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void read_file(char name[101],char content[2001])
{
    char *word;
    //cout<<name<<endl<<content<<endl;
    char name_t[101];
    strcpy(name_t,name);
    word=strtok(name_t,delimiters);
    while(word!=nullptr)
    {
        if(is_word(word))
        {
            //cout<<word;
            if(!dictionary.is_key_found(word))
                dictionary.add_key(word);
            node *t;
            t=dictionary.get_key_node(word);
            file_occurance *crawl;
            crawl=t->data;
            if(t->data==nullptr)
            {
                t->data=new file_occurance;
                strcpy(t->data->files_name,name);
                t->data->name_occurance=1;
                t->data->content_occurance=0;
                t->data->ptr=nullptr;
                //cout<<name;
            }
            while(crawl!=nullptr)
            {
                if(strcmp(crawl->files_name,name)==0)
                {
                    crawl->name_occurance++;
                    break;
                }
                else if(crawl->ptr==nullptr)
                {
                    crawl->ptr=new file_occurance;
                    strcpy(crawl->ptr->files_name,name);
                    crawl->ptr->name_occurance=1;
                    crawl->ptr->content_occurance=0;
                    crawl->ptr->ptr=nullptr;
                    break;
                }
                crawl=crawl->ptr;
            }
        }
        word=strtok(nullptr,delimiters);
    }
    word=strtok(content,delimiters);
    while(word!=nullptr)
    {
        if(is_word(word))
        {
            //cout<<word;
            if(!dictionary.is_key_found(word))
                dictionary.add_key(word);
            node *t;
            t=dictionary.get_key_node(word);
            file_occurance *crawl;
            crawl=t->data;
            if(t->data==nullptr)
            {
                t->data=new file_occurance;
                strcpy(t->data->files_name,name);
                t->data->name_occurance=0;
                t->data->content_occurance=1;
                t->data->ptr=nullptr;
            }
            while(crawl!=nullptr)
            {
                if(strcmp(crawl->files_name,name)==0)
                {
                    crawl->content_occurance++;
                    break;
                }
                else if(crawl->ptr==nullptr)
                {
                    crawl->ptr=new file_occurance;
                    strcpy(crawl->ptr->files_name,name);
                    crawl->ptr->name_occurance=0;
                    crawl->ptr->content_occurance=1;
                    crawl->ptr->ptr=nullptr;
                    break;
                }
                crawl=crawl->ptr;
            }
        }
        word=strtok(nullptr,delimiters);
    }
}
void read_all_files()
{
    ifstream file1(FILES_TXT);
    if(file1)
    {
        txt_file temp;
        while(!file1.eof())
        {
            file1.read((char*)&temp,sizeof(temp));
//            cout<<endl<<temp.name<<endl<<temp.content<<endl;
            read_file(temp.name,temp.content);
 /*           cout<<temp.name<<"\n"<<temp.content<<"\n";
            char *word;
            word=strtok(temp.content,delimiters);
            while(word!=nullptr)
            {
                cout<<word<<endl;
                if(strlen(word)>=3)
                {
                    if(!dictionary.is_key_found(word))
                        dictionary.add_key(word);
                    node *t;
                    t=dictionary.get_key_node(word);
                    file_occurance *crawl;
                    crawl=t->data;
                    if(t->data==nullptr)
                    {
                        t->data=new file_occurance;
                        strcpy(t->data->files_name,temp.name);
                        t->data->occurance=1;
                        t->data->ptr=nullptr;
                    }
                    while(crawl!=nullptr)
                    {
                        if(strcmp(crawl->files_name,temp.name)==0)
                        {
                            crawl->data->occurance++;
                            break;
                        }
                        else if(crawl->ptr==nullptr)
                        {
                            crawl->ptr=new file_occurance;
                            strcpy(crawl->ptr->files_name,temp.name);
                            crawl->ptr->occurance=1;
                            crawl->ptr->ptr=nullptr;
                            break;
                        }
                        crawl=crawl->ptr;
                    }
                }
                word=strtok(nullptr,delimiters);
            }
*/
        }
    }
}
void remove_file(char name[101],char content[2001])
{
    char *word;
    //cout<<name<<endl<<content<<endl;
    char name_t[101];
    strcpy(name_t,name);
    word=strtok(name_t,delimiters);
    while(word!=nullptr)
    {
        if(is_word(word))
        {
            //cout<<word;
            //if(!dictionary.is_key_found(word))
            //    dictionary.add_key(word);
            node *t;
            t=dictionary.get_key_node(word);
            file_occurance *crawl;
            crawl=t->data;
            if(t->data!=nullptr&&strcmp(t->data->files_name,name)==0)
            {
                t->data=t->data->ptr;
            }
            else if(t->data!=nullptr)
            {
                while(crawl->ptr!=nullptr)
                {
                    if(strcmp(crawl->ptr->files_name,name)==0)
                    {
                        file_occurance *temp;
                        temp=crawl->ptr;
                        crawl->ptr=crawl->ptr->ptr;
                        delete temp;
                        break;
                    }
                    crawl=crawl->ptr;
                }
            }
        }
        word=strtok(nullptr,delimiters);
    }
    word=strtok(content,delimiters);
    while(word!=nullptr)
    {
        if(is_word(word))
        {
            cout<<word;
            //if(!dictionary.is_key_found(word))
            //    dictionary.add_key(word);
            node *t;
            t=dictionary.get_key_node(word);
            file_occurance *crawl;
            crawl=t->data;
            if(t->data!=nullptr&&strcmp(t->data->files_name,name)==0)
            {
                t->data=t->data->ptr;
            }
            else if(t->data!=nullptr)
            {
                while(crawl->ptr!=nullptr)
                {
                    if(strcmp(crawl->ptr->files_name,name)==0)
                    {
                        file_occurance *temp;
                        temp=crawl->ptr;
                        crawl->ptr=crawl->ptr->ptr;
                        delete temp;
                        break;
                    }
                    crawl=crawl->ptr;
                }
            }
        }
        word=strtok(nullptr,delimiters);
    }
}
bool is_file_found(char *name)
{
    txt_file temp;
    ifstream file1(FILES_TXT);
    if(file1)
    {
        while(!file1.eof())
        {
            file1.read((char*)&temp,sizeof(temp));
            if(strcmp(temp.name,name)==0)
                return true;
        }
    }
    return false;
}
bool is_word(char word[])
{
    int i;
    for(i=0;i<strlen(word);i++)
    {
        if(word[i]<'A'||word[i]>'z'||(word[i]<'a'&&word[i]>'Z'))
            break;
    }
    if(i==strlen(word)&&strlen(word)>=4)
        return true;
    else
        return false;
}



