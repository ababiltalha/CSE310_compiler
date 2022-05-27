#include "SymbolTable.h"

SymbolTable::SymbolTable(int bucket){
    this->bucket=bucket;
    this->globalId=0;
    this->currentScope=new ScopeTable(bucket, nullptr, ++this->globalId);
    cout<<"SymbolTable with bucket size "+ to_string(bucket) +" created"<<endl;
}

SymbolTable::~SymbolTable(){
    while(this->currentScope!=nullptr){
        ScopeTable* parent=this->currentScope->getParentScope();
        delete this->currentScope;
        this->currentScope=parent;
    }
    cout<<"ScopeTable closed"<<endl;
}

void SymbolTable::enterScope(){
    if(this->currentScope==nullptr){
        this->currentScope=new ScopeTable(this->bucket, nullptr, ++this->globalId);
        cout<<"New ScopeTable with id "<<this->currentScope->getId()<<" created";
        return;
    }
    ScopeTable* newScope= new ScopeTable(this->bucket, this->currentScope, this->globalId);
    this->currentScope=newScope;
    cout<<"New ScopeTable with id "<<this->currentScope->getId()<<" created";
}

void SymbolTable::exitScope(){
    // if no scope exists
    if(this->currentScope==nullptr){
        cout<<"No scope exists"<<endl;
        return;
    }
    ScopeTable* parent=this->currentScope->getParentScope();
    cout<<"ScopeTable with id "<<this->currentScope->getId()<<" removed";
    delete this->currentScope;
    this->currentScope=parent;
}

void SymbolTable::insertSymbol(string name, string type){
    if(this->currentScope==nullptr){
        this->currentScope= new ScopeTable(this->bucket, nullptr, ++this->globalId);
    }
    this->currentScope->insertSymbol(name, type);
}

bool SymbolTable::removeSymbol(string name){
    // if(this->lookUpSymbol(name))
    if(this->currentScope==nullptr){
        cout<<"No current scope";
        return false;
    }
    return this->currentScope->deleteSymbol(name);
}

SymbolInfo* SymbolTable::lookUpSymbol(string name){
    if(this->currentScope==nullptr){
        this->currentScope=new ScopeTable(this->bucket, nullptr, this->globalId);
    }
    return this->currentScope->lookupSymbol(name);
}

void SymbolTable::printCurrentScope(){
    if(this->currentScope==nullptr){
        cout<<"Nothing to print"<<endl;
        return;
    }
    this->currentScope->print();
}

void SymbolTable::printAllScope(){
    ScopeTable* current=this->currentScope;
    while (current!=nullptr)
    {
        current->print();
        current=current->getParentScope();
    }
    
}
