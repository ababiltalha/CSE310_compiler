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
vector<string> parameterTypeList;
vector<string> parameterNameList;
string returnTypeToMatch;

void split(const string s, char delim) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        v.push_back(item);
    }
}

string getArrayName(const string s){
	stringstream ss(s);
	string item;
	while(getline(ss, item, '['))
		return item;
}

void splitParameterTypeList(const string s, char delim) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        parameterTypeList.push_back(item);
    }
}

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
                    // multiple parameter same error
					errorCount++;
					fprintf(errorout, "Error at line %d: Multiple declaration of %s in parameter\n\n", lineCount, paramName.c_str());
					fprintf(logout, "Error at line %d: Multiple declaration of %s in parameter\n\n", lineCount, paramName.c_str());
                    flag=false;
                }
            }
			// if(flag)
				parameterNameList.push_back(paramName);
		}
    }
}

void clearVector() {
	v.clear();
}

void clearParameterTypeList() {
	parameterTypeList.clear();
}

void clearParameterNameList() {
	parameterNameList.clear();
}

void yyerror(char *s)
{
	errorCount++;
	fprintf(errorout, "Error at line %d: syntax error\n\n", lineCount);
	fprintf(logout, "Error at line %d: syntax error\n\n", lineCount);
}


%}

%union{
	SymbolInfo* symbol;
}
%token IF ELSE FOR WHILE INT FLOAT DOUBLE CHAR RETURN VOID PRINTLN DO BREAK SWITCH CASE DEFAULT CONTINUE ASSIGNOP NOT SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP
%token <symbol> ID ADDOP MULOP RELOP LOGICOP CONST_INT CONST_FLOAT
%type <symbol> declaration_list type_specifier var_declaration unit program func_declaration func_definition parameter_list factor variable expression logic_expression argument_list arguments rel_expression simple_expression term unary_expression statement statements compound_statement expression_statement

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start : program
	{
		fprintf(logout, "Line %d: start : program\n\n", lineCount);
	}
	;

program : program unit 
	{
		$$ = new SymbolInfo($1->getName()+"\n"+$2->getName(),"program");
		fprintf(logout, "Line %d: program : program unit\n\n%s\n\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
		// deleete $2;
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
				splitParameterTypeList($4->getType(), ',');


				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				table.insertSymbolInfo(f);
				clearParameterTypeList();
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+"("+$4->getName()+");","func_declaration");
			fprintf(logout, "Line %d: func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n%s\n\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
		}
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
			table.enterScope();table.exitScope(); // dummy scope for declaration
			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+"();","func_declaration");
			fprintf(logout, "Line %d: func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n%s\n\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN 
		{
			string returnType = $1->getName();
			returnTypeToMatch= returnType;
			string funcName = $2->getName();
			splitParameterTypeList($4->getType(), ',');
			// for (int i = 0; i < parameterTypeList.size(); i++)
        		// cout<<parameterTypeList[i]<<endl;
			extractParameterNameList($4->getName(),',');
			// for (int i = 0; i < parameterNameList.size(); i++)
        		// cout<<parameterNameList[i]<<endl;
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr) // exists in symboltable, may or may not be func, decl or defn
			{
				// cout<<temp->getType()<<endl;
				
				if (temp->getType()=="FUNCTION"){
					FunctionInfo* ftemp=(FunctionInfo*) temp;
					if(ftemp->getDefined()){
						errorCount++;
						fprintf(errorout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
						fprintf(logout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
					}
					else { // decl but not defn, working case
						// return type matching
						if (ftemp->getReturnType() != returnType) {
							errorCount++;
							fprintf(errorout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						// total number of arguments mismatch
						if ((ftemp->getParameterTypeList().size() != parameterTypeList.size())) {
							
							errorCount++;
							fprintf(errorout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						else {
							for(int i=0; i<ftemp->getParameterTypeList().size(); i++){
								if (ftemp->getParameterTypeList()[i] != parameterTypeList[i]){
									errorCount++;
									fprintf(errorout, "Error at line %d: %dth parameter mismatch with declaration in function %s\n\n", lineCount, i+1, funcName.c_str());
									fprintf(logout, "Error at line %d: %dth parameter mismatch with declaration in function %s\n\n", lineCount, i+1, funcName.c_str());
									break;
								}
							}

						}
						ftemp->setDefined(true);
						
					}
				}
				else { // not a function 
					errorCount++;
					fprintf(errorout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, funcName.c_str());
					fprintf(logout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, funcName.c_str());
				}
			}
			else { // not in symboltable
				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				f->setDefined(true);
				table.insertSymbolInfo(f);
			}
			;
		} compound_statement {
			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+"("+$4->getName()+")"+$7->getName()+"\n","func_definition");
			fprintf(logout, "Line %d: func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n%s\n\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $4;
			// deleete $7;
		}
		| type_specifier ID LPAREN RPAREN
		{
			string returnType = $1->getName();
			returnTypeToMatch= returnType;
			string funcName = $2->getName();
			
			SymbolInfo* temp = table.lookUpSymbol(funcName);
			if (temp!=nullptr) // exists in symboltable, may or may not be func, decl or defn
			{
				// cout<<temp->getType()<<endl;
				
				if (temp->getType()=="FUNCTION"){
					FunctionInfo* ftemp=(FunctionInfo*) temp;
					if(ftemp->getDefined()){
						errorCount++;
						fprintf(errorout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
						fprintf(logout, "Error at line %d: Multiple definition of function %s\n\n", lineCount, funcName.c_str());
					}
					else { // decl but not defn, working case
						// return type matching

						if (ftemp->getReturnType() != returnType) {
							errorCount++;
							fprintf(errorout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Return type mismatch with function declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						// total number of arguments mismatch
						if ((ftemp->getParameterTypeList().size() != 0)) {
							errorCount++;
							fprintf(errorout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
							fprintf(logout, "Error at line %d: Total number of arguments mismatch with declaration in function %s\n\n", lineCount, funcName.c_str());
						}
						
						ftemp->setDefined(true);
						
					}
				}
				else { // not a function 
					errorCount++;
					fprintf(errorout, "Error at line %d: %s not a function\n\n", lineCount, funcName.c_str());
					fprintf(logout, "Error at line %d: %s not a function\n\n", lineCount, funcName.c_str());
				}
			}
			else { // not in symboltable
				FunctionInfo* f= new FunctionInfo(funcName, returnType);
				f->setDefined(true);
				table.insertSymbolInfo(f);
			}
			
		} compound_statement {
			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+"()"+$6->getName()+"\n","func_definition");
			fprintf(logout, "Line %d: func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n%s\n\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $6;
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			$$ = new SymbolInfo($1->getName() + "," + $3->getName() + " " + $4->getName(), $1->getType() + "," + $3->getType());
			fprintf(logout, "Line %d: parameter_list : parameter_list COMMA type_specifier ID\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| parameter_list COMMA type_specifier
		{
			$$ = new SymbolInfo($1->getName() + "," + $3->getName(), $1->getType() + "," + $3->getType());
			fprintf(logout, "Line %d: parameter_list : parameter_list COMMA type_specifier\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| type_specifier ID
		{
			$$ = new SymbolInfo($1->getName() + " " + $2->getName(), $1->getType());
			fprintf(logout, "Line %d: parameter_list : type_specifier ID\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| type_specifier
		{
			$$ = $1;
			fprintf(logout, "Line %d: parameter_list : type_specifier\n\n%s\n\n",  lineCount, $$->getName().c_str());
		}
		| error
		{

		}
		;

 		
compound_statement : LCURL enter_scope statements RCURL
			{
				

				$$ = new SymbolInfo("{\n"+$3->getName()+"\n}\n","compound_statement");
				fprintf(logout, "Line %d: compound_statement : LCURL statements RCURL\n\n%s\n\n",  lineCount, $$->getName().c_str());

				fprintf(logout, "\n\n%s\n\n", table.printAllScope().c_str());
				table.exitScope();
				
			}
 		    | LCURL enter_scope RCURL
			{
				$$ = new SymbolInfo("{\n}\n","compound_statement");
				fprintf(logout, "Line %d: compound_statement : LCURL RCURL\n\n%s\n\n",  lineCount, $$->getName().c_str());

				// fprintf(logout, "\n\n%s\n\n", table.printAllScope().c_str());
				table.exitScope();
			};

enter_scope :
			{
				table.enterScope();
				if ((parameterNameList.size() != parameterTypeList.size())) {
					errorCount++;
					fprintf(errorout, "Error at line %d: Parameters name not given in function definition\n\n", lineCount);
					fprintf(logout, "Error at line %d: Parameters name not given in function definition\n\n", lineCount);
				}
				else if(parameterTypeList.size()>0){
					for(int i=0; i<parameterTypeList.size(); i++){
						table.insertSymbol(parameterNameList[i], parameterTypeList[i]);
					}
				}
				clearParameterNameList();
				clearParameterTypeList();
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			string varType = $1->getName();
			string varList = $2->getName();
			if ($1->getName()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Variable type cannot be void \n\n", lineCount);
				fprintf(logout, "Error at line %d: Variable type cannot be void \n\n", lineCount);
			}
			
			else {
				split(varList,',');
				for (string var : v){
					
					// printf("%s ",iter.c_str());

					if ((var.find("[") != string::npos) || (var.find("]") != string::npos)) {
						// printf("array");
						string arrayName = getArrayName(var);
						bool newSymbol = table.insertSymbol(arrayName, varType+"[]");
						if(!newSymbol){
							errorCount++;
							fprintf(errorout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, arrayName.c_str());
							fprintf(logout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, arrayName.c_str());
						}
					}

					else {
						bool newSymbol = table.insertSymbol(var, varType);
						if(!newSymbol){
							errorCount++;
							fprintf(errorout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, var.c_str());
							fprintf(logout, "Error at line %d: Multiple declaration of %s\n\n", lineCount, var.c_str());
						}
					}


				}
				clearVector();
			}

			$$ = new SymbolInfo($1->getName()+" "+$2->getName()+";", "var_declaration");
			fprintf(logout, "Line %d: var_declaration : type_specifier declaration_list SEMICOLON\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
		}
 		 ;
 		 
type_specifier	: INT
		{
			$$= new SymbolInfo("int","int");
			fprintf(logout, "Line %d: type_specifier : INT\n\nint\n\n", lineCount);
		}
 		| FLOAT
		{
			$$= new SymbolInfo("float","float");
			fprintf(logout, "Line %d: type_specifier : FLOAT\n\nfloat\n\n", lineCount);
		}
 		| VOID
		{
			$$= new SymbolInfo("void","void");
			fprintf(logout, "Line %d: type_specifier : VOID\n\nvoid\n\n", lineCount);
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		  {
			$$ = new SymbolInfo($1->getName()+","+$3->getName(), "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $3;
		  }
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD 
		  {
			if($5->getName()=="0"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
				fprintf(logout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
			}
			
			$$ = new SymbolInfo($1->getName()+","+$3->getName()+"["+$5->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $3;
			// deleete $5;
		  }
 		  | ID
		  {
			$$ = new SymbolInfo($1->getName(), "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
		  }
 		  | ID LTHIRD CONST_INT RTHIRD
		  {
			if($3->getName()=="0"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
				fprintf(logout, "Error at line %d: Array size cannot be zero\n\n", lineCount);
			}
			
			$$ = new SymbolInfo($1->getName()+"["+$3->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $3;
		  }
		  | ID LTHIRD RTHIRD
		  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Array size undefined\n\n", lineCount);
			fprintf(logout, "Error at line %d: Array size undefined\n\n", lineCount);

			$$ = new SymbolInfo($1->getName()+"[]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID LTHIRD RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
			
		  }
		  | declaration_list COMMA ID LTHIRD RTHIRD 
		  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Array size undefined\n\n", lineCount);
			fprintf(logout, "Error at line %d: Array size undefined\n\n", lineCount);

			$$ = new SymbolInfo($1->getName()+","+$3->getName()+"[]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : declaration_list COMMA ID LTHIRD RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
		  }
 		  | ID LTHIRD CONST_FLOAT RTHIRD
		  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
			fprintf(logout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);

			$$ = new SymbolInfo($1->getName()+"["+$3->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list : ID LTHIRD CONST_FLOAT RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
			
		  }
		  | declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD 
		  {
			errorCount++;
			fprintf(errorout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
			fprintf(logout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);

			$$ = new SymbolInfo($1->getName()+","+$3->getName()+"["+$5->getName()+"]", "declaration_list");
			fprintf(logout, "Line %d: declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
		  }
 		  ;
 		  
statements : statement
		{
			$$=$1;
			fprintf(logout, "Line %d: statements : statement\n\n%s\n\n", lineCount, $$->getName().c_str());
		}
	   | statements statement
	    {
			$$ = new SymbolInfo($1->getName()+"\n"+$2->getName(), "statements");
			fprintf(logout, "Line %d: statements : statements statement\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
	    }
	   ;
	   
statement : var_declaration
	  {
		$$=$1;
		fprintf(logout, "Line %d: statement : var_declaration\n\n%s\n\n", lineCount, $$->getName().c_str());
	  }
	  | expression_statement
	  {
		$$=$1;
		fprintf(logout, "Line %d: statement : expression_statement\n\n%s\n\n", lineCount, $$->getName().c_str());
	  }
	  | compound_statement
	  {
		$$=$1;
		fprintf(logout, "Line %d: statement : compound_statement\n\n%s\n\n", lineCount, $$->getName().c_str());
	  }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  {
		$$ = new SymbolInfo("for("+$3->getName()+$4->getName()+$5->getName()+")"+$7->getName(), "statement");
		fprintf(logout, "Line %d: statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $3;
		// deleete $4;
		// deleete $5;
		// deleete $7;
	  }
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	  {
		$$ = new SymbolInfo("if("+$3->getName()+")"+$5->getName(), "statement");
		fprintf(logout, "Line %d: statement : IF LPAREN expression RPAREN statement\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $3;
		// deleete $5;
	  }
	  | IF LPAREN expression RPAREN statement ELSE statement
	  {
		$$ = new SymbolInfo("if("+$3->getName()+")"+$5->getName()+ "else\n"+$7->getName(), "statement");
		fprintf(logout, "Line %d: statement : IF LPAREN expression RPAREN statement ELSE statement\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $3;
		// deleete $5;
		// deleete $7;
	  }

	  | WHILE LPAREN expression RPAREN statement
	  {
		$$ = new SymbolInfo("while("+$3->getName()+")"+$5->getName(), "statement");
		fprintf(logout, "Line %d: statement : WHILE LPAREN expression RPAREN statement\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $3;
		// deleete $5;
	  }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  {
		SymbolInfo *temp = table.lookUpSymbol($3->getName());
		//handle undeclared variable error
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $3->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $3->getName().c_str());
		}
		else $$ = new SymbolInfo("printf("+$3->getName()+");", "statement");
		fprintf(logout, "Line %d: statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $3;
		// deleete temp;
	  }
	  | RETURN expression SEMICOLON
	  {
		// check return type in func_defn and decl
		if($2->getType()=="expression") {
			errorCount++;
			fprintf(errorout, "Error at line %d: Assignment expression does not have a return type\n\n", lineCount);
			fprintf(logout, "Error at line %d: Assignment expression does not have a return type\n\n", lineCount);
		}

		else if(returnTypeToMatch=="void");

		else if($2->getType()!=returnTypeToMatch){
			errorCount++;
			fprintf(errorout, "Error at line %d: Return type mismatch\n\n", lineCount);
			fprintf(logout, "Error at line %d: Return type mismatch\n\n", lineCount);
		}
		
		$$ = new SymbolInfo("return "+$2->getName()+";", "statement");
		fprintf(logout, "Line %d: statement : RETURN expression SEMICOLON\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $2;
	  }
	  ;
	  
expression_statement 	: SEMICOLON
			{
				$$ = new SymbolInfo(";", "expression_statement");
				fprintf(logout, "Line %d: expression_statement : SEMICOLON\n\n%s\n\n", lineCount, $$->getName().c_str());
			}			
			| expression SEMICOLON 
			{
				$$ = new SymbolInfo($1->getName()+";", "expression_statement");
				fprintf(logout, "Line %d: expression_statement : expression SEMICOLON\n\n%s\n\n", lineCount, $$->getName().c_str());
			}
			| error
			{}
			;
	  
variable : ID 		
	 {
		SymbolInfo *temp = table.lookUpSymbol($1->getName());
		//handle undeclared variable error
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $1->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $1->getName().c_str());
			$$ = new SymbolInfo($1->getName(),"variable");
		}
		else $$ = new SymbolInfo(temp->getName(), temp->getType());
		// // cout<<lineCount<<$$->getType()<<endl;;
		fprintf(logout, "Line %d: variable : ID\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
	 }
	 | ID LTHIRD expression RTHIRD 
	 {
		SymbolInfo *temp = table.lookUpSymbol($1->getName());
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $1->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $1->getName().c_str());
			$$ = new SymbolInfo($1->getName()+"["+$3->getName()+"]","variable");
		}
		else {
			string varType = temp->getType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [float] error
				if ($3->getType()!="int"){
					errorCount++;
					fprintf(errorout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
					fprintf(logout, "Error at line %d: Expression inside third brackets not an integer\n\n", lineCount);
				}
				$$ = new SymbolInfo($1->getName()+"["+$3->getName()+"]", getArrayName(varType));
			} 
			else { 
				errorCount++;
				fprintf(errorout, "Error at line %d: %s not an array\n\n", lineCount, $1->getName().c_str());
				fprintf(logout, "Error at line %d: %s not an array\n\n", lineCount, $1->getName().c_str());
				$$ = new SymbolInfo($1->getName()+"["+$3->getName()+"]","variable");
			}
		}
		fprintf(logout, "Line %d: variable : ID LTHIRD expression RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
		// deleete $3;
	 }
	 | ID LTHIRD RTHIRD 
	 {
		SymbolInfo *temp = table.lookUpSymbol($1->getName());
		if(temp==nullptr){
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $1->getName().c_str());
			fprintf(logout, "Error at line %d: Undeclared variable %s\n\n", lineCount, $1->getName().c_str());
			$$ = new SymbolInfo($1->getName()+"[]","variable");
		}
		else {
			string varType = temp->getType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [] error
				errorCount++;
				fprintf(errorout, "Error at line %d: Array size undefined\n\n", lineCount);
				fprintf(logout, "Error at line %d: Array size undefined\n\n", lineCount);
				$$ = new SymbolInfo($1->getName()+"[]", getArrayName(varType));
			} 
			else { 
				errorCount++;
				fprintf(errorout, "Error at line %d: %s not an array\n\n", lineCount, $1->getName().c_str());
				fprintf(logout, "Error at line %d: %s not an array\n\n", lineCount, $1->getName().c_str());
				$$ = new SymbolInfo($1->getName()+"[]","variable");
			}
		}
		fprintf(logout, "Line %d: variable : ID LTHIRD expression RTHIRD\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
		// deleete $3;
	 }
	 ;
	 
expression : logic_expression
		{
			$$=$1;
			fprintf(logout, "Line %d: expression : logic_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
		}
	   | variable ASSIGNOP logic_expression
	   	{
			// bunch of type mismatch handling (but int in float is allowed (added))
			// cout<<$1->getType()<<" "<<$3->getType()<<endl;
			if ($1->getType()=="void" || $3->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			else if ($1->getType()!=$3->getType()){
				string varType= $1->getType();
				string exprType= $3->getType();
				if ((varType.find("[") != string::npos) || (exprType.find("[") != string::npos)) { // either an array
					errorCount++;
					fprintf(errorout, "Error at line %d: Type mismatch, %s is an array\n\n", lineCount, $1->getName().c_str());
					fprintf(logout, "Error at line %d: Type mismatch, %s is an array\n\n", lineCount, $1->getName().c_str());
				}
				else if (varType=="float" && exprType=="int") ;
				else if (varType=="variable" || exprType=="factor") ;
				else {
					errorCount++;
					// cout<<varType<<" "<<exprType<<endl;
					fprintf(errorout, "Error at line %d: Type Mismatch\n\n", lineCount);
					fprintf(logout, "Error at line %d: Type Mismatch\n\n", lineCount);
				}
			}
			$$ = new SymbolInfo($1->getName()+"="+$3->getName(), "expression");
			fprintf(logout, "Line %d: expression : variable ASSIGNOP logic_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $3;
	   	}
	   ;
			
logic_expression : rel_expression
		{
			$$=$1;
			fprintf(logout, "Line %d: logic_expression : rel_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
		}
		 | rel_expression LOGICOP rel_expression
		{
			if ($1->getType()=="void" || $3->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			$$ = new SymbolInfo("", "int");
			$$->setName($1->getName()+$2->getName()+$3->getName());
			fprintf(logout, "Line %d: logic_expression : rel_expression LOGICOP rel_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $3;
		}
		 ;
			
rel_expression	: simple_expression
		{
			$$=$1;
			fprintf(logout, "Line %d: rel_expression : simple_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
		}
		| simple_expression RELOP simple_expression
		{
			if ($1->getType()=="void" || $3->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			$$ = new SymbolInfo("", "int");
			$$->setName($1->getName()+$2->getName()+$3->getName());
			fprintf(logout, "Line %d: rel_expression : simple_expression RELOP simple_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $3;
		}
		;
				
simple_expression : term 
		{
			$$=$1;
			fprintf(logout, "Line %d: simple_expression : term\n\n%s\n\n", lineCount, $$->getName().c_str());
		}
		  | simple_expression ADDOP term 
		{
			//handle int addition and float addition
			string exprType;
			// // cout<<lineCount<<$1->getType()<<endl;
			// // cout<<lineCount<<$3->getType()<<endl;
			if(($1->getType()=="int") && ($3->getType()=="int")) exprType= "int"; 
			else exprType= "float";
			if ($1->getType()=="void" || $3->getType()=="void"){
				// errorCount++;
				// fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				// fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
				exprType= "void";
			}

			$$ = new SymbolInfo("", exprType);
			$$->setName($1->getName()+$2->getName()+$3->getName());
			// // cout<<lineCount<<$$->getType()<<endl;
			fprintf(logout, "Line %d: simple_expression : simple_expression ADDOP term\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $1;
			// deleete $2;
			// deleete $3;
		}
		  ;
					
term :	unary_expression
	 {
		$$=$1;
		fprintf(logout, "Line %d: term : unary_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
	 }
     |  term MULOP unary_expression
	 {
		//handle errors
		if ($1->getType()=="void" || $3->getType()=="void"){
			// errorCount++;
			// fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
			// fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			$$ = new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"void");
		}
		else if($2->getName()=="%"){ // modulus cases
			if(($1->getType()=="int") && ($3->getType()=="int")){
				if($3->getName()=="0"){
					errorCount++;
					fprintf(errorout, "Error at line %d: Modulus by Zero\n\n", lineCount);
					fprintf(logout, "Error at line %d: Modulus by Zero\n\n", lineCount);
				}
			}
			else { // non int operand
				errorCount++;
				fprintf(errorout, "Error at line %d: Non-Integer operand on modulus operator\n\n", lineCount);
				fprintf(logout, "Error at line %d: Non-Integer operand on modulus operator\n\n", lineCount);
			}
			$$ = new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"int");
		}
		else {
			if(($1->getType()=="int")&&($3->getType()=="int"))
				$$ = new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"int");
			else $$ = new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"float");
		}
		fprintf(logout, "Line %d: term : term MULOP unary_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
		// deleete $2;
		// deleete $3;

	 }
     ;

unary_expression : ADDOP unary_expression  
		 {
			if ($2->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			$$ = new SymbolInfo($1->getName()+$2->getName(), $2->getType());
			fprintf(logout, "Line %d: unary_expression : ADDOP unary_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $2;
		 }
		 | NOT unary_expression 
		 {
			if ($2->getType()=="void"){
				errorCount++;
				fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
			}
			$$ = new SymbolInfo("!"+$2->getName(), $2->getType());
			fprintf(logout, "Line %d: unary_expression : NOT unary_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
			// deleete $2;
		 }
		 | factor 
		 {
			$$=$1;
			fprintf(logout, "Line %d: unary_expression : factor\n\n%s\n\n", lineCount, $$->getName().c_str());
		 }
		 ;
	
factor	: variable 
	{
		$$=$1;
		fprintf(logout, "Line %d: factor : variable\n\n%s\n\n", lineCount, $$->getName().c_str());
	}
	| ID LPAREN argument_list RPAREN
	{
		string returnType= "factor";
		string funcName = $1->getName();
		SymbolInfo* temp = table.lookUpSymbol(funcName);
		if (temp==nullptr)
		{
			errorCount++;
			fprintf(errorout, "Error at line %d: Undeclared function %s\n\n", lineCount, funcName.c_str());
			fprintf(logout, "Error at line %d: Undeclared function %s\n\n", lineCount, funcName.c_str());
		}
		else {
			if(temp->getType()=="FUNCTION"){
				FunctionInfo* ftemp= (FunctionInfo*) temp;
				returnType= ftemp->getReturnType();
				splitParameterTypeList($3->getType(),',');
				// if(ftemp->getReturnType()=="void"){
				// 	errorCount++;
				// 	fprintf(errorout, "Error at line %d: Void function used in expression\n\n", lineCount);
				// 	fprintf(logout, "Error at line %d: Void function used in expression\n\n", lineCount);
				// }
				// else 
				if(parameterTypeList.size()!=ftemp->getParameterTypeList().size()){
					errorCount++;
					fprintf(errorout, "Error at line %d: Total number of arguments mismatch in function %s\n\n", lineCount, funcName.c_str());
					fprintf(logout, "Error at line %d: Total number of arguments mismatch in function %s\n\n", lineCount, funcName.c_str());
				}
				else {
					for(int i=0; i<ftemp->getParameterTypeList().size(); i++){
						if (parameterTypeList[i].find("[") != string::npos){ // array check
							errorCount++;
							fprintf(errorout, "Error at line %d: Type mismatch, argument is an array\n\n", lineCount);
							fprintf(logout, "Error at line %d: Type mismatch, argument is an array\n\n", lineCount);
							break;
						}
						if (ftemp->getParameterTypeList()[i] != parameterTypeList[i]){
							errorCount++;
							fprintf(errorout, "Error at line %d: %dth argument mismatch in function %s\n\n", lineCount, i+1, funcName.c_str());
							fprintf(logout, "Error at line %d: %dth argument mismatch in function %s\n\n", lineCount, i+1, funcName.c_str());
							break;
						}
					}

				}

				clearParameterTypeList();
			}
			else {
				errorCount++;
				fprintf(errorout, "Error at line %d: %s not a function\n\n", lineCount, funcName.c_str());
				fprintf(logout, "Error at line %d: %s not function\n\n", lineCount, funcName.c_str());	
			}
		}
		$$ = new SymbolInfo($1->getName()+"("+$3->getName()+")", returnType);
		fprintf(logout, "Line %d: factor : ID LPAREN argument_list RPAREN\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
		// deleete $3;
	}
	| LPAREN expression RPAREN
	{
		$$ = new SymbolInfo("("+$2->getName()+")", $2->getType());
		fprintf(logout, "Line %d: factor : LPAREN expression RPAREN\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $2;
	}
	| CONST_INT 
	{
		$$ = $1;
		fprintf(logout, "Line %d: factor : CONST_INT\n\n%s\n\n", lineCount, $$->getName().c_str());
	}
	| CONST_FLOAT
	{
		$$ = $1;
		fprintf(logout, "Line %d: factor : CONST_FLOAT\n\n%s\n\n", lineCount, $$->getName().c_str());
	}
	| variable INCOP
	{
		$$ = new SymbolInfo($1->getName()+"++",$1->getType());
		fprintf(logout, "Line %d: factor : variable INCOP\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
	}
	| variable DECOP
	{
		$$ = new SymbolInfo($1->getName()+"--",$1->getType());
		fprintf(logout, "Line %d: factor : variable DECOP\n\n%s\n\n", lineCount, $$->getName().c_str());
		// deleete $1;
	}
	;
	
argument_list : arguments
			{
				$$=$1;
				fprintf(logout, "Line %d: argument_list : arguments\n\n%s\n\n", lineCount, $$->getName().c_str());
			}
			  |
			{
				$$=new SymbolInfo("", "void");
				fprintf(logout, "Line %d: argument_list : \n\n%s\n\n", lineCount, $$->getName().c_str());
			}
			  ;
	
arguments : arguments COMMA logic_expression
			{
				$$ = new SymbolInfo($1->getName()+","+$3->getName(),$1->getType()+","+$3->getType());
				fprintf(logout, "Line %d: arguments : arguments COMMA logic_expression\n\n%s\n\n", lineCount, $$->getName().c_str());
				// deleete $1;
				// deleete $3;
			}
	      | logic_expression
			{
				$$=$1;
				fprintf(logout, "Line %d: arguments : logic_expression\n\n%s\n\n", lineCount, $1->getName().c_str());
			}
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
	
	fprintf(logout, "\n%s\n",table.printAllScope().c_str());
	fprintf(logout, "Total lines: %d\n", lineCount);
	fprintf(logout, "Total errors: %d\n", errorCount);

	fclose(logout);
	fclose(errorout);
	
	return 0;
}

