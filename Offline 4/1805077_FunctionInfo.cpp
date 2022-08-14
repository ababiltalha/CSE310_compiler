#ifndef FUNCTION_INFO_CPP
#define FUNCTION_INFO_CPP

#include "1805077_FunctionInfo.h"

FunctionInfo::FunctionInfo(string name, string returnType):SymbolInfo(name, "FUNCTION"){
    this->returnType=returnType;
    this->defined=false;
}

void FunctionInfo::addParameter(string parameterType){
    this->parameterTypeList.push_back(parameterType);
}

vector<string> FunctionInfo::getParameterTypeList(){
    return parameterTypeList;
}

string FunctionInfo::getReturnType(){
    return returnType;
}

bool FunctionInfo::getDefined(){
    return defined;
}

void FunctionInfo::setDefined(bool defined){
    this->defined=defined;
}

#endif 