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

int Parser::parseSingle(stringstream* ss, double* x){
	*ss >> *x;
	cout << *x << "\n";
	return ss->fail();
}

int Parser::parseDuple(stringstream* ss, double* x, double* y){
	*ss >> *x >> *y;
	cout << *x << " " << *y << "\n";
	return ss->fail();
}

int Parser::parseDuple(stringstream* ss, int* x, int* y){
	*ss >> *x >> *y;
	cout << *x << " " << *y << "\n";
	return ss->fail();
}

int Parser::parseTriple(stringstream* ss, double* x, double* y, double* z){
	*ss >> *x >> *y >> *z;
	cout << *x << " " << *y << " " << *z << "\n";
	return ss->fail();
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




