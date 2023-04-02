#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "Interpreter.h"

using namespace std;

int main()
{
	fstream my_file;
	my_file.open("p.txt");
	if (!my_file) 
	{
		cout << "The file does not exist!";
	}
	else 
	{
		string codeLine;
		Lexer* lexer = new Lexer();
		while (getline(my_file, codeLine))
		{
			lexer->Lex(codeLine);
		}
		//lexer->ToString();

		Parser* parser = new Parser();
		parser->Parse(lexer->GetTokenList());
		
		//parser->ToString();

		parser->CheckSyntax();

		Compiler* compiler = new Compiler();

		compiler->BuildCode(parser->GetSyntaxTree()->Root);

		compiler->Compile(parser->GetSyntaxTree());

		//compiler->ToString();

		Interpreter* interpreter = Interpreter::getInstance(compiler->GetCodeObject());

		interpreter->Interprete(compiler->GetByteCodeList());

	}
	my_file.close();
	return 0;
}