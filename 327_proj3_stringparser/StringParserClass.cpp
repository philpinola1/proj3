/*
 * StringParserClass.h
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <vector>
#include <string>
#include <string.h>
#include <iostream>

#include "../327_proj3_test/includes/constants.h"
#include "../327_proj3_test/includes/StringParserClass.h"

using namespace KP_StringParserClass;


		//dont forget to initialize member variables
		StringParserClass::StringParserClass(void) {
			this->pEndTag = 0;
			this->pStartTag = 0;
			this->areTagsSet = false;
		}

		//call cleanup to release any allocated memory
		StringParserClass::~StringParserClass(void) {
		}

		//these are the start tag and the end tags that we want to find,
		//presumably the data of interest is between them, please make a
		//COPY of what pStartTag and pEndTag point to.  In other words
		//DO NOT SET pStartTag = pStart
		//returns:
		//SUCCESS
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		int StringParserClass::setTags(const char *pStart, const char *pEnd) {

			if (!pStart || !pEnd) {
				return ERROR_TAGS_NULL;
			}

			pStartTag = 0;
			int startlen = strlen(pStart) +1;
			pStartTag = new char [startlen];

			if (pStart){
				memset( pStartTag, 0, (startlen)* sizeof(char));
				strncpy(pStartTag, pStart, startlen);
			}
			else {
				return ERROR_TAGS_NULL;
			}

			pEndTag = 0;
			int endlen = strlen(pEnd) + 1;
			pEndTag = new char [endlen];

			if (pEnd){
				memset (pEndTag, 0, (endlen)* sizeof(char));
				strncpy(pEndTag, pEnd, endlen);
			}
			else {
				return ERROR_TAGS_NULL;
			}

			areTagsSet = true;
			return SUCCESS;
		}


		void StringParserClass::cleanup() {

		}

		//Searches a string starting at pStart for pTagToLookFor
		//returns:
		//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
		//FAIL did not find pTagToLookFor and pEnd points to 0
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {

			if (!pStart || !pEnd) {
				return ERROR_TAGS_NULL;
			}

			const int looklen = strlen(pTagToLookFor);
			const int slen = strlen(pStart);
			//const int eLen = strlen(pEnd);

			std::cout << slen;

			for (int i = 0; i < slen; i++) {

				if (*(pStart + i) == pTagToLookFor[0]) {
					if (strncmp((pStart+i), pTagToLookFor, looklen) == 0) {
						return SUCCESS;
					}
				}
			}

			pEnd = 0;
			return FAIL;

		}

		//First clears myVector
		//going to search thru pDataToSearchThru, looking for info bracketed by
		//pStartTag and pEndTag, will add that data to myStrings
		//returns
		//SUCCESS  finished searching for data between tags, results in myStrings (0 or more entries)
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		//ERROR_DATA_NULL pDataToSearchThru is null
		int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector) {
			myVector.clear();

			if (!pStartTag || !pEndTag) {
				areTagsSet = false;
				return ERROR_TAGS_NULL;
			}

			if (!pDataToSearchThru) {
				return ERROR_DATA_NULL;
			}

			int sLen = strlen(pStartTag);
			int eLen = strlen(pEndTag);

//			char * duh = pStartTag + sLen;
//			char * duh2 = pEndTag + eLen;

			while (pDataToSearchThru) {

//				int find1 = StringParserClass::findTag(pStartTag, pDataToSearchThru, duh);
//				int find2 = StringParserClass::findTag(pEndTag, pDataToSearchThru, duh2);

				//std::cout << "find1: " << find1 << std::endl;
				//std::cout << "find2: " << find2 << std::endl;

//				if (find1 == FAIL || find2 == FAIL) {
//					return ERROR_TAGS_NULL;
//				}
//
//				else if (find1 == ERROR_TAGS_NULL || find2 == ERROR_TAGS_NULL) {
//					return ERROR_TAGS_NULL;
//				}


				//So I know I should implemented findTags and then call it here for both pStartTag & pEndTag
				//but, this function encompasses (most) of the functionalliy of findTags below vvv
				//couldn't figure out how to find when there is no end tag (I know, I should have done used findTags to catch this ocurance)
				bool flag1 = true;

				char *Itr1 = pDataToSearchThru; //re
				char *Itr2 = 0;

				//moves pStartTag to the addr of first char of start tag
				while (flag1) {

					if (*Itr1 == pStartTag[0]) {

						if (strncmp(Itr1, pStartTag, sLen) == 0) {
							flag1 = false;
							Itr1 = Itr1 + sLen; //move pointer to last char of tag
						}
						else {
							Itr1++;
						}
					}
					else if (*Itr1 == '\0') {
						flag1 = false;
					}
					else {
						Itr1++;
					}
				}

				Itr2 = Itr1;
				bool flag2 = true;

				//moves pEndTag to the addr of first char of end tag
				while (flag2) {

					if (*Itr2 == pEndTag[0]) {

						if (strncmp(Itr2, pEndTag, eLen) == 0) {
							flag2 = false;
						}
						else {
							Itr2++;
						}

					}
					else if (*Itr2 == '\0') {
						flag2 = false;
					}
					else {
						Itr2++;
					}
				}

				//spit the chars between Itr1&2 to a std::string
				//spit that std::string into vector
				std::string toVect = "";
				while (Itr1 != Itr2) {
					toVect = toVect + *Itr1;
					Itr1++;
				}
				if (toVect.length() > 0) {
					myVector.push_back(toVect);
					Itr1 = 0;
					pDataToSearchThru = Itr2 + eLen; //used to help break out of outer-most whileloop
					Itr2 = 0;
				}
				else {
					pDataToSearchThru = 0;
				}

			}
			return SUCCESS;
		}

