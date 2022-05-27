#include "SymbolTable.cpp"

using namespace std;
int main()
{
    SymbolTable* symbolTable=nullptr;
    string line;
	ifstream infile("dummy.txt");
	bool isFirstLine=true;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    if(isFirstLine){
	    	isFirstLine=false;
	    	int bucket;
	    	iss>>bucket;
	    	cout<<bucket<<endl;
            symbolTable=new SymbolTable(bucket);
        //do the things yoou need to do with bucket size;
		}else{
			string command;
		    iss>>command;
		    if(command.compare("I")==0){
		    	string name,type;
		    	iss>>name>>type;
                symbolTable->insertSymbol(name, type);
          //do the things you need to do with insert command
		    	cout<<"Insert "<<name<<' '<<type<<endl;
			}
			else if(command.compare("L")==0){
		    	string name;
		    	iss>>name;
                symbolTable->lookUpSymbol(name);
		    	cout<<"Lookup "<<name<<endl;
          //do the things you need to do with lookup command
			}
            else if(command.compare("L")==0){
		    	string name;
		    	iss>>name;
                symbolTable->lookUpSymbol(name);
		    	cout<<"Lookup "<<name<<endl;
          //do the things you need to do with lookup command
			}
		    
		}
	}
		
	return 0;

    
}