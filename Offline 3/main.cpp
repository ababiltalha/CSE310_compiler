#include "SymbolTable.cpp"

vector<string> parameterNameList;
void extractParameterNameList(const string s, char delim) {
    bool flag;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        flag=true;
        stringstream ss2(item);
		string paramName;
		if(getline(ss2, paramName, ' ')) {}
        if(getline(ss2, paramName, ' ')) {
            for(string str : parameterNameList){
                if(paramName==str){
                    cout<<"error"<<endl;
                    flag=false;
                }
            }
			if(flag) parameterNameList.push_back(paramName);
		}
    }
}


int main(){
    extractParameterNameList("int a,int a,float c",',');
    for (int i = 0; i < parameterNameList.size(); i++)
        cout<<parameterNameList[i]<<endl;
}