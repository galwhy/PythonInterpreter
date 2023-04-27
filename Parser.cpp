#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include "AbstractSyntaxTree.h"
#include "Token.h"
#include "Parser.h"
#include "Node.h"

using namespace std;

Parser::Parser()
{
	this->ConditionOperators = { "==", "!=", ">=", "<=", ">", "<" };
}

void Parser::Parse(vector<Token*> TokenList)
{
	int lastIndentation = 0;
	int operatorCount = 0;
	bool conditionCheck = false;
	bool numericCheck = false;
	bool parenthesesCheck = false;

	stack<Token*>* operatorStack = new stack<Token*>();
	stack<Token*>* operatorOutputStack = new stack<Token*>();
	stack<Token*>* numStack = new stack<Token*>();
	stack<Token*>* outputStack = new stack<Token*>();

	stack<Token*>* boolStack = new stack<Token*>();
	stack<Token*>* boolOutputStack = new stack<Token*>();
	stack<Node*>* conditionStack = new stack<Node*>();
	vector<Node*>* conditionOutputStack = new vector<Node*>();
	

	Node* currentTree = this->syntaxTree.Root;

	for (int i = 0; i < TokenList.size(); i++)
	{
		Token* currentToken = TokenList.at(i);
		if (lastIndentation > currentToken->indentation)
		{
			for (int j = currentToken->indentation; j < lastIndentation; j++)
			{
				currentTree = currentTree->Parent;
			}
		}

		if ((!numericCheck || currentToken->type == Type::EndLine) && !numStack->empty())
		{
			numericCheck = false;
			parenthesesCheck = false;
			Node* currentNumricTree = currentTree;
			if (conditionCheck && !currentTree->Children->empty())
			{
				currentNumricTree = currentTree->GetLastChild();
				currentTree->Children->pop_back();
				conditionStack->push(currentNumricTree);
			}
			else if (conditionCheck && !conditionStack->empty())
			{
				currentNumricTree = conditionStack->top();
			}
			else if (conditionCheck && !conditionOutputStack->empty())
			{
				currentNumricTree = conditionOutputStack->front();
			}
			else if (!currentTree->Children->empty())
				currentNumricTree = currentTree->GetLastChild();


			while (!operatorStack->empty())
			{
				if (operatorStack->top()->value != "(")
				{
					operatorOutputStack->push(operatorStack->top());
				}
				operatorStack->pop();
			}
			while (!numStack->empty())
			{
				outputStack->push(numStack->top());
				numStack->pop();
			}

			if (!operatorOutputStack->empty())
			{
				if (operatorOutputStack->top()->value == "[]")
				{
					IndexNode* newTree = new IndexNode(operatorOutputStack->top(), currentTree);
					operatorOutputStack->pop();
					currentNumricTree->InsertChild(newTree);
					currentNumricTree = newTree;
				}
				else
				{
					OperatorNode* newTree = new OperatorNode(operatorOutputStack->top(), currentNumricTree);
					operatorOutputStack->pop();
					currentNumricTree->InsertChild(newTree);
					currentNumricTree = newTree;
				}
			}
			

			while (!outputStack->empty())
			{
				if (!operatorOutputStack->empty())
				{
					Node* newTree1;
					if (operatorOutputStack->top()->value == "[]")
					{
						newTree1 = new IndexNode(operatorOutputStack->top(), currentTree);
						operatorOutputStack->pop();
						currentNumricTree->InsertChild(newTree1);
					}
					else
					{
						newTree1 = new OperatorNode(operatorOutputStack->top(), currentNumricTree);
						operatorOutputStack->pop();
						currentNumricTree->InsertChild(newTree1);
					}
					

					Node* newTree2 = new Node(outputStack->top(), currentNumricTree);
					outputStack->pop();
					currentNumricTree->InsertChild(newTree2);

					currentNumricTree = newTree1;
				}
				else
				{
					Node* newTree1 = new Node(outputStack->top(), currentNumricTree);
					outputStack->pop();
					currentNumricTree->InsertChild(newTree1);
				}
			}
		}
		if ((!conditionCheck || currentToken->type == Type::EndLine) && !conditionStack->empty())
		{
			conditionCheck = false;
			Node* currentBoolTree = currentTree;
			
			if (!currentTree->Children->empty())
				currentBoolTree = currentTree->GetLastChild();

			while (!boolStack->empty())
			{
				if (boolStack->top()->value != "(")
				{
					boolOutputStack->push(boolStack->top());

				}
				boolStack->pop();
			}
			while (!conditionStack->empty())
			{
				conditionOutputStack->push_back(conditionStack->top());
				conditionStack->pop();
			}

			if (!boolOutputStack->empty())
			{
				BoolNode* newTree = new BoolNode(boolOutputStack->top(), currentBoolTree);
				boolOutputStack->pop();
				currentBoolTree->InsertChild(newTree);
				currentBoolTree = newTree;
			}


			while (!conditionOutputStack->empty())
			{
				if (!boolOutputStack->empty())
				{
					BoolNode* newTree1 = new BoolNode(boolOutputStack->top(), currentBoolTree);
					boolOutputStack->pop();
					currentBoolTree->InsertChild(newTree1);

					Node* newTree2 = conditionOutputStack->back();
					conditionOutputStack->pop_back();
					currentBoolTree->InsertChild(newTree2);

					currentBoolTree = newTree1;
				}
				else
				{
					Node* newTree1 = conditionOutputStack->back();
					conditionOutputStack->pop_back();
					currentBoolTree->InsertChild(newTree1);
				}
			}
		}

		if (currentToken->type == Type::Keyword)
		{
			if (currentToken->value == "return")
			{
				ReturnNode* newTree = new ReturnNode(currentToken, currentTree);
				currentTree->InsertChild(newTree);
			}
			else
			{
				GlobalNode* newTree = new GlobalNode(currentToken, currentTree);
				currentTree->InsertChild(newTree);
			}
			numericCheck = false;
			
		}
		else if (currentToken->type == Type::Branch)
		{
			numericCheck = false;
			BranchNode* newTree = new BranchNode(currentToken, currentTree);
			currentTree->InsertChild(newTree);
			currentTree = newTree;
			conditionCheck = true;
		}
		else if (currentToken->type == Type::Identifier)
		{
			numericCheck = true;
			numStack->push(currentToken);
			/*if (TokenList->at(i + 1)->type == Type::NumOperator)
			{
				Token* operatorToken = TokenList->at(i + 1);
				AbstractSyntaxTree* newTree = new AbstractSyntaxTree(*operatorToken, currentTree);
				currentTree->InsertChild(newTree);
				currentTree = newTree;

				newTree = new AbstractSyntaxTree(*currentToken, currentTree);
				currentTree->InsertChild(newTree);
			}
			else
			{
				AbstractSyntaxTree* newTree = new AbstractSyntaxTree(*currentToken, currentTree);
				currentTree->InsertChild(newTree);
				if (TokenList->at(i + 1)->type != Type::Delimiter)
				{
					for (int _ = 0; _ < operatorCount; _++)
						currentTree = currentTree->Parent;
					operatorCount = 0;
				}	
			}*/
		}
		else if (currentToken->type == Type::Literal)
		{
			numericCheck = true;
			numStack->push(currentToken);
			/*AbstractSyntaxTree* newTree = new AbstractSyntaxTree(currentToken, currentTree);
			currentTree->InsertChild(newTree);
			if (TokenList->at(i + 1)->type != Type::Delimiter)
			{
				for (int _ = 0; _ < operatorCount; _++)
					currentTree = currentTree->Parent;
				operatorCount = 0;
			}*/
		}
		else if (currentToken->type == Type::IteratorOperator)
		{
			numericCheck = false;
			if (currentToken->value == "in")
			{
				IteratorNode* newTree = new IteratorNode(currentToken, currentTree);
				currentTree->InsertChild(newTree);
			}
		}
		else if (currentToken->type == Type::BoolOperator)
		{
			conditionCheck = true;
			numericCheck = false;
			if (!boolStack->empty() && boolStack->top()->priority > currentToken->priority)
			{
				boolOutputStack->push(boolStack->top());
				boolStack->pop();

				conditionOutputStack->push_back(conditionStack->top());
				conditionStack->pop();
				conditionOutputStack->push_back(conditionStack->top());
				conditionStack->pop();
			}
			boolStack->push(currentToken);
		}
		else if (currentToken->type == Type::NumOperator)
		{
			numericCheck = true;
			if (!operatorStack->empty() && operatorStack->top()->priority > currentToken->priority)
			{
				operatorOutputStack->push(operatorStack->top());
				operatorStack->pop();

				outputStack->push(numStack->top());
				numStack->pop();
				outputStack->push(numStack->top());
				numStack->pop();
			}
			operatorStack->push(currentToken);
		}
		else if (currentToken->type == Type::EqualOperator)
		{
			numericCheck = false;
			if (currentToken->value == "=")
			{
				EqualNode* newTree = new EqualNode(currentToken, currentTree);
				currentTree->InsertChild(newTree);
			}
			else
			{
				CompareNode* newTree = new CompareNode(currentToken, currentTree);
				currentTree->InsertChild(newTree);
			}
			//operatorCount++;
		}
		else if (currentToken->type == Type::Delimiter)
		{
			if (currentToken->value == "(")
			{
				parenthesesCheck = true;
				operatorStack->push(currentToken);
				boolStack->push(currentToken);
			}
			else if (currentToken->value == ")" && parenthesesCheck)
			{
				Token* currentOperator = operatorStack->top();
				operatorStack->pop();
				while (currentOperator->value != "(")
				{
					operatorOutputStack->push(currentOperator);
					outputStack->push(numStack->top());
					numStack->pop();
					outputStack->push(numStack->top());
					numStack->pop();

					currentOperator = operatorStack->top();
					operatorStack->pop();
				}
			}
			else if (currentToken->value == ")")
			{
				Token* currentBool = boolStack->top();
				boolStack->pop();
				while (currentBool->value != "(")
				{
					boolOutputStack->push(currentBool);
					conditionOutputStack->push_back(conditionStack->top());
					conditionStack->pop();
					conditionOutputStack->push_back(conditionStack->top());
					conditionStack->pop();

					currentBool = boolStack->top();
					boolStack->pop();
				}
			}
			else if (currentToken->value == ":")
			{
				numericCheck = false;
				//conditionCheck = false;
			}
			/*if (conditionCheck && currentToken->value == ":")
			{
				cout << "line " << currentToken->line << ": Syntax Error";
				break;
			}
			if (currentToken->value == ":")
			{
				if (currentTree->Value->value != "else")
					currentTree = currentTree->Parent;
				operatorCount = 0;
			}
			else if (currentToken->value == ")")
			{
				currentTree = currentTree->Parent;
			}*/
		}
		lastIndentation = currentToken->indentation;
	}
	if (syntaxTree.Root->GetLastChild()->Value->value != "return")
	{
		Token* currentToken = new Token(Type::Keyword, "return");
		ReturnNode* newTree = new ReturnNode(currentToken, currentTree);
		syntaxTree.Root->InsertChild(newTree);
	}
}

int Parser::CheckSyntax(Node* node)
{
	vector<Node*>* treeList = node->Children;
	if (node != nullptr)
	{
		if (node->Value != NULL)
		{
			if (node->Value->type == Type::NumOperator || node->Value->type == Type::BoolOperator || node->Value->type == Type::EqualOperator)
			{
				if (treeList->size() != 2)
				{
					throw ParserException(node->Value->line);
				}
			}
		}
		for (Node* Tree : *treeList)
		{
			if (CheckSyntax(Tree) == 1)
				return 1;
		}
	}
}

void Parser::CheckSyntax()
{
	CheckSyntax(this->syntaxTree.Root);
}

AbstractSyntaxTree* Parser::GetSyntaxTree()
{
	return &this->syntaxTree;
}

void Parser::ToString(const std::string& prefix, Node* node)
{
	vector<Node*>* treeList = node->Children;
	if (node != nullptr)
	{
		std::cout << prefix;

		// print the value of the node
		if (node->Value != nullptr)
			std::cout << node->Value->value << std::endl;

		// enter the next tree level - left to right branch
		for (Node* Tree : *treeList)
		{
			ToString(prefix + ("     "), Tree);
		}
	}
}

void Parser::ToString()
{
	ToString("", this->syntaxTree.Root);
}


ParserException::ParserException(int line)
{
	stringstream ss;
	ss << "Syntax Error: line " << line;
	msg = ss.str();
}

const char* ParserException::what() const noexcept
{
	return msg.c_str();
}