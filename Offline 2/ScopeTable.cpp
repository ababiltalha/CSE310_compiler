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
    for (int i = 0; i < this->bucket; i++)
    {
        SymbolInfo* temp;
        while(this->hashTable[i]!=nullptr) {
            temp=this->hashTable[i]->getNext();
            delete this->hashTable[i]; // array delete? no
            this->hashTable[i]=temp;
        }
    }
    delete[] this->hashTable;
    cout<<"\nDestroying the ScopeTable"<<endl;
}

uint32_t ScopeTable::hashFunction(string name){
    uint32_t hash=0;
    for (int i = 0; i < name.size(); i++)
        hash = name[i] + (hash << 6) + (hash << 16) - hash;
    return hash%bucket;
}

bool ScopeTable::insertSymbol(string name, string type){
    int position=0;
    int hashVal=hashFunction(name);
    SymbolInfo* current=this->hashTable[hashVal];
    if(current==nullptr){
        this->hashTable[hashVal]=new SymbolInfo(name, type);
        // cout<<"Inserted at ScopeTable id# "<<this->id<<" at position "<<hashVal<<", "<<position;
        return true;
    }
    while(current->getNext()!=nullptr){
        if(current->getName()==name) {
            // cout<<"< "<<name<<" : "<<type<<"> already exists in current ScopeTable";
            return false;
        }
        current=current->getNext();
        position++;
    }
    if(current->getName()==name) {
        // cout<<"< "<<name<<" : "<<type<<"> already exists in current ScopeTable";
        return false;
    }
    current->setNext(new SymbolInfo(name, type));
    // cout<<"Inserted at Scope "<<this->id<<" at position "<<hashVal<<", "<<++position;
    return true;
}

bool ScopeTable::deleteSymbol(string name){
    int position=0;
    int hashVal=hashFunction(name);
    SymbolInfo* current=this->hashTable[hashVal];
    if(current==nullptr) {
        cout<<"Not found\n\n"<<name<<" not found";
        return false;
    }
    SymbolInfo* prev=nullptr;
    // check current
    if(current->getName()==name){
        this->hashTable[hashVal]=current->getNext();
        delete current;
        cout<<"Found in ScopeTable# "<<this->id<<" at position "<<hashVal<<", "<<position<<"\n\nDeleted Entry "<<hashVal<<", "<<position<<" from current ScopeTable";
        return true;
    }
    while(current!=nullptr){
        if(current->getName()==name) {
            prev->setNext(current->getNext());
            delete current;
            cout<<"Found in ScopeTable# "<<this->id<<" at position "<<hashVal<<", "<<position<<"\n\nDeleted Entry "<<hashVal<<", "<<position<<" from current ScopeTable";
            return true;
        }
        prev=current;
        current=current->getNext();
        position++;
    }
    cout<<"Not found\n\n"<<name<<" not found";
    return false;
}

SymbolInfo* ScopeTable::lookupSymbol(string name){
    int position=0;
    int hashVal=hashFunction(name);
    SymbolInfo* current=this->hashTable[hashVal];
    while(current!=nullptr){
        if(current->getName()==name) {
            cout<<"Found in ScopeTable# "<<this->id<<" at position "<<hashVal<<", "<<position;
            return current;
        }
        current=current->getNext();
        position++;
    }
    // cout<<"Not found";
    return nullptr;
}

string ScopeTable::print(){
    string str="ScopeTable # "+id;
    // cout<<"\nScopeTable# "<<id<<endl;
    for (int i = 0; i < bucket; i++)
    {
        SymbolInfo* current=this->hashTable[i];
        if(current==nullptr) continue;
        str+="\n"+to_string(i)+" --> ";
        // cout<<endl<<i<<" --> ";
        while(current!=nullptr){
            // cout<<endl<<i<<" --> ";
            // cout<<*current;
            str+="< "+current->getName()+" : "+current->getType()+" >";
            current=current->getNext();
        }
    }
    str+="\n\n";
    return str;
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