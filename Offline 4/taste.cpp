#include "1805077_SymbolTable.cpp"

int getArraySize(const string s){
	stringstream ss(s);
	string item;
	if(getline(ss, item, '[')){}
	while(getline(ss, item, ']'))
		return stoi(item);
    return 0;
}

int main(){
    SymbolTable t(30);
    t.enterScope();
    t.enterScope();
    t.exitScope();
    t.enterScope();
    t.enterScope();
    cout<<t.getCurrentScopeId()<<endl;

    cout<<getArraySize("arr[4]")<<endl;
}