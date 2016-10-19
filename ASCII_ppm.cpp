#include "ASCII_ppm.h"

#include<iostream>
#include<fstream>
#include <math.h>
#include <sstream>
#include <exception>


using namespace std;


/* Utility functions for parsing ASCII text files.
 * 
*/
namespace ParserUtil
{
	/* Reads a file and returns its lines as string
	*/
	string readFile(string name){
		ifstream txtStream;
		txtStream.open(name);
		string line;
		string txt = "";

		if (txtStream.is_open()) {
			while (getline(txtStream, line)) {
				txt += line + "\n";
			}
			txtStream.close();
		}
		else {
			throw "file not found";
		}

		// keep line formatting from file
		if (txt[txt.length() - 1] != '\n'){
			txt = txt + "\n";
		}

		return txt;
	}

	/* Converts a double to string version of a floored int. ** 255.32 -> "255" **
	*/
	string itos(double input){
		int result = (int) floor(input);
		stringstream s;
		s << result;
		return s.str();
	}

	/* Converts a string into a positive integer. Return -1 when non-integers are given.
	*/
	int stoi(string input){
		if (!input.compare("")){
			cout << "empty input";
			return -1;
		}
		int result = 0;
		int nextDigit = 0;
		int len = input.length();
		for (int i = 0; i < len; i++){
			switch (input[i]){
				case '0' :
					nextDigit = 0;
					break;
				case '1' : 
					nextDigit = 1;
					break;
				case '2':
					nextDigit = 2;
					break;
				case '3':
					nextDigit = 3;
					break;
				case '4':
					nextDigit = 4;
					break;
				case '5':
					nextDigit = 5;
					break;
				case '6':
					nextDigit = 6;
					break;
				case '7':
					nextDigit = 7;
					break;
				case '8':
					nextDigit = 8;
					break;
				case '9':
					nextDigit = 9;
					break;
				default:
					cout << "non-numeric character " << input[i] << "\n";
					return -1;
			}
			result = result * 10 + nextDigit;
		}
		return result;
	}

	/* Tokenizes a string on a delimiter. ! pre-allocate 'tokens' !
	 * ** Currently unused in favor of splitList. **
	*/
	void split(string delim, string inputString, string* tokens){
		int split = 0, pos = 0, i = 0;
		while (split > -1 && pos < inputString.length()){
			split = inputString.find(delim, pos);
			tokens[i] = inputString.substr(pos, split - pos);
			pos = split + 1;
			i++;
		}
	}

	/* Given a list of delimiters and a string to parse, fill a flat array of tokens
	 * Array elements appear in same order as in string.
	*/
	// TODO: Revisit. Currently does much more work than it needs to.
	void splitList(string* delims, int delimSize, string inputString, string* tokens){
		int split = 0, pos = 0, i = 0, len = inputString.length();
		int newSplit;
		while (split > -1 && pos < len && i < 20){
			split = len;
			//TODO: can split into a map/min function if possible
			for (int j = 0; j < delimSize; j++){
				if ((newSplit = inputString.find(delims[j], pos)) >= 0 && newSplit < split){
					split = newSplit;
				}
			}
			//end TODO
			tokens[i] = inputString.substr(pos, split - pos);
			pos = split + 1;
			i++;
		}
	}
}


//public
ASCII_ppm::ASCII_ppm()
{
}

void ASCII_ppm::init(string file){
	
	string tokens[4];
	ParserUtil::split(".", file, tokens);

	fileName = tokens[0];
	openTxt(file);
	parseA0();
}

string ASCII_ppm::getHeader(){
	return header;
}
string ASCII_ppm::getImage(){
	return image;
}

int ASCII_ppm::savePpm(){
	ofstream saveFile(fileName + ".ppm");
	saveFile << header << image;
	saveFile.close();
	return 1;
}

void ASCII_ppm::generateSolid(string r, string g, string b){
	image = "";
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			image += r + " " + g + " " + b + " ";
		}
	}
}

void ASCII_ppm::generateGradient(int rTop, int gTop, int bTop, int rBottom, int gBottom, int bBottom){
	image = "";
	
	rTop = makeValid(rTop);
	gTop = makeValid(gTop);
	bTop = makeValid(bTop);
	rBottom = makeValid(rBottom);
	gBottom = makeValid(gBottom);
	bBottom = makeValid(bBottom);
	
	double rStep = gradientStep(rTop, rBottom, height-1);
	double gStep = gradientStep(gTop, gBottom, height-1);
	double bStep = gradientStep(bTop, bBottom, height-1);
	
	for (int i = 0; i < height; i++){
		double rIter = rTop - rStep*i;
		double gIter = gTop - gStep*i;
		double bIter = bTop - bStep*i;

		for (int j = 0; j < width; j++){
			image += ParserUtil::itos(rIter) + " " + ParserUtil::itos(gIter) + " " + ParserUtil::itos(bIter) + " ";
		}
	}
}

int ASCII_ppm::makeValid(int value){
	if (value > maxVal){
		return maxVal;
	}
	else if (value < 0){
		return 0;
	}
	else {
		return value;
	}
}


//private
void ASCII_ppm::openTxt(string name){
	header = ParserUtil::readFile(name);
}

// parseHeader is intended to parse the header info off of any ppm file.
void ASCII_ppm::parseHeader(){
	string tokens[64];
	parseWhiteSpace(tokens);

	for (int i = 0; i < 4; i++){
		if (tokens[i] == ""){
			cout << "txt file format is: 'imsize	<width> <height>'";

		}
	}

	type = tokens[0];
	width = ParserUtil::stoi(tokens[1]);
	height = ParserUtil::stoi(tokens[2]);
	maxVal = ParserUtil::stoi(tokens[3]);

	if (type.compare("P3") && type.compare("p3")){
		cout << "improper ppm type.\n";
	}
	if (width < 0 || height < 0 || maxVal < 0){
		cout << "non-zero values required.\n";
	}
	
	header = tokens[0] + " " + tokens[1] + " " + tokens[2] + " " + tokens[3] + "\n";
}

void ASCII_ppm::parseA0(){
	string tokens[16];
	parseWhiteSpace(tokens);

	for (int i = 0; i < 3; i++){
		if (tokens[i] == ""){
			throw invalid_argument("Specification not met.");
		}
	}
	type = "P3";
	width = ParserUtil::stoi(tokens[1]);
	height = ParserUtil::stoi(tokens[2]);
	maxVal = 255;
	if (tokens[0].compare("imsize") || width < 0 || height < 0){
		throw invalid_argument("Specification not met.");
	}

	header = type + "\n" + tokens[1] + " " + tokens[2] + "\n" + "255\n";
}

void ASCII_ppm::parseWhiteSpace(string* tokens){
	string delims[4];
	delims[0] = " ";
	delims[1] = "\n";
	delims[2] = "\t";
	delims[3] = "\r";
	ParserUtil::splitList(delims, 4, header, tokens);
}

double ASCII_ppm::gradientStep(int start, int end, double distance){
	double step = ((double)start - (double)end) / distance;
	return step;
}

/*
int main()
{
	ASCII_ppm ppm;
	string fileInput;

	int go = 1;
	while (go){
		try{
			cout << "Enter input text file name: ";
			cin >> fileInput;
			if (!fileInput.compare("quit")){
				return 0;
			}
			ppm.init(fileInput);
			go = 0;
		}
		catch (invalid_argument){
			cout << "Text file specification not met. Format: 'imsize <(int) width> <(int) height>'";
			return -1;
		}
		catch (...){
			cout << "File not found.\n\n";
		}
	}
	
	cout << "\nThis program will create a simple top-to-bottom gradient\n"
		<< "Enter 6 r g b integers (0-255) separated by whitespace: ";
	string r1, g1, b1, r2, g2, b2;
	string tokens[6];
	cin >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
	//invalid values will be sent to black
	ppm.generateGradient(ParserUtil::stoi(r1), ParserUtil::stoi(g1), ParserUtil::stoi(b1), ParserUtil::stoi(r2), ParserUtil::stoi(g2), ParserUtil::stoi(b2));
	ppm.savePpm();
	
	return 0;
}
*/