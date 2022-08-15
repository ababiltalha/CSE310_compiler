#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include<bits/stdc++.h>
#include "1805077_ScopeTable.cpp"
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
    bool insertSymbol(string name, string type); // I
    bool removeSymbol(string name); // D
    SymbolInfo* lookUpSymbol(string name); // L
    void printCurrentScope(); // P C
    string printAllScope(); // P A

    bool insertSymbolInfo(SymbolInfo* s); 

    string getCurrentScopeId();

};

#endif 