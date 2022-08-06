#include <iostream>
#include "elf.h"

int main() {

    const int treeCount = 2;
    Tree** forest = nullptr;
    cout << "---Elf forest---" << endl;

    while (true)
    {
        string command;
        showMenu();
        cout << "Enter the command:";
        cin >> command;
        if(command == "forest")
        {
            system("cls");
            cout << "Populating forest number with elfes" << endl;
            cout << "-Be patient, there may be a lot of these elves there..." << endl;
            if(forest != nullptr)
            {
                delete[] forest;
                forest = nullptr;
            }

            forest = new Tree*[treeCount];

            for (int i = 0; i < treeCount; ++i)
            {
                system("cls");
                cout << "--- Populating tree number " << i+1 <<"---" << endl;
                cout << "-(Enter 'none' if the house is not inhabited)-" << endl;
                forest[i] = new Tree();
            }
            system("pause");
            system("cls");
        }
        else if(command == "show")
        {
            system("cls");
            if(forest != nullptr)
            {
                for (int i = 0; i < treeCount; ++i)
                {
                    cout << "--- Populating tree number " << i+1 <<"---"<< endl;
                    showOwners(forest[i]->getBranches(), forest[i]->getCountBranches());
                }
            }
            else
                cout << "Error! Forest empty, enter command 'forest' for create new forest!" << endl;
            system("pause");
            system("cls");
        }
        else if (command == "search")
        {
            system("cls");
            if(forest != nullptr)
            {
                string elfName;
                cout<<"Enter name for search:";
                cin>>elfName;

                cout << "--- Search in forest---"<< endl;
                for (int i = 0; i < treeCount; ++i)
                {
                    vector<vSearch> vResult;
                    searchNameOnTree(forest[i]->getBranches(), forest[i]->getCountBranches(), elfName, vResult);

                    if(!vResult.empty())
                        showResultSearch(vResult, forest[i], i);
                    else
                        cout<<"No one elf with the name '" << elfName << "' on this tree N:"<< i + 1 <<endl;
                }
                system("pause");
                system("cls");
            }
            else
                cout << "Error! Forest empty, enter command 'forest' for create new forest!" << endl;
        }
        else if(command == "exit")
        {break;}
        else
        {
            system("cls");
            cout << "Unknown command" << endl;
        }
    }

    system("cls");
    cout <<"---Bey, bey!---" << endl;
    system("pause");
    return 0;
}
//github
//git hub