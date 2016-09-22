#include "Parser.h"
#include <string>
#include <vector>
#include <fstream>

#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser()
{
}

Parser::~Parser()
{
}

string Parser::getFileStripped(string sourceText){
	istringstream ss(sourceText);
	string file = "";
	getline(ss, file, '.');
	cout << file;
	return file;
}

int Parser::parseFile(){
	return 0;
}




