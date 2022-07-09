#include "SymbolTable.cpp"

int main(){
    SymbolTable table(30);
    table.insertSymbol("a","a");
    cout<<table.printAllScope();

    FunctionInfo* f = new FunctionInfo("foo", "void");
    f->addParameter("int");
    f->addParameter("int");
    table.insertSymbolInfo(f);
    cout<<table.printAllScope();
    SymbolInfo* temp= table.lookUpSymbol("foo");
    FunctionInfo* femp= (FunctionInfo*) temp;
    cout<<femp->getReturnType()<<endl;
    cout<<femp->getParameterTypeList().size()<<endl;
}