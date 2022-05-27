#include<bits/stdc++.h>
#include "ScopeTable.cpp"
using namespace std;
using namespace std;

unsigned long hashFunction(string name){
    unsigned long hash=0;
    for (int i = 0; i < name.size(); i++)
        hash = name[i] + (hash << 6) + (hash << 16) - hash;
    return hash%7;
}

int main()
{
    // cout<<hashFunction("a")<<endl;
    ScopeTable sc(7, nullptr);
    cout<<sc.insertSymbol("a","a");
    cout<<sc.insertSymbol("foo","FUNCTION");
    cout<<sc.insertSymbol("a","b");
    cout<<sc.insertSymbol("5","NUMBER");
    cout<<sc.insertSymbol("i","VAR");
    sc.print();
    cout<<*sc.lookupSymbol("5");
    cout<<*sc.lookupSymbol("a");
    cout<<*sc.lookupSymbol("b");
    cout<<sc.deleteSymbol("a");
    sc.print();
    // Object o(123);
    // Object o= new Object(123);
}