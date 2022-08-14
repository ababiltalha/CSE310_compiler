#ifndef FUNCTION_INFO_H
#define FUNCTION_INFO_H

#include "1805077_SymbolInfo.h"

class FunctionInfo : public SymbolInfo
{
private:
    string returnType;
    vector<string> parameterTypeList;
    bool defined;
public:
    FunctionInfo(string name, string returnType);
    void addParameter(string parameterType);
    vector<string> getParameterTypeList();
    string getReturnType();
    bool getDefined();
    void setDefined(bool defined);
};




#endif