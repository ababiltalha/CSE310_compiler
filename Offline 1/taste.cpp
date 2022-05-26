#include<bits/stdc++.h>
using namespace std;

unsigned long hashFunction(string name){
    unsigned long hash=0;
    for (int i = 0; i < name.size(); i++)
        hash = name[i] + (hash << 6) + (hash << 16) - hash;
    return hash%7;
}

int main()
{
    cout<<hashFunction("a")<<endl;
}