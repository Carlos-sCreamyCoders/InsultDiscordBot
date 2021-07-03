#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

const int M_VAL = 1;  //how similar it is to the training (higher copies whole phrases)
const int OUT_LENGTH = 20;  //in words
const string OUT_FILE = "out.insult";  //where it is written

//===============================================
//=Function Declarations
//===============================================

vector<string> ReadToVector(char* argv[]);
map<string, string> MapCorrolation(char* argv[], vector<string> words);


//===============================================
//=Main
//===============================================

int main(int argc, char* argv[]){
	srand(time(NULL)); // this line initializes the random number generated

	vector<string> words = ReadToVector(argv);
	
	int M = M_VAL;
	//having it based on phrases rather than just words
	map<list<string>, vector<string>> wordmapPhrase;  //the list is the phrase
	list<string> stateList;
	for (int i = 0; i < M; i++) {  //two words in each phrase
	  	stateList.push_back("");
	}

	for (long unsigned int i = 0; i < words.size(); i++) {
		wordmapPhrase[stateList].push_back(words.at(i));
		stateList.push_back(words.at(i));
		stateList.pop_front();
	}

	stateList.clear();
	for (int i = 0; i < M; i++) {
	stateList.push_back("");
	}
	ofstream out;
	out.open(OUT_FILE);
	for (int i = 0; i < OUT_LENGTH; i++) {
		int ind = rand() % wordmapPhrase[stateList].size();
		out << wordmapPhrase[stateList][ind]<<" ";
		stateList.push_back(wordmapPhrase[stateList][ind]);
		stateList.pop_front();
	}
	out << endl;

	return 0;
}


//===============================================
//=Function Definitions
//===============================================

vector<string> ReadToVector(char* argv[]) {
	ifstream in;
	ofstream out;
	in.open("training.txt");
	out.open("vector.txt");

	vector<string> words;
	string next_line;
	while (in >> next_line) {  //reads in the file to a set of words
		for (long unsigned int i = 0; i < next_line.length(); i++) {
			if (!isalpha(next_line[i])){
				next_line = next_line.substr(0, i);
			}
		}
		words.push_back(next_line);
	}
	for (auto itr = words.begin(); itr != words.end(); itr++) {
		//outputs the words in the set to the output file
		out << *itr << endl;
	}
	return words;
	
}

map<string, string> MapCorrolation(char* argv[], vector<string> words) {
	map<string, string> wordmap;
	string last="";
	for (auto itr=words.begin(); itr!=words.end(); itr++) {
		//create a map in the format: <last word, current word>
		wordmap[last]=*itr;
		last = *itr;
	}

	ofstream out;
	out.open((string) argv[1] + "_map.txt");
	for (auto itr = wordmap.begin(); itr != wordmap.end(); itr++) {
		//output the map to a file
		out << itr->first << ", " << itr->second << endl;
	}
	return wordmap;
}
