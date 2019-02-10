// ttree: The words that match the characters you typed are displayed
#include <iostream>
#include <list>
#include <string>
using namespace std;

// tree class declaration
class ttree;

//-----------Exceptions-------------------------
class Exception {};								// Exception class
class ttreeException : public exception {};		// ttree exception
class ttreeNotFound : public ttreeException {}; // ttreeNotFound exception

												// ttree: a tree that stores tnodes 

// tnode: contains an array of tnodes with the size of 26, representing A(0) to Z(25)
class tnode {
private:
	ttree* _nextLevel; // pointer to the ttree at the next level
	list<string>* _words; // store keywords

	void copy(tnode& tn); // public copy constructor

public:
	tnode(); // default constructor of tnode
	tnode(tnode& tn); // non-empty constructor
	~tnode(); // destructor of tnode

	friend ostream& operator<< (ostream& s, ttree& tt);
	ttree* getNext();
	list<string>* getWords();
	void find(string key, list<string>* results);

	void put(string key);
	void insert(string key, int depth, int maxDepth);
	void setNext(ttree* nextLevel);
	void setWords(list<string>* words);

	void operator=(tnode& tn);
};

// Default constructor for tnode
tnode::tnode() {
	_nextLevel = NULL;
	_words = NULL;
}

// Non-Empty constructor
tnode::tnode(tnode& tn) {
	copy(tn);   
}

// Destructor for tnode
tnode::~tnode() {
}

// Copy constructor
void tnode::copy(tnode& tn) {
	_nextLevel = tn._nextLevel;
	_words = tn._words;
}

// getNext Method
ttree* tnode::getNext() {
	return _nextLevel;
}

list<string>* tnode::getWords() {
	return _words;
}

void tnode::find(string key, list<string>* results) {
	
}

void tnode::put(string key) {
	//iterator? 
	_words->push_front(key);
}

void tnode::insert(string key, int depth, int maxDepth) {
	if (_nextLevel && (int)key.size() > depth) {
		(*_nextLevel).insert(key);
		return;
	}
	char next = key[depth];
	list<string>::iterator it;
	for (it = _words->begin(); it != _words->end(); it++) {
		string& ot = *it;
		if (ot == key) {
			return;
		}
		if (ot[depth] == next && depth < maxDepth) {
			_nextLevel = new ttree(maxDepth);
			_nextLevel->setDepth(depth + 1); 
			it = _words->begin();
			if ((int)it->size() == depth) {
				it++;
			}
			while (it != _words->end()) {
				list<string>::iterator it2 = it;
				it2++;
				_nextLevel->_tnodes[(*it)[depth] - 'A']._words->push_back(*it);
				_words->erase(it);
				it = it2;
			}
			_nextLevel->insert(key);
			return;
		}
		if (ot > key) {
			break;
		}
		_words->insert(it, key);
	}
}

void tnode::setNext(ttree* nextLevel) {
	_nextLevel = nextLevel;
}

void tnode::setWords(list<string>* words) {
	_words = words;
}

class ttree {
private:
	friend class tnode;
	int _maxDepth; // max depth allowance
	int _currentDepth; // The depth of the current node (root is depth 1)
public:
	tnode * _tnodes; // pointer to _tnodes, a tnode array of size 26 will be created in the constructor
	ttree(); // set the maxDepth to 5 in the empty constructor;
	ttree(int maxDepth); // constructor with given maxDepth value;
	ttree(int maxDepth, int currentDepth); // constructor maxDepth and currentDepth
	~ttree(); // destructor of ttree
	void insert(string key); // insert 'key' into the tree
	void search(string key); // search for 'key' in the tree and print out all the matches
	void setDepth(int depth);
	// ostream operator and other methods
};

// Default constructor for ttree
ttree::ttree() {
	_tnodes = NULL;
	_maxDepth = 5;
	_currentDepth = 1;
}

// maxDepth parameter constructor for ttree
ttree::ttree(int maxDepth) {
	_maxDepth = maxDepth;
}

ttree::ttree(int maxDepth, int currentDepth) {
	_maxDepth = maxDepth;
	_currentDepth = currentDepth;
}

// Destructor for ttree
ttree::~ttree() {
	if (_tnodes != NULL) {
		delete _tnodes;
	}
	_tnodes = NULL;
}

// Insert into the ttree
void ttree::insert(string key) {
	_tnodes[key[_currentDepth - 1] - 'A'].insert(key, _currentDepth, _maxDepth);

}

// Search the ttree
void ttree::search(string key) {

}

void ttree::setDepth(int depth) {
	_currentDepth = depth;
}




int main()
{

	char submission; // characters collected from the user
	string input = ""; // string collected from the user
	ttree* dict = new ttree();

	while (cin >> submission) {
		switch (submission) { // I, S, or D

			case 'I': // Insert word
			{
				cin >> input;
				//cout << input << endl;
				dict->insert(input);

				break;
			}

			case 'S': // Search words
			{
				cin >> input;
				//cout << input << endl;
				dict->search(input);

				break;
			}

			case 'D': // Display 
			{
				//cout << "Display" << endl;

				break;
			}

			default: cout << "Error: Input not recognized.\n"; // outputs if input is not I, S, or D
		}
	}


    return 0;
}
