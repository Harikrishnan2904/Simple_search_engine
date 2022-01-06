#include <iostream>
#include <windows.h>

#include "structures.h"
#include "trie.h"
#include "files.h"

using namespace std;

int main()
{
    read_all_files();
    history.download();
    while(1)
    {
        system("cls");
        cout<<" -----------\n  Main Menu\n -----------\n";
        cout<<"\n1)Search for files\n2)Add new file\n3)History\n4)Quit\n\nOption:";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            cout<<" -----------\n   Search\n -----------\n";
            search_file();
        }
        else if(opt==2)
        {
            create_file();
        }
        else if(opt==3)
        {
            cout<<" -----------\n   History\n -----------\n";
            access_history();
        }
        else if(opt==4)
        {
            break;
        }
        else
        {
            cout<<"Invalid option!!!Enter any key to continue...";
            cin.get();cin.get();
        }
    }
    history.upload();
}
