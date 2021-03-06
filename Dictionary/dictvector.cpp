#include "dict.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

namespace efiilj {

	//Matrix::Matrix(int width, int height) : width(width), height(height)
	DictVector::DictVector() {  };

	bool DictVector::addWord(string word, string definition) {

		word[0] = toupper(word[0]);
		definition[0] = toupper(definition[0]);

		if (definition[definition.length() - 1] != '.')
			definition.append(".");

		if (!findWord(word)) {
			this->words.push_back(word);
			this->definitions.push_back(definition);
			return true;
		}

		return false;
	}

	bool DictVector::findWord(string word) {

		word[0] = toupper(word[0]);

		return (std::find(words.begin(), words.end(), word) != words.end());
	}

	bool DictVector::findWord(string word, int &index) {

		word[0] = toupper(word[0]);

		auto it = std::find(words.begin(), words.end(), word);
		if (it != words.end()) {
			index = distance(words.begin(), it);
			return true;
		}

		return false;
	}

	bool DictVector::findWord(string word, string &definition) {

		int index;
		word[0] = toupper(word[0]);

		if (this->findWord(word, index)) {
			definition = definitions[index];
			return true;
		}

		return false;
	}

	bool DictVector::save(string path) {
		ofstream file;
		file.open(path);
		if (file.is_open()) {
			for (int i = 0; i < words.size(); i++) {
				file << words[i] << "#" << definitions[i] << endl;
			}
			file.close();
			return true;
		}

		return false;

	}

	bool DictVector::load(string path) {
		int index;
		string line;
		ifstream file(path);
		if (file.is_open()) {
			while (getline(file, line))
			{
				index = line.find_first_of("#");
				if (index != string::npos) {
					this->words.push_back(line.substr(0, index));
					this->definitions.push_back(line.substr(index + 1, line.size()));
				}
			}
			file.close();
			return true;
		}

		return false;
	}

	void DictVector::list() {
		for (int i = 0; i < words.size(); i++) {
			cout << " - " << words[i] << ": " << definitions[i] << endl;
		}
	}

	DictVector::~DictVector() { }

}


