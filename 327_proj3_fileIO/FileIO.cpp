/*
 * FileReader.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */
#include <iostream>
#include <fstream>
#include "../327_proj3_test/includes/FileIO.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;


	//trys to open filename, and return its contents in contents
	//it will strip out only \n's (char return\line feed)
	//returns:
	//SUCCESS all worked, contents string contains all in the file
	//COULD_NOT_OPEN_FILE_TO_READ contents string is cleared
int KP_FileIO::getFileContents(const std::string &filename, std::string &contents) {

	ifstream infile;
    infile.open(filename.c_str());

	if (infile.is_open()) {

		while (infile.is_open()) {

			while (!infile.eof()) {
				char line [200];
				char *p = line;
				infile.getline(p, 200);
				std::string str(line);
				contents = contents + line;
				}
			infile.close();
			return SUCCESS;
			}
		}
	else{
		return COULD_NOT_OPEN_FILE_TO_READ;
	}
}


	//trys to open filename, and serialize  myEntryVector contents to it
	//returns:
	//SUCCESS all worked, filename contains myEntryVector strings
	//COULD_NOT_OPEN_FILE_TO_WRITE


int KP_FileIO::writeVectortoFile(const std::string filename,std::vector<std::string> &myEntryVector){

	ofstream outfile;
	outfile.open(filename.c_str());
	vector<std::string>::iterator itr;

	if (outfile.is_open()) {
		for (itr = myEntryVector.begin(); itr != myEntryVector.end(); itr++) {
			outfile << *itr << endl;
		}
		outfile.close();
	}
	else {
		return COULD_NOT_OPEN_FILE_TO_WRITE;
	}
	return SUCCESS;
}
