#pragma once
#include<bits/stdc++.h>
#include "ScopeTable.cpp"
using namespace std;

class SymbolTable
{
private:
    int bucket;
    ScopeTable* currentScope;
    int globalId;

public:
    SymbolTable(int bucket);
    ~SymbolTable();
    void enterScope(); // S
    void exitScope(); // E
    void insertSymbol(string name, string type); // I
    bool removeSymbol(string name); // D
    SymbolInfo* lookUpSymbol(string name); // L
    void printCurrentScope(); // P C
    void printAllScope(); // P A


};

