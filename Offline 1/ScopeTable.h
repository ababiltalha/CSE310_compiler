#pragma once
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
public:
    ScopeTable(int bucket, ScopeTable* parent, int globalId);
    ~ScopeTable();
    unsigned long hashFunction(string name);
    bool insertSymbol(string name, string type);
    bool deleteSymbol(string name);
    SymbolInfo* lookupSymbol(string name);
    void print();
    string getId();
    int getInnerScopeCount();
    ScopeTable* getParentScope();
};


