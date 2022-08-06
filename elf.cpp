//
// Created by Sg on 01.08.2022.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "elf.h"
using namespace std;

int Tree::getCountBranches() const {
    return countBranch;
}
int Tree::getLvl() const {
    return lvl;
}
int Tree::getNBranch(const Branch *myB) const {
    if(branches != nullptr)
    {
        for (int i = 0; i < countBranch; ++i)
            if(branches[i] == myB)
                return i;
    }
    return -1;
}
Tree::Tree(int inLvl, int inCountBranch, int inCountTopBranch) {

        if(inLvl == 0)
        {
            srand(time(nullptr));
            inCountBranch = 3 + rand() % 3;
        }

        countBranch = inCountBranch;
        branches = new Branch*[inCountBranch];
        lvl = inLvl;

        for (int i = 0; i < inCountBranch; ++i)
        {
            if(inLvl == 0)
            {
                srand(time(nullptr));
                inCountTopBranch = 2 + rand () % 2;
            }

            branches[i] = new Branch(lvl+1,inCountTopBranch, i+1);
        }
}
Branch::Branch(int inLvl, int inCountBranch, int nBranch)  : Tree(inLvl, inCountBranch)
{
    cout << "-Enter elf name (" << getLvlStr() << " branch " << nBranch << "):";
    cin >> name;
}
string Branch::getName() const {
    return name;
}
Branch** Tree::getBranches() const {
    return branches;
}
string Tree::getLvlStr() const {
    if(lvl == 0)
        return "Tree";
    else if (lvl == 1)
        return "Big";
    else if (lvl == 2)
        return "Top";
}
void showOwners(Branch** myB, int count)
{
    if(myB == nullptr)
        return;

    for (int i = 0; i < count; ++i)
    {
        if(myB[i]->getLvl() == 1)
            cout<<myB[i]->getLvlStr()<<" branch N:" << i + 1 <<" owner:"<<myB[i]->getName()<<endl;
        else
            cout<<"--"<<myB[i]->getLvlStr()<<" branch N:" << i + 1 <<" owner:"<<myB[i]->getName()<<endl;

        showOwners(myB[i]->getBranches(), myB[i]->getCountBranches());
    }

}
void searchNameOnTree(Branch **myB, int count, const string &name, vector<vSearch> &vBranch, Branch *big) {
    if(myB == nullptr)
        return;

    for (int i = 0; i < count; ++i)
    {
        if(myB[i]->getName() == name)
        {
            if(myB[i]->getLvl() == 1)
            {
                vSearch s{myB[i],i,-1};
                vBranch.push_back(s);
            }
            else if(myB[i]->getLvl() == 2)
            {
                vSearch s{big,-1,i};
                vBranch.push_back(s);
            }
        }
        searchNameOnTree(myB[i]->getBranches(), myB[i]->getCountBranches(), name, vBranch, myB[i]);
    }
}
int neighbourCount(const Branch* myB)
{
    int count = -1;

    if(myB->getName() != "None" && myB->getName() != "none")
        count++;

    for (int i = 0; i < myB->getCountBranches(); ++i)
        if(myB->getBranches()[i]->getName() != "None"
        && myB->getBranches()[i]->getName() != "none")
            count++;

    return count;
}
void showResultSearch(vector<vSearch>& vBranch, const Tree* tree, int nTree)
{
    for (auto & i : vBranch)
    {
        if(i.nBig == -1)
            i.nBig = tree->getNBranch(i.big); //не работает если вектор конст

        cout<<"Tree:"<<nTree + 1<<" Big branch:"<<i.nBig + 1;
        if(i.nTop != -1)
            cout << " Top branch:" <<i.nTop + 1;
        cout << " neighbour:" << neighbourCount(i.big) << endl;
    }
}
void showMenu()
{
    cout<<"Valid command format: 1 'forest' for new elf forest;"<<endl;
    cout<<"                      2 'show' for show elf forest;"<<endl;
    cout<<"                      3 'search' for search elf neighbour;"<<endl;
    cout<<"                      4 'exit' for exit."<<endl;
}