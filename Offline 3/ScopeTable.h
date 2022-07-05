#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H
#include<bits/stdc++.h>
#include "SymbolInfo.cpp"
using namespace std;

class ScopeTable
{
private:
    // static int globalId;
    SymbolInfo** hashTable;
    int bucket;
    string id;
    int innerScopeCount; //child num
    ScopeTable* parentScope;
    uint32_t hashFunction(string name);
public:
    ScopeTable(int bucket, ScopeTable* parent, int globalId);
    ~ScopeTable();
    bool insertSymbol(string name, string type);
    bool deleteSymbol(string name);
    SymbolInfo* lookupSymbol(string name);
    string print();
    string getId();
    int getInnerScopeCount();
    ScopeTable* getParentScope();
};

#endif
