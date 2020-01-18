/*************************Preprocessor Directives********************/
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Stack.h"
#include "Stack.cpp"

/*************************Struct Declarations********************/
struct Parenthesis
{
	char type;
	int x;
	int y;

	Parenthesis(char type = 0, int x = 0, int y = 0)
	{
		this->type = type;
		this->x = x;
		this->y = y;
	}
};

/*************************Function Declarations********************/
std::string GetFileAddress(); 	//Gets the address of the file to be balanced
void OpenFile(std::string fileAddr); //Opens and returns a stream to the given file
void AnalyzeFile(); //Checks the file for unbalanced parenthesis
void FindUnbalancedParenthesis(std::string& line); /*Finds unbalanced parenthesis in
the file*/
void DisplayUnbalancedParenthesis(); /*Prints out the unbalanced parenthesis found*/
void CompileUnbalancedParenthesis(); /*Compiles a list of the unbalanced parenthesis*/

/*************************Global Variables********************/
std::fstream file; //A stream to the file to be balanced
DataStructures::Stack<Parenthesis> parenthesisPos[3]; /*A stack containing the found
parenthesis and their positions*/
std::vector<Parenthesis> unbalancedParenthesis; /*A vector containing the unbalanced
parenthesis*/
char parenthesisTypes[] = { '{', '}', '(', ')', '[', ']' };

/*************************Functions********************/
int main()
{
	//Getting the file address
	std::string fileAddr = GetFileAddress();

	//Creating a stream to the file
	OpenFile(fileAddr);

	//Checking if the file has any unbalanced parenthesis
	AnalyzeFile();

	//Closing the file stream
	file.close();
}

std::string GetFileAddress()
{	
	std::string fileAddr; //The address of the file

	std::cout << "Enter file address: ";
	std::getline(std::cin, fileAddr);

	return fileAddr;
}

void OpenFile(std::string fileAddr)
{
	//Opening the file
	file.open(fileAddr, std::ios::in);

	//Checking if the file has opened successfully
	if (!file.is_open())
	{
		std::cout << "Unable to open file. Try Again!";
		exit(1);
	}
}

void AnalyzeFile()
{
	//Reading the file and tracking parenthesis
	while (!file.eof())
	{
		std::string line; //A line from the file
		std::getline(file, line); //Reading a file line

		FindUnbalancedParenthesis(line);
	}

	//Checking if any unbalanced parenthesis were found
	DisplayUnbalancedParenthesis();
}

void FindUnbalancedParenthesis(std::string& line)
{
	static int lineCtr = 0;

	for (int a = 0; a < line.length(); ++a)
	{
		switch (line[a])
		{
		case '{': parenthesisPos[0].Push(Parenthesis(0, lineCtr, a)); break;
		case '(': parenthesisPos[1].Push(Parenthesis(2, lineCtr, a)); break;
		case '[': parenthesisPos[2].Push(Parenthesis(4, lineCtr, a)); break;
		case '}': parenthesisPos[0].Empty() ? unbalancedParenthesis.push_back(Parenthesis(1, lineCtr, a)) : parenthesisPos[0].Pop();
			break;
		case ')': parenthesisPos[1].Empty() ? unbalancedParenthesis.push_back(Parenthesis(3, lineCtr, a)) : parenthesisPos[1].Pop();
			break;
		case ']': parenthesisPos[2].Empty() ? unbalancedParenthesis.push_back(Parenthesis(5, lineCtr, a)) : parenthesisPos[2].Pop();
			break;
		}
	}

	++lineCtr;
}

void DisplayUnbalancedParenthesis()
{
	CompileUnbalancedParenthesis();
	
	//Checking if any unbalanced parenthesis were found
	if (unbalancedParenthesis.size() == 0)
	{
		std::cout << "No unbalanced parenthesis found\n";
	}
	else //Priniting the found unbalanced parenthesis
	{
		for (Parenthesis prn : unbalancedParenthesis)
		{
			std::cout << "Unbalanced Parenthesis '" << parenthesisTypes[prn.type] <<
				"' found on line " << prn.x << " at position " << prn.y << "\n";
		}
	}
}

void CompileUnbalancedParenthesis()
{
	for (char a = 0; a < 3; ++a)
	{
		while (parenthesisPos[a].Size() != 0)
		{
			unbalancedParenthesis.push_back(parenthesisPos[a].Top());
			parenthesisPos[a].Pop();
		}
	}
}