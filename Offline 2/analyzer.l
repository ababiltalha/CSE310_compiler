%option noyywrap

%x UNKNOWN_WORD

%{
#include<bits/stdc++.h>

int line_count=1;
int word_count=0;
int error_count=0;

char* scannedString="";


FILE *logout;
FILE *tokenout;

void increaseWordCount(){
	word_count++;
}

void increaseErrorCount(){
	error_count++;
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

void detectKeyword(char *str){
    char* s= toUpper(str);
    fprintf(tokenout,"<%s>",s);
	fprintf(logout,"Line no %d: TOKEN <%s> Lexeme %s found\n",line_count,s,str);
	// increaseWordCount();
}

void detectUnknownWord(char *str){
	increaseErrorCount();
	printf("Unknown word %s\n", str);
	fprintf(logout,"Error at line no %d: Unrecognized word %s\n",line_count,str);
}

void endOfFile(){
	fprintf(logout,"Total Line Count: %d\n",line_count);
	fprintf(logout,"Total Error Count: %d\n",error_count);
}

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n
KEYWORD if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue
CONST_INT {DIGIT}+
CONST_FLOAT {DIGIT}*({DIGIT}\.?|\.{DIGIT}){DIGIT}*([Ee][-+]?{DIGIT}+)?


%%

{WHITESPACE} {}

{NEWLINE} {line_count++;}

{KEYWORD} {detectKeyword(yytext);}

{CONST_INT} {
	printf("Integer literal found %s\n", yytext);
	fprintf(tokenout,"<CONST_INT, %s>", yytext);
	fprintf(logout,"Line no %d: TOKEN <CONST_INT, %s> Lexeme %s found\n",line_count,yytext,yytext);
}

{CONST_FLOAT} {}




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
