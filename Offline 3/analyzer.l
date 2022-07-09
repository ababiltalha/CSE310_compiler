%option noyywrap

%x UNKNOWN_WORD
%x STRING_STATE
%x MULTILINE_CMNT_STATE
%x SINGLELINE_CMNT_STATE



%{
#include "SymbolInfo.h"
#include "y.tab.h"

// #define YYSTYPE SymbolInfo*
extern YYSTYPE yylval;

int lineCount=1;
int wordCount=0;
int errorCount=0;
int logStringStart;

string tokenString="";
string logString="";
string newString="";


extern FILE *logout;
extern FILE *errorout;
FILE *tokenout;

void yyerror(char *);

void increaseWordCount(){
	wordCount++;
}

void increaseErrorCount(){
	errorCount++;
}

char* toUpper(char *s){
    int i;
    char* u= new char;
    for (i = 0; s[i]!='\0'; i++) {
      if(s[i] >= 'a' && s[i] <= 'z') {
         u[i] = s[i]-32;
      } else u[i]=s[i];
   }
   return u;
}

char toSpecial(char* s){
	char sp;
	if(s[0]=='\\'){
		if(s[1]=='n') sp='\n';
		if(s[1]=='t') sp='\t';
		if(s[1]=='\\') sp='\\';
		if(s[1]=='\'') sp='\'';
		if(s[1]=='a') sp='\a';
		if(s[1]=='f') sp='\f';
		if(s[1]=='r') sp='\r';
		if(s[1]=='b') sp='\b';
		if(s[1]=='v') sp='\v';
		if(s[1]=='0') sp='\0';
		if(s[1]=='\"') sp='\"';
		return sp;
	}
	if(s[1]!= '\\') sp=s[1];
	else {
		if(s[2]=='n') sp='\n';
		if(s[2]=='t') sp='\t';
		if(s[2]=='\\') sp='\\';
		if(s[2]=='\'') sp='\'';
		if(s[2]=='a') sp='\a';
		if(s[2]=='f') sp='\f';
		if(s[2]=='r') sp='\r';
		if(s[2]=='b') sp='\b';
		if(s[2]=='v') sp='\v';
		if(s[2]=='0') sp='\0';
		if(s[1]=='\"') sp='\"';
	}
	return sp;
}



void detectKeyword(char *str){
    char* s= toUpper(str);
    // fprintf(tokenout,"<%s> ",s);
	// fprintf(logout,"Line no %d: Token <%s> Lexeme %s found\n\n",lineCount,s,str);
	// increaseWordCount();
	
}

void detectUnknownWord(char *str){
	increaseErrorCount();
	// printf("Unknown word %s\n", str);
	// fprintf(logout,"Error at line no %d: Unrecognized word %s\n\n",lineCount,str);
}

void endOfFile(){
	string allScope;
	// allScope=table->printAllScope();
	// fprintf(logout,"%s",allScope.c_str());
	// fprintf(logout,"Total lines: %d\n",lineCount);
	// fprintf(logout,"Total errors: %d\n",errorCount);
}

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE (\r)?[\n]
KEYWORD if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue
CONST_INT {DIGIT}+
CONST_FLOAT {DIGIT}*({DIGIT}\.?|\.{DIGIT}){DIGIT}*([Ee][-+]?{DIGIT}+)?
CHAR [ -~]
SPECIAL_CHAR \\[\\nfratbv0\'\"]
CONST_CHAR \'({CHAR}|{SPECIAL_CHAR})\'
LCURL [{]
RCURL [}]
LTHIRD ("[")
RTHIRD ("]")
ID ({LETTER}|_)({LETTER}|_|{DIGIT})*
TOO_MANY_DEC {CONST_INT}(\.{CONST_INT})(\.{CONST_INT})+
ILL_FORM_NUM {CONST_FLOAT}+\.{CONST_INT}
INVALID_NUM_ID {CONST_INT}{ID}
MULTI_CHAR \'{CHAR}{2,}\'
UNFINISHED_CHAR \'({CHAR}?)|(\'{SPECIAL_CHAR})
EMPTY_CHAR \'\'


%%

{WHITESPACE} {}

{NEWLINE} {lineCount++;}

"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"break" {return BREAK;}
"int" {return INT;}
"float" {return FLOAT;}
"double" {return DOUBLE;}
"char" {return CHAR;}
"return" {return RETURN;}
"void" {return VOID;}
"switch" {return SWITCH;}
"case" {return CASE;}
"default" {return DEFAULT;}
"continue" {return CONTINUE;}
"printf"	{return PRINTLN;}

{CONST_INT} {
	// fprintf(tokenout,"<CONST_INT, %s> ", yytext);
	// fprintf(logout,"Line no %d: Token <CONST_INT> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "CONST_INT");
	yylval.symbol = s;
	return CONST_INT;
}

{CONST_FLOAT} {
	// fprintf(tokenout,"<CONST_FLOAT, %s> ", yytext);
	// fprintf(logout,"Line no %d: Token <CONST_FLOAT> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "CONST_FLOAT");
	yylval.symbol = s;
	return CONST_FLOAT;
}

[\'][\'] {
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Empty character constant error \'\'\n\n",lineCount);
}

{UNFINISHED_CHAR}|[\'][\\][\'] {
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Unterminated character %s\n\n",lineCount,yytext);
}

{CONST_CHAR} {
	char ch= toSpecial(yytext);
	// fprintf(tokenout,"<CONST_CHAR, %c> ", ch);
	// fprintf(logout,"Line no %d: Token <CONST_CHAR> Lexeme %s found --> <CONST_CHAR, %c> \n\n",lineCount,yytext,ch);
	
}

{MULTI_CHAR} {
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Multi character constant error %s\n\n",lineCount,yytext);
}

"+"|"-" {
	// fprintf(tokenout,"<ADDOP,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <ADDOP> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "ADDOP");
	yylval.symbol = s;
	return ADDOP;
}

"*"|"/"|"%" {
	// fprintf(tokenout,"<MULOP,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <MULOP> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "MULOP");
	yylval.symbol = s;
	return MULOP;
}

"++" 	{return INCOP;}
"--" 	{return DECOP;}

"<"|"<="|">"|">="|"=="|"!=" {
	// fprintf(tokenout,"<RELOP,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <RELOP> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "RELOP");
	yylval.symbol = s;
	return RELOP;
}

"=" {
	// fprintf(tokenout,"<ASSIGNOP,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <ASSIGNOP> Lexeme %s found\n\n",lineCount,yytext);
	return ASSIGNOP;
}

"&&"|"||" {
	// fprintf(tokenout,"<LOGICOP,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <LOGICOP> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "LOGICOP");
	yylval.symbol = s;
	return LOGICOP;
}

"!" {
	// fprintf(tokenout,"<NOT,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <NOT> Lexeme %s found\n\n",lineCount,yytext);
	return NOT;
}

";" 	{ return SEMICOLON;}
"," 	{return COMMA;}
"(" 	{return LPAREN;cout<<"a"<<endl;}
")" 	{return RPAREN;}
{LCURL} {return LCURL;}
{RCURL} {return RCURL;}
{LTHIRD} {return LTHIRD;}
{RTHIRD} {return RTHIRD;}

"\"" {
	BEGIN STRING_STATE;
	logStringStart=lineCount;
	newString=yytext;
	tokenString.append(newString);
	logString.append(newString);
}

<STRING_STATE>"\"" {
	newString=yytext;
	tokenString.append(newString);
	logString.append(newString);
	// fprintf(tokenout,"<STRING,%s> ",tokenString.c_str());
	// fprintf(logout,"Line no %d: Token <STRING> Lexeme %s found --> <STRING,%s> \n\n",logStringStart,logString.c_str(),tokenString.c_str());
	BEGIN INITIAL;
	tokenString="";
	logString="";
}

<STRING_STATE>[\\][\\nfratbv0\'\"] {
	newString=yytext;
	logString.append(newString);
	char ch= toSpecial(yytext);
	// printf("%c", ch);
	newString= ch;
	tokenString.append(newString);	
}

<STRING_STATE>[\\]{NEWLINE} {
	lineCount++;
	newString=yytext;
	logString.append(newString);
}

<STRING_STATE>[\\][^{NEWLINE}] {
	increaseErrorCount();
	newString=yytext;
	logString.append(newString);
	// fprintf(logout,"Error at line no %d: Unterminated String %s\n\n",logStringStart,logString.c_str());
	BEGIN INITIAL;
	tokenString="";
	logString="";
}

<STRING_STATE>{NEWLINE} {
	lineCount++;
	increaseErrorCount();
	// logString.append(newString);
	// fprintf(logout,"Error at line no %d: Unterminated String %s\n\n",logStringStart,logString.c_str());
	BEGIN INITIAL;
	tokenString="";
	logString="";
}

<STRING_STATE>. {
	newString=yytext;
	tokenString.append(newString);
	logString.append(newString);
}

<STRING_STATE><<EOF>> {
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Unterminated String %s\n\n",logStringStart,logString.c_str());
	BEGIN INITIAL;
	tokenString="";
	logString="";
	endOfFile();
	return 0;
}

\/\/ {
	BEGIN SINGLELINE_CMNT_STATE;
	logStringStart=lineCount;
	newString=yytext;
	logString.append(newString);
}

<SINGLELINE_CMNT_STATE>{NEWLINE} {
	lineCount++;
	// fprintf(logout,"Line no %d: Token <COMMENT> Lexeme %s found\n\n",logStringStart,logString.c_str());
	BEGIN INITIAL;
	logString="";
}

<SINGLELINE_CMNT_STATE>\\{NEWLINE} {
	lineCount++;
	newString=yytext;
	logString.append(newString);
}

<SINGLELINE_CMNT_STATE>\\[^{NEWLINE}] {
	newString=yytext;
	logString.append(newString);
}

<SINGLELINE_CMNT_STATE>. {
	newString=yytext;
	logString.append(newString);
}

<SINGLELINE_CMNT_STATE><<EOF>> {
	// fprintf(logout,"Line no %d: Token <COMMENT> Lexeme %s found\n\n",logStringStart,logString.c_str());
	BEGIN INITIAL;
	tokenString="";
	logString="";
	endOfFile();
	return 0;
}

\/\* {
	BEGIN MULTILINE_CMNT_STATE;
	logStringStart=lineCount;
	newString=yytext;
	logString.append(newString);
}

<MULTILINE_CMNT_STATE>\*\/ {
	BEGIN INITIAL;
	newString=yytext;
	logString.append(newString);
	// fprintf(logout,"Line no %d: Token <COMMENT> Lexeme %s found\n\n",logStringStart,logString.c_str());
	logString="";
}

<MULTILINE_CMNT_STATE>{NEWLINE} {
	lineCount++;
	newString=yytext;
	logString.append(newString);
}


<MULTILINE_CMNT_STATE>. {
	newString=yytext;
	logString.append(newString);
}

<MULTILINE_CMNT_STATE><<EOF>> {
	BEGIN INITIAL;
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Unterminated comment %s\n\n",logStringStart,logString.c_str());
	endOfFile();
	return 0;
}

{ID} {
	// fprintf(tokenout,"<ID,%s> ",yytext);
	// fprintf(logout,"Line no %d: Token <ID> Lexeme %s found\n\n",lineCount,yytext);
	SymbolInfo *s= new  SymbolInfo(yytext, "ID");
	// cout<<*s<<endl;
	yylval.symbol = s;
	return ID;
}

{TOO_MANY_DEC} {
	increaseErrorCount();
	fprintf(errorout,"Error at line no %d: Too many decimal points %s\n\n",lineCount,yytext);
	return CONST_FLOAT;
}

{ILL_FORM_NUM} {
	increaseErrorCount();
	fprintf(errorout,"Error at line no %d: Ill formed number %s\n\n",lineCount,yytext);
	return CONST_FLOAT;
}

{INVALID_NUM_ID} {
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Invalid prefix on ID or invalid suffix on Number %s\n\n",lineCount,yytext);
}

. {
	increaseErrorCount();
	// fprintf(logout,"Error at line no %d: Unrecognized character %s\n\n",lineCount,yytext);
}

<<EOF>> {
	endOfFile();
	return 0;
}


%%


