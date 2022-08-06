//
// Created by Sg on 01.08.2022.
//
#include <vector>
#include <string>
#pragma once
using namespace std;
class Branch;
struct vSearch{
    const Branch* big{};
    int nBig = -1;
    int nTop = -1;
};
class Tree{

    int lvl = 0;
    Branch** branches = nullptr;
    int countBranch = 0;
public:
    explicit Tree(int inLvl = 0, int inCountBranch = 0, int inCountTopBranch = 0);
    int getCountBranches() const;
    Branch ** getBranches() const;
    int getNBranch(const Branch* myB) const;
    int getLvl() const;
    string getLvlStr() const;
};
class Branch:Tree
{
    string name;
public:
    using Tree::getCountBranches;
    using Tree::getBranches;
    using Tree::getLvl;
    using Tree::getLvlStr;
    string getName() const;
    explicit Branch(int inLvl, int inCountBranch, int nBranch);
};
void showOwners(Branch** myB, int count);
void searchNameOnTree(Branch** myB, int count, const string& name, vector<vSearch>& vBranch, Branch* big = nullptr);
void showResultSearch(vector<vSearch>& vBranch, const Tree* tree, int nTree);
int neighbourCount(const Branch* myB);
void showMenu();
