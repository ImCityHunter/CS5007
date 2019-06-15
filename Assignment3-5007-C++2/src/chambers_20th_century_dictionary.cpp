/*
 * chambers_20th_century_dictionary.cpp
 *
 * This program relies on the availability of the 'curl' utility
 * for reading input from a URL. Curl is available with MacOS and
 * most Linux distros. Curl is also available under CygWin. See
 * http://www.oracle.com/webfolder/technetwork/tutorials/obe/cloud/
 * 	objectstorage/installing_cURL/installing_cURL_on_Cygwin_on_Windows.html
 * for instructions. There are also a number of curl ports
 * available on Windows. See https://curl.haxx.se/download.html.
 *
 * @since 2017-06-05
 * @author philip gust
 */


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <iterator>

using namespace std;

/**
 * Define Dictionary as a map of word to definition strings
 */
typedef map<string,pair<long,size_t>> Dictionary;

//long is ftell, size_t position
typedef pair<long,size_t> wordPair;



/**
 *
 * Given a tempfile and definition, write the definition onto the file
 * @param tmpFile
 * @param definition
 *
 * @return return a pair given by the definition
 */
pair<long,size_t>* buildFile(FILE *tmpFile, string definition){

	//base case
	if(tmpFile==NULL) {
		printf("\n Error: File cannot be found\n");
	}

	//get the last pos of the file
	long current_pos = ftell(tmpFile);
	wordPair *newPair = new wordPair(current_pos,definition.length()+1);

	//write the definition onto the file
	fwrite (definition.c_str(),sizeof(char), newPair->second, tmpFile);

	return newPair;
}


/**
 * Use a given file and wordPair(info), and return the corresponding definition
 * @param wordPair
 * @param tmpFile
 * @return defintion of the word
 */
string returnDefinition(pair<long,size_t> wordPair, FILE *tmpFile){

	if(tmpFile==NULL){
		printf("\n Error: File cannot be found\n");
	}
	//start pos of the definition
	long start = wordPair.first;

	//length of the definition
	size_t length = wordPair.second;

	//set the pointer to a position at the file
	rewind(tmpFile);
	int check = fseek(tmpFile,start,SEEK_SET);

	if(check!=0){
		printf("\n Error: index or call function error\n");
		return "ERROR";
	}


	char *read = (char*) malloc(sizeof(char)*wordPair.second);
	fread(read,sizeof(char),length,tmpFile);

	return string(read);
}
/**
 * Normalize a "\r\n" newline sequence to "\n".
 *
 * @param str the input string to be normaized
 * @return the new length of the input string
 */
static int normalizeEoln(char* str) {
	char* eoln = strstr(str, "\r\n");
	if (eoln != (char*)NULL) {
		strcpy(eoln++, "\n");
	}
	return eoln-str;
}

/**
 * Read the definition into the defStr buffer up to defSize characters.
 * Subsequent characters are ignored.
 *
 * @param file the input File
 * @param defStr the input string for the definition with initial text
 * @return true of the definition was read, false if there was an error
 */
static bool readDefinition(FILE* file, string& defStr) {
	bool status;
	char line[256];

    while ((status = (fgets(line, sizeof(line), file) != NULL))) {
    	normalizeEoln(line);

    	// definition ends with empty line
    	if (line[0] == '\n') {
        	break;
        }
    	defStr.append(line);
    }
    return status;
}

/**
 * Read definitions from input stream, starting with the firstWord
 * and ending with the lastWord in the dictionary and build a HashMap
 * with the words and their definitions.
 *
 * Chambers 20th Century Dictionary entries are of the form:
 *
 * SAKE, sak'e, _n._ a Japanese fermented liquor made from rice: a generic
 * name for all spirituous liquors.\r\n
 *
 * The first line has the defined word followed by a comma. Definitions can
 * have multiple lines. Entries are separated by an empty line. Input Lines
 * are terminated by the newline sequence "\r\n" which is replace by '\n'
 * in the tree.
 *
 * @param file the input FILE
 * @param firstWord the first word whose definition is added to the map
 * @param lastWord the last word whose definition is added to the map
 * @return a map with the words and definitions as entries
 */
pair<Dictionary*, FILE*> readChambers_20th_CenturyDictionary(
	FILE* file, string const& firstWord, string const& lastWord) {

	FILE  *tempFile =tmpfile();
	Dictionary* dict = new Dictionary();

	// line buffer
    char line[256];

    // find line with first word to process
	int firstLen = firstWord.length();
	bool found = false;
    while (!found && fgets(line, sizeof(line), file)) {
    	// found if line begins with first word followed by a ', '
        if (firstWord.compare(0, firstLen, line, 0, firstLen) == 0) {
			// definition valid if it begins with word followed by ", "
        	found = (strncmp(line+firstLen, ", ", 2) == 0);
        }
    }

    if (found) {
		do {
			// get definition of current word
			normalizeEoln(line);
			string defStr = line;
			if (!readDefinition(file, defStr)) {
				break;
			}

			// definition valid if it begins with word followed by ", "
			size_t wordLen = defStr.find(", ");
			if (wordLen != string::npos) {
				// extract the word being defined
				string word = defStr.substr(0, wordLen);
				string def = defStr.substr(wordLen+2);  //skip over ", "

				//make new pair, then insert
				wordPair newPair = *buildFile(tempFile,def);
				dict->insert(make_pair(word,newPair));

				// done if just processed last word
				found = (word.compare(lastWord) == 0);
			}

		} while (!found && fgets(line, sizeof(line), file));
    }

    return make_pair(dict,tempFile);
}

/**
 * Test building a map from entries in Chambers's Twentieth Century Dictionary
 * (part 4 of 4: S-Z and supplements) hosted by Project Gutenberg at
 * http://www.gutenberg.org/cache/epub/38700/pg38700.txt.
 */
void testChambers_20th_CenturyDictionary(void) {
	// read piped output of curl
	// see http://stackoverflow.com/questions/26648857/can-fopen-be-used-to-open-the-url
    cout << endl << "Opening Chambers's Twentieth Century Dictionary (part 4 of 4: S-Z and supplements)" << endl;
	FILE* file = popen("curl -s 'http://www.gutenberg.org/cache/epub/38700/pg38700.txt'", "r");
	if (file == (FILE*)NULL) {
		cout << "...Error opening dictionary" << endl;
		return;
    }

	const string firstWord = "SAB";    // first definition to load
	const string lastWord = "SYZYGY";  // last definition to load
	cout << "...Loading definitions from " << firstWord << " to " << lastWord << endl;

	pair<Dictionary*, FILE*> readChamb = readChambers_20th_CenturyDictionary(file, firstWord, lastWord);

	//tempFile is opened in readChamber, shall be closed at the end of this function
	Dictionary* dict = readChamb.first;
	FILE *tempFile = readChamb.second;


	int nEntries = dict->size();
	cout << "...Loaded " << nEntries << " definitions" << endl;

	string cmd;
	const string cmdChars = "=?#";  // command characters
	do {
		if (cmd.compare("quit") == 0) {
			cout << "Done." << endl;
			break;
		} else if (cmdChars.find(cmd[0]) != string::npos) { // process command
			if (cmd.back() == '*') { // process wildcard command
				// all matching words
				const size_t wordLen = cmd.size()-2;
				const string word = cmd.substr(1, wordLen); // extract word
				size_t count = 0;
				for (auto itr = dict->begin(); itr != dict->end(); itr++) {
					if (itr->first.compare(0, wordLen, word) == 0) {
						if (cmd[0] == '=') {
							cout << endl << itr->first;
						} else if (cmd[0] == '?') {
							string def = returnDefinition(itr->second,tempFile);
							cout << endl << def;
						}
						count++;
					}
				}
				if (cmd[0] == '#') {
					cout << count << endl;
				} else if (count == 0) {
					cout << "No definitions match '" << word << "*'" << endl;
				}
			} else {
				// process non-wildcard command
				// match specific word
				const string word = cmd.substr(1);  // extract word
				auto itr = dict->find(word);
				if (itr == dict->end()) { // report no definition
					cout << "No definition for '" << word << "'" << endl;
				} else if (cmd[0] == '#') {   // print count
					cout << ((itr == dict->end()) ? 0 : 1) << endl;
				} else {  // print key or value
					string def = returnDefinition(itr->second,tempFile);
					cout << ((cmd[0] == '?') ? def : itr->first) << endl;
				}
			}
		} else {
			// unknown command
			// show command list
			cout << "Commands:" << endl;
			cout << "  Quit:  quit" << endl;
			cout << "  List words: =<word> or =<prefix>*" << endl;
		    cout << "  List definitions: ?<word> or ?<prefix>*" << endl;
		    cout << "  Count words: #<word> or #<prefix>*" << endl;
		}
		cout << endl << "> ";  // prompt
	} while (cin >> cmd);

	//close files
	pclose(tempFile);
	pclose(file);
	return;
}

/**
 * Run testChambers_20th_CenturyDictionary function.
 *
 * @return EXIT_SUCCESS
 */
int main(void) {
	testChambers_20th_CenturyDictionary();
	return EXIT_SUCCESS;
}
