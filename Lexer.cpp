#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Lexer.h"

using namespace std;

int Lexer::line = 0;

Lexer::Lexer()
{
	//this->TokenList = new vector<Token*>();


	this->NumOperators = {"+", "-", "/", "*"};
	this->BoolOperators = {"or", "and"};
	this->EqualOperators = { "==", "<=", ">=", "+=", "-=", "*=", "/=", "=" ,"<", ">"};
	this->IteratorOperators = { "in" };
	this->KeyWords = {"print", "return"};
	this->Branches = { "elif", "if", "else", "while", "for"};
	this->Delimiters = { ":", "(", ")" , "\""};
}

int Lexer::CheckIndentation(string* CodeLine)
{
	int count = 0;
	while (isspace(CodeLine->at(0)))
	{
		if (isspace(CodeLine->at(0)))
		{
			CodeLine->erase(CodeLine->begin());
			count++;
		}
		else break;
	}
	return count;
}

void Lexer::ReplaceWhiteSpace(string* CodeLine)
{
	for (int i = 0; i < CodeLine->length(); i++)
	{
		if (isspace(CodeLine->at(i)))
			CodeLine->at(i) = ' ';
	}
}

void Lexer::Lex(string CodeLine)
{
	this->line++;
	int codeIndex = 0;
	ReplaceWhiteSpace(&CodeLine);
	int indentation = CheckIndentation(&CodeLine);
	bool identifiedToken = false;
	string currentLine;

	while (codeIndex < CodeLine.length())
	{
		string currentToken;
		identifiedToken = false;
		int whitespace = CodeLine.find(" ", codeIndex);
		if (CodeLine[codeIndex] == '[')
		{
			whitespace = CodeLine.find("]", codeIndex) + 1;
		}
		currentToken = CodeLine.substr(codeIndex, whitespace - codeIndex);
		if (currentToken.length() == 0)
		{
			codeIndex++;
			continue;
		}

		for (string op : this->NumOperators) //Check for operators
		{
			if (currentToken.find(op) == 0)
			{
				 
				Token* token = new Token(Type::NumOperator, op, indentation, this->line);
				if (op == "*" || op == "/") token->priority = 1;
				this->TokenList.push_back(token);
				codeIndex += op.length();
				identifiedToken = true;
				break;
			}
		}

		for (string op : this->BoolOperators) //Check for operators
		{
			if (currentToken.find(op) == 0)
			{
				Token* token = new Token(Type::BoolOperator, op, indentation, this->line);
				if (op == "and") token->priority = 1;
				this->TokenList.push_back(token);
				codeIndex += op.length();
				identifiedToken = true;
				break;
			}
		}

		for (string op : this->EqualOperators) //Check for operators
		{
			if (currentToken.find(op) == 0)
			{
				Token* token = new Token(Type::EqualOperator, op, indentation, this->line);
				this->TokenList.push_back(token);
				codeIndex += op.length();
				identifiedToken = true;
				break;
			}
		}

		for (string op : this->IteratorOperators) //Check for operators
		{
			if (currentToken.find(op) == 0)
			{
				Token* token = new Token(Type::IteratorOperator, op, indentation, this->line);
				this->TokenList.push_back(token);
				codeIndex += op.length();
				identifiedToken = true;
				break;
			}
		}

		for (string delimiter : this->Delimiters) //Check for delimiters
		{
			if (currentToken.find(delimiter) == 0)
			{
				Token* token = new Token(Type::Delimiter, delimiter, indentation, this->line);
				this->TokenList.push_back(token);
				codeIndex += delimiter.length();
				identifiedToken = true;
				break;
			}
		}

		for (string keyword : this->KeyWords)
		{
			if (currentToken.find(keyword) == 0)
			{
				Token* token = new Token(Type::Keyword, keyword, indentation, this->line);
				this->TokenList.push_back(token);
				codeIndex += keyword.length();
				identifiedToken = true;
				break;
			}
		}

		for (string keyword : this->Branches)
		{
			if (currentToken.find(keyword) == 0)
			{
				Token* token = new Token(Type::Branch, keyword, indentation, this->line);
				this->TokenList.push_back(token);
				codeIndex += keyword.length();
				identifiedToken = true;
				break;
			}
		}
		if (identifiedToken) continue;
		
		for (int i = 1; i < currentToken.length(); i++)
		{
			if (!(isalnum(currentToken[i]) || currentToken[i] == '_' || currentToken[i] == ',' || currentToken[i] == ' ' || currentToken[i] == ']'))
			{
				currentToken = currentToken.substr(0, i);
				break;
			}
		}
		if ((isalpha(currentToken[0]) || currentToken[0] == '_') && (this->TokenList.empty() || this->TokenList.back()->value != "\""))
		{
			
			Token* token = new Token(Type::Identifier, currentToken, indentation, this->line);
			this->TokenList.push_back(token);
			codeIndex += currentToken.length();
			continue;
		}
		else 
		{
			Token* token = new Token(Type::Literal, currentToken, indentation, this->line);
			if (this->TokenList.back()->value == "\"")
				token->literalType = ObjectType::String;
			else if (currentToken == "true" || currentToken == "false")
				token->literalType = ObjectType::Bool;
			else if (currentToken[0] == '[')
				token->literalType = ObjectType::List;
			else
				token->literalType = ObjectType::Int;
			this->TokenList.push_back(token);
			codeIndex += currentToken.length();
			continue;
		}
	}

	Token* token = new Token(Type::EndLine, "\n", indentation, this->line);
	this->TokenList.push_back(token);
}

vector<Token*> Lexer::GetTokenList()
{
	return this->TokenList;
}

void Lexer::ToString()
{
	for (int i = 0; i < this->TokenList.size(); i++)
	{
		Token* currentToken = this->TokenList.at(i);
		if (currentToken->type == Type::NumOperator)
		{
			cout << "NumOperator: " << currentToken->value << endl;
		}
		else if (currentToken->type == Type::BoolOperator)
		{
			cout << "BoolOperator: " << currentToken->value << endl;
		}
		else if (currentToken->type == Type::EqualOperator)
		{
			cout << "EqualOperator: " << currentToken->value << endl;
		}
		else if(currentToken->type == Type::Keyword)
		{
			cout << "Keyword: " << currentToken->value << endl;
		}
		else if (currentToken->type == Type::Literal)
		{
			cout << "Literal: " << currentToken->value << endl;
		}
		else if (currentToken->type == Type::Identifier)
		{
			cout << "Identifier: " << currentToken->value << endl;
		}
		else if (currentToken->type == Type::Delimiter)
		{
			cout << "Delimiter: " << currentToken->value << endl;
		}
		else if (currentToken->type == Type::EndLine)
		{
			cout << "EndLine: " << currentToken->value << endl;
		}
	
	}
}