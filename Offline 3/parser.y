%{
#include "SymbolTable.cpp"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
FILE *fp, *logout, *errorout;
extern int lineCount;
extern int errorCount;

SymbolTable table(30);
vector<string> v;


void yyerror(char *s)
{
	printf("error\n");
}


%}

%union{
	SymbolInfo* symbol;
}
%token IF ELSE FOR WHILE INT FLOAT DOUBLE CHAR RETURN VOID MAIN PRINTLN DO BREAK SWITCH CASE DEFAULT CONTINUE ASSIGNOP NOT SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP
%token <symbol> ID ADDOP MULOP RELOP LOGICOP CONST_INT CONST_FLOAT
%type <symbol> declaration_list type_specifier var_declaration unit program func_declaration func_definition parameter_list
%nonassoc LESS_PREC_THAN_ELSE
%nonassoc ELSE

%%

start : program
	{
		fprintf(logout, "Line %d: start : program\n\n", lineCount);
		fprintf(logout, "\n%s\n",table.printAllScope().c_str());
		fprintf(logout, "Total lines: %d\n", lineCount);
		fprintf(logout, "Total errors: %d\n", errorCount);
	}
	;

program : program unit 
	{
		$$ = new SymbolInfo($1->getName()+"\n"+$2->getName(),"program");
		fprintf(logout, "Line %d: program : program unit\n\n%s\n\n\n", lineCount, $$->getName().c_str());
		delete $1;
		delete $2;
	}
	| unit
	{
		$$ = $1;
		fprintf(logout, "Line %d: program : unit\n\n%s\n\n\n", lineCount, $$->getName().c_str());
	}
	;
	
unit : var_declaration
	{
		$$ = $1;
		fprintf(logout, "Line %d: unit : var_declaration\n\n%s\n\n\n", lineCount, $$->getName().c_str());
	}
     | func_declaration
	{
		$$ = $1;
		fprintf(logout, "Line %d: unit : func_declaration\n\n%s\n\n\n", lineCount, $$->getName().c_str());
	}
     | func_definition
	{
		$$ = $1;
		fprintf(logout, "Line %d: unit : func_definition\n\n%s\n\n\n", lineCount, $$->getName().c_str());
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			string returnType = $1->getName();
			string funcName = $2->getName();
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr)
			{
				errorCount++;
				fprintf(errorout, "Error at line %d: Multiple declaration of function %s\n\n", lineCount, funcName.c_str());
				fprintf(logout, "Error at line %d: Multiple declaration of function %s\n\n", lineCount, funcName.c_str());
			}
			else {
				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				table.insertSymbolInfo(f);
			}
			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+"();","func_declaration");
			fprintf(logout, "Line %d: func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n%s\n\n\n", lineCount, $$->getName().c_str());
			delete $1;
			delete $2;
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		| type_specifier ID LPAREN RPAREN compound_statement
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			$$ = new SymbolInfo($1->getName() + "," + $3->getName() + " " + $4->getName(), "parameter_list");
			fprintf(logout, "Line %d: parameter_list : parameter_list COMMA type_specifier ID\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| parameter_list COMMA type_specifier
		{
			$$ = new SymbolInfo($1->getName() + "," + $3->getName(), "parameter_list");
			fprintf(logout, "Line %d: parameter_list : parameter_list COMMA type_specifier\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| type_specifier ID
		{
			$$ = new SymbolInfo($1->getName() + " " + $2->getName(), "parameter_list");
			fprintf(logout, "Line %d: parameter_list : type_specifier ID\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| type_specifier
		{
			$$ = $1;
			fprintf(logout, "Line %d: parameter_list : type_specifier\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		;

 		
compound_statement : LCURL statements RCURL
 		    | LCURL RCURL
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+";", "var_declaration");
			fprintf(logout, "Line %d: var_declaration : type_specifier declaration_list SEMICOLON\n\n%s\n\n", lineCount, $$->getName().c_str());
			delete $1;
			delete $2;
		}
 		 ;
 		 
type_specifier	: INT
		{
			$$= new SymbolInfo("int","INT");
			fprintf(logout, "Line %d: type_specifier : INT\n\nint\n\n", lineCount);
		}
 		| FLOAT
		{
			$$= new SymbolInfo("float","FLOAT");
			fprintf(logout, "Line %d: type_specifier : FLOAT\n\nfloat\n\n", lineCount);
		}
 		| VOID
		{
			$$= new SymbolInfo("void","VOID");
			fprintf(logout, "Line %d: type_specifier : VOID\n\nvoid\n\n", lineCount);
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		  {
			$$ = new SymbolInfo($1->getName()+","+$3->getName(), "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID\n\n%s\n\n", lineCount, $$->getName().c_str());
			delete $1;
			delete $3;
		  }
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD 
		  {

		  }
 		  | ID
		  {
			$$ = new SymbolInfo($1->getName(), "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID\n\n%s\n\n", lineCount, $$->getName().c_str());
			delete $1;
		  }
 		  | ID LTHIRD CONST_INT RTHIRD
 		  ;
 		  
statements : statement
	   | statements statement
	   {

	   }
	   ;
	   
statement : var_declaration
	  | expression_statement
	  | compound_statement
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement

	  | IF LPAREN expression RPAREN statement %prec LESS_PREC_THAN_ELSE
	  | IF LPAREN expression RPAREN statement ELSE statement

	  | WHILE LPAREN expression RPAREN statement
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  | RETURN expression SEMICOLON
	  ;
	  
expression_statement 	: SEMICOLON			
			| expression SEMICOLON 
			;
	  
variable : ID 		
	 | ID LTHIRD expression RTHIRD 
	 ;
	 
expression : logic_expression	
	   | variable ASSIGNOP logic_expression 	
	   ;
			
logic_expression : rel_expression 	
		 | rel_expression LOGICOP rel_expression 	
		 ;
			
rel_expression	: simple_expression 
		| simple_expression RELOP simple_expression	
		;
				
simple_expression : term 
		  | simple_expression ADDOP term 
		  ;
					
term :	unary_expression
     |  term MULOP unary_expression
     ;

unary_expression : ADDOP unary_expression  
		 | NOT unary_expression 
		 | factor 
		 ;
	
factor	: variable 
	| ID LPAREN argument_list RPAREN
	| LPAREN expression RPAREN
	| CONST_INT 
	| CONST_FLOAT
	| variable INCOP 
	| variable DECOP
	;
	
argument_list : arguments
			  |
			  ;
	
arguments : arguments COMMA logic_expression
	      | logic_expression
	      ; 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout= fopen(argv[2],"w");
	fclose(logout);
	errorout= fopen(argv[3],"w");
	fclose(errorout);
	
	logout= fopen(argv[2],"a");
	errorout= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	

	fclose(logout);
	fclose(errorout);
	
	return 0;
}

