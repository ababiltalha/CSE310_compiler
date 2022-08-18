#ifndef SYMBOL_INFO_H
#define SYMBOL_INFO_H
#include<bits/stdc++.h>
using namespace std;

class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo* next;
// Offline 4
    int stackOffset;
    string code;
    string address;
    bool isGlobalBool;

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

    int getStackOffset();
    void setStackOffset(int offset);
    string getCode();
    void setCode(string code); 
    string getAddress();
    void setAddress(string address);
    bool isGlobal();
    void setGlobal(bool global);
};

#endif