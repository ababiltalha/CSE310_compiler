#include "SymbolTable.cpp"

using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin>>n;
    SymbolTable* symbolTable = new SymbolTable(n);

    string menuInput;
    while(!feof(stdin)) {
        cin>>menuInput;
        cout<<endl;
        if(menuInput == "I") {
            string name, type;
            cin>>name>>type;
            symbolTable->insertSymbol(name, type);
        } else if(menuInput == "L") {
            string name;
            cin >> name;
            symbolTable->lookUpSymbol(name);
        } else if(menuInput == "E") {
            symbolTable->exitScope();
        } else if(menuInput == "S") {
            symbolTable->enterScope();
        } else if(menuInput == "D") {
            string name;
            cin >> name;
            symbolTable->removeSymbol(name);
        } else if(menuInput == "P") {
            string command;
            cin>>command;
			if(command=="A") symbolTable->printAllScope();
			else if(command=="C") symbolTable->printCurrentScope();
        }
	}
}