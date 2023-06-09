#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "Interpreter.h"

using namespace std;

void start(string fileName)
{
	fstream my_file;
	my_file.open(fileName);
	if (!my_file)
	{
		cout << "The file does not exist!";
	}
	else
	{
		string codeLine;
		Lexer lexer;
		Parser parser;
		Compiler compiler;

		while (getline(my_file, codeLine))
		{
			lexer.Lex(codeLine);
		}
		//lexer.ToString();

		parser.Parse(lexer.GetTokenList());

		//parser.ToString();

		parser.CheckSyntax();

		compiler.BuildCode(parser.GetSyntaxTree()->Root);

		compiler.Compile(parser.GetSyntaxTree());

		//compiler->ToString();

		Interpreter::getInstance(compiler.GetCodeObject())->Interprete(compiler.GetByteCodeList());
	}
	my_file.close();
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc > 1)
		{
			start(argv[1]);
		}
		start("p.txt");
	}
	catch (exception &e)
	{
		cout << e.what();
	}
	return 0;
}