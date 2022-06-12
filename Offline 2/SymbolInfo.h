#pragma once
#include<bits/stdc++.h>
using namespace std;

class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo* next;
public:
    SymbolInfo(string name, string type);
    ~SymbolInfo();
    string getName();
    string getType();
    SymbolInfo* getNext();
    void setName(string name);
    void setType(string type);
    void setNext(SymbolInfo* next);
    friend ostream &operator<<(ostream &output, SymbolInfo &symbol);
};

