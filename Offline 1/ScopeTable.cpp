#include "ScopeTable.h"

ScopeTable::ScopeTable(int bucket, ScopeTable* parent){
    this->bucket=bucket;
    this->parentScope=parent;
    this->hashTable=new SymbolInfo*[bucket];
    for (int i = 0; i < bucket; i++)
    {
        hashTable[i]=nullptr;
    }
    this->innerScope=0;
    if (parent!=nullptr){
        (this->parentScope->innerScope)++;
        id=this->parentScope->id+"."+
        to_string(this->parentScope->innerScope);
    }
    // global scope
    else id=to_string(1);
}

ScopeTable::~ScopeTable(){
    // write
}

unsigned long ScopeTable::hashFunction(string name){
    unsigned long hash=0;
    for (int i = 0; i < name.size(); i++)
        hash = name[i] + (hash << 6) + (hash << 16) - hash;
    return hash%bucket;
}

bool ScopeTable::insertSymbol(string name, string type){
    int hashVal=hashFunction(name);
    SymbolInfo* current=this->hashTable[hashVal];
    if(current==nullptr){
        this->hashTable[hashVal]=new SymbolInfo(name, type);
        return true;
    }
    while(current->getNext()!=nullptr){
        if(current->getName()==name) return false;
        current=current->getNext();
    }
    if(current->getName()==name)
        return false;
    current->setNext(new SymbolInfo(name, type));
    return true;
    
}
//     bool deleteSymbol(string name);
//     SymbolInfo* lookupSymbol(string name);
void ScopeTable::print(){
    //
    for (int i = 0; i < bucket; i++)
    {
        SymbolInfo* current=this->hashTable[i];
        cout<<endl<<i<<" --> ";
        while(current!=nullptr){
            cout<<*current;
            current=current->getNext();
        }
    }
    
}
//     string getId();
//     int getInnerScope();
