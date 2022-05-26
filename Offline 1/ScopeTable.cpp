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
    id=

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

}
//     bool deleteSymbol(string name);
//     SymbolInfo* lookupSymbol(string name);
//     void print();
//     string getId();
//     int getInnerScope();
