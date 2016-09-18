#include "Parser.h"
#include <string>
#include <vector>
#include <fstream>

#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser(string source)
{
	sourceText = source;
}

Parser::~Parser()
{
}

string Parser::getFileStripped(){
	istringstream ss(sourceText);
	string file = "";
	getline(ss, file, '.');
	cout << file;
	return file;
}

void Parser::setSource(string newSource){
	sourceText = newSource;
}

int Parser::parseFile(){
	return 0;
}




