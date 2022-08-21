#include "1805077_SymbolTable.cpp"

ifstream asmly;
ofstream optimizely;
int lineNumber=0;
vector<string> lineVector(1000);
vector<string> split(const string &s){
    vector<string> elements;
    string item = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ' || s[i] == ',' || s[i] == '\t') {
            if (item != "") {
                elements.push_back(item);
                item = "";
            }
        }
        else {
            item += s[i];
        }
    }

    if (item != "") {
        elements.push_back(item);
    }

    return elements;
}

int main(){
    string line, nextLine;
	vector<string> portions, nextPortions;
	lineVector.clear();
	asmly.open("code.asm");
	optimizely.open("optimized_code.asm");
	
	while (getline (asmly,line)) {
        cout<<lineNumber++<<endl;
		lineVector.push_back(line);
    }

    for (int i = 0; i < lineVector.size()-1; i++)
    {
        // cout<<0<<split(lineVector[i]).size()<<0<<endl;
        if((split(lineVector[i]).size()==0))
            continue;
        if((split(lineVector[i])[0].find(";") != string::npos))
            continue;
        cout<<"LINE  : " << __LINE__<<endl;
        line=lineVector[i];
        nextLine=lineVector[i+1];
        portions=split(line);
        nextPortions=split(nextLine);
        cout<<portions[0]<<endl;
		if(portions[0]=="PUSH"){
            if(nextPortions[0]=="POP"){ 
                if(portions[1]==nextPortions[1]){ // same register push and pop
                    lineVector[i]=";"+lineVector[i];
                    lineVector[i+1]=";"+lineVector[i+1];
                }
                else { // different memory push and pop
                    lineVector[i]=";"+lineVector[i];
                    lineVector[i+1]="MOV "+nextPortions[1]+", "+portions[1];
                }
            }
        } 

        if(portions[0]=="MOVE"){
            if(portions[1]==portions[2]){ // same register push and pop
                lineVector[i]=";"+lineVector[i];
            }
            if(nextPortions[0]=="MOVE"){ 
                if((portions[1]==nextPortions[2]) && (portions[2]==nextPortions[1])){ // same register push and pop
                    lineVector[i+1]=";"+lineVector[i+1];
                }
                if(portions[1]==nextPortions[1]){
                    lineVector[i]=";"+lineVector[i];
                }
            }
        }


    }


    for (int i = 0; i < lineVector.size(); i++)
    {
        optimizely<<lineVector[i]<<endl;
    }
    
	
	asmly.close();
	optimizely.close();

	return 0;
}