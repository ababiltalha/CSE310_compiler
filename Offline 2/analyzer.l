%option noyywrap

%x UNKNOWN_WORD

%{
#include<bits/stdc++.h>

using namespace std;

int lineCount=1;
int wordCount=0;
int errorCount=0;

string scannedString="";


FILE *logout;
FILE *tokenout;

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
	}
	return sp;
}



void detectKeyword(char *str){
    char* s= toUpper(str);
    fprintf(tokenout,"<%s> ",s);
	fprintf(logout,"Line no %d: Token <%s> Lexeme %s found\n\n",lineCount,s,str);
	// increaseWordCount();
}

void detectUnknownWord(char *str){
	increaseErrorCount();
	// printf("Unknown word %s\n", str);
	fprintf(logout,"Error at line no %d: Unrecognized word %s\n\n",lineCount,str);
}

void endOfFile(){
	fprintf(logout,"Total lines: %d\n",lineCount);
	fprintf(logout,"Total errors: %d\n",errorCount);
}

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n
KEYWORD if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue
CONST_INT {DIGIT}+
CONST_FLOAT {DIGIT}*({DIGIT}\.?|\.{DIGIT}){DIGIT}*([Ee][-+]?{DIGIT}+)?
CHAR [ -~]
SPECIAL_CHAR \\[\\nfratbv0\']
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
UNFINISHED_CHAR (\'(({CHAR})?)|({SPECIAL_CHAR}))|(\'\\\')
EMPTY_CHAR \'\'


%%

{WHITESPACE} {}

{NEWLINE} {lineCount++;}

{KEYWORD} {detectKeyword(yytext);}

{CONST_INT} {
	// printf("Integer literal found %s\n", yytext);
	fprintf(tokenout,"<CONST_INT, %s> ", yytext);
	fprintf(logout,"Line no %d: Token <CONST_INT> Lexeme %s found\n\n",lineCount,yytext);
	// insert into symbolTable
}

{CONST_FLOAT} {
	fprintf(tokenout,"<CONST_FLOAT, %s> ", yytext);
	fprintf(logout,"Line no %d: Token <CONST_FLOAT> Lexeme %s found\n\n",lineCount,yytext);
	// insert into symbolTable
}

[\'][\'] {
	increaseErrorCount();
	fprintf(logout,"Error at line no %d: Empty character constant error \'\'\n\n",lineCount);
}

{MULTI_CHAR} {
	increaseErrorCount();
	fprintf(logout,"Error at line no %d: Multi character constant error %s\n\n",lineCount,yytext);
}

{UNFINISHED_CHAR} {
	increaseErrorCount();
	fprintf(logout,"Error at line no %d: Unterminated character %s\n\n",lineCount,yytext);
}

{CONST_CHAR} {
	char ch= toSpecial(yytext);
	fprintf(tokenout,"<CONST_CHAR, %c> ", ch);
	fprintf(logout,"Line no %d: Token <CONST_CHAR> Lexeme %s found\n\n",lineCount,yytext);
	// insert yytext in symbolTable;
}

"+"|"-" {
	fprintf(tokenout,"<ADDOP,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <ADDOP> Lexeme %s found\n\n",lineCount,yytext);
}

"*"|"/"|"%" {
	fprintf(tokenout,"<MULOP,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <MULOP> Lexeme %s found\n\n",lineCount,yytext);
}

"++"|"--" {
	fprintf(tokenout,"<INCOP,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <INCOP> Lexeme %s found\n\n",lineCount,yytext);
}

"<"|"<="|">"|">="|"=="|"!=" {
	fprintf(tokenout,"<RELOP,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <RELOP> Lexeme %s found\n\n",lineCount,yytext);
}

"=" {
	fprintf(tokenout,"<ASSIGNOP,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <ASSIGNOP> Lexeme %s found\n\n",lineCount,yytext);
}

"&&"|"||" {
	fprintf(tokenout,"<LOGICOP,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <LOGICOP> Lexeme %s found\n\n",lineCount,yytext);
}

"!" {
	fprintf(tokenout,"<NOT,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <NOT> Lexeme %s found\n\n",lineCount,yytext);
}

"(" {
	fprintf(tokenout,"<LPAREN,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <LPAREN> Lexeme %s found\n\n",lineCount,yytext);
}

")" {
	fprintf(tokenout,"<RPAREN,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <RPAREN> Lexeme %s found\n\n",lineCount,yytext);
}

{LCURL} { 
	// scope
	fprintf(tokenout,"<LCURL,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <LCURL> Lexeme %s found\n\n",lineCount,yytext);
}

{RCURL} {
	// scope
	fprintf(tokenout,"<RCURL,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <RCURL> Lexeme %s found\n\n",lineCount,yytext);
}

{LTHIRD} {
	fprintf(tokenout,"<LTHIRD,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <LTHIRD> Lexeme %s found\n\n",lineCount,yytext);
}

{RTHIRD} {
	fprintf(tokenout,"<RTHIRD,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <RTHIRD> Lexeme %s found\n\n",lineCount,yytext);
}

"," {
	fprintf(tokenout,"<COMMA,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <COMMA> Lexeme %s found\n\n",lineCount,yytext);
}

";" {
	fprintf(tokenout,"<SEMICOLON,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <SEMICOLON> Lexeme %s found\n\n",lineCount,yytext);
}

{ID} {
	fprintf(tokenout,"<ID,%s> ",yytext);
	fprintf(logout,"Line no %d: Token <ID> Lexeme %s found\n\n",lineCount,yytext);
	// insert
}

{TOO_MANY_DEC} {
	increaseErrorCount();
	fprintf(logout,"Error at line no %d: Too many decimal points %s\n\n",lineCount,yytext);
}

{ILL_FORM_NUM} {
	increaseErrorCount();
	fprintf(logout,"Error at line no %d: Ill formed number %s\n\n",lineCount,yytext);
}

{INVALID_NUM_ID} {
	increaseErrorCount();
	fprintf(logout,"Error at line no %d: Invalid prefix on ID or invalid suffix on Number %s\n\n",lineCount,yytext);
}








%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("log.txt","w");
	tokenout= fopen("token.txt","w");

	yyin= fin;
	yylex();
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
    printf("\n");
	return 0;
}
