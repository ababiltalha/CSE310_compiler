#include "ScopeTable.h"

ScopeTable::ScopeTable(int bucket, ScopeTable* parent, int globalId){
    this->bucket=bucket;
    this->parentScope=parent;
    this->hashTable=new SymbolInfo*[bucket];
    for (int i = 0; i < bucket; i++)
    {
        hashTable[i]=nullptr;
    }
    this->innerScopeCount=0;
    if (this->parentScope!=nullptr){
        (this->parentScope->innerScopeCount)++;
        this->id=this->parentScope->id+"."+
        to_string(this->parentScope->innerScopeCount);
    }
    // global scope
    else id=to_string(globalId);
}

ScopeTable::~ScopeTable(){
    // write
}

unsigned long ScopeTable::hashFunction(string name){
    unsigned long hash=0;
    for (int i = 0; i < name.size(); i++)
        hash = (int)name[i] + (hash << 6) + (hash << 16) - hash;
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

bool ScopeTable::deleteSymbol(string name){
    int hashVal=hashFunction(name);
    SymbolInfo* current=this->hashTable[hashVal];
    if(current==nullptr) return false;
    SymbolInfo* prev=nullptr;
    // check current
    if(current->getName()==name){
        this->hashTable[hashVal]=current->getNext();
        delete current;
        return true;
    }
    while(current!=nullptr){
        if(current->getName()==name) {
            prev->setNext(current->getNext());
            delete current;
            return true;
        }
        prev=current;
        current=current->getNext();
    }
    return false;
}

SymbolInfo* ScopeTable::lookupSymbol(string name){
    int hashVal=hashFunction(name);
    SymbolInfo* current=this->hashTable[hashVal];
    while(current!=nullptr){
        if(current->getName()==name) {
            return current;
        }
        current=current->getNext();
    }
    return nullptr;
}
void ScopeTable::print(){
    cout<<"ScopeTable# "<<id<<endl;
    for (int i = 0; i < bucket; i++)
    {
        SymbolInfo* current=this->hashTable[i];
        cout<<endl<<i<<" --> ";
        while(current!=nullptr){
            cout<<*current;
            current=current->getNext();
        }
    }
    cout<<endl;  
}
string ScopeTable::getId(){
    return this->id;
}
int ScopeTable::getInnerScopeCount(){
    return this->innerScopeCount;
}
ScopeTable* ScopeTable::getParentScope(){
    return this->parentScope;
}