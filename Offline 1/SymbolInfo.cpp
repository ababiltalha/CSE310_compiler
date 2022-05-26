#include "SymbolInfo.h"

SymbolInfo::SymbolInfo(string name, string type){
    this->name=name;
    this->type=type;
    this->next=nullptr;
}

SymbolInfo::~SymbolInfo(){
    //
}

string SymbolInfo::getName(){
    return this->name;
}

string SymbolInfo::getType(){
    return this->type;
}

SymbolInfo* SymbolInfo::getNext(){
    return this->next;
}

void SymbolInfo::setName(string name){
    this->name=name;

}

void SymbolInfo::setType(string type){
    this->type=type;

}

void SymbolInfo::setNext(SymbolInfo* next){
    this->next=next;
}

ostream &operator<<(ostream &output, SymbolInfo &symbol){
    output<<"< "<<symbol.name<<" : "<<symbol.type<<" >";
    return output;
}
