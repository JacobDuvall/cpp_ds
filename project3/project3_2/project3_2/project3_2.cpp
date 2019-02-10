// Project3_1.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <list>
using namespace std;

//SortedArrays that are to be stored within LinkedSortedArray
template <class DT>
class SortedArray {
protected:
	int _arraySize;
	int _min;
	int _max;
	int _numberOfElements;
public:
	DT * paObject;
	SortedArray();
	SortedArray(int arraySize);
	DT& operator[](int k);
	int binarySearch(const DT& paObjectArr, const DT& key, int first, int last);
	int find(const DT& lookFor);
	int insert(const DT& newElement);
	int remove(DT& oldElement);
	int size();
	int getMax();
	int getMin();
	SortedArray* split(int i);
	~SortedArray();
};

//Default constructor 
template <class DT>
SortedArray<DT>::SortedArray() {
	_arraySize = 0;
	_numberOfElements = 0;
	_min = 0;
	_max = 0;
	paObject = NULL;
}

//int arraySize constructor
template <class DT>
SortedArray<DT>::SortedArray(int arraySize) {
	_arraySize = arraySize;
	_numberOfElements = 0;
	_min = 0; // smallest possible number
	_max = 0; // biggest possible number
	paObject = new DT[_arraySize];
}

//Returns max element
template <class DT>
int SortedArray<DT>::getMax() {
	int x = 0;
	for (int i = 0; i < _numberOfElements; i++) {
		if (x < paObject[i]) {
			x = paObject[i];
		}
	}
	_max = x;
	return x;
}

//Returns min element
template <class DT>
int SortedArray<DT>::getMin() {
	int x = 10000;
	for (int i = 0; i < _numberOfElements; i++) {
		if (x > paObject[i]) {
			x = paObject[i];
		}
	}
	_min = x;
	return x;
}

//Overloads the [] operator
template <class DT>
DT& SortedArray<DT>::operator [] (int k) {
	return paObject[k];
}

// Performs binary search to location position of element
template <class DT>
int SortedArray<DT>::binarySearch(const DT& paObjectArr, const DT& key, int first, int last) {

	int mid; // Middle of array

	if (first < last) { // Checks values passed are sorted

		mid = (first + last) / 2;

		if (key == paObject[mid]) { // key is mid
			return mid;
		}
		if (key > paObject[mid]) { // key is greater than mid
			return binarySearch(paObjectArr, key, mid + 1, last);
		}
		if (key < paObject[mid]) { // key is less than mid
			return binarySearch(paObjectArr, key, first, mid);
		}
		else {
			return -1;
		}
	}
}

// Finds the position using binary search
template <class DT>
int SortedArray<DT>::find(const DT& lookFor) {
	return binarySearch(*paObject, lookFor, 0, _numberOfElements);
}

//Inserts element in sorted order using binary search
template <class DT>
int SortedArray<DT>::insert(const DT& newElement) {

	if (_numberOfElements < _arraySize) { // Checks if there is room in the array

		_numberOfElements++; // increases _numberOfElements by 1

		int insertLocation = binarySearch(*paObject, newElement, 0, _numberOfElements); // Performs binary search to find sorted order

		for (int i = _numberOfElements - 1; i >= 0 && paObject[i] > newElement; i--) {
			paObject[i + 1] = paObject[i];
		}

		for (int i = insertLocation - 1; i < _numberOfElements; i++) {
			paObject[i] = paObject[i];
		}

		paObject[insertLocation - 1] = newElement; // Inserts newElement in sorted order

		if (_numberOfElements == 1) { // If this is the only element, max and min are both that element
			_max = newElement;
			_min = newElement;
		}
		else { // Sets the max and min element accordingly
			if (newElement > _max) {
				_max = newElement;
			}
			if (newElement < _min) {
				_min = newElement;
			}
		}
		return insertLocation;
	}
	else {
		return -1;
	}

}

// removes element 
template <class DT>
int SortedArray<DT>::remove(DT& oldElement) {

	if (find(oldElement) == -1) {
		return -1;
	}
	else {

		int deleteLocation = binarySearch(*paObject, oldElement, 0, _numberOfElements); // Find the location to remove

		for (int i = deleteLocation; i > _numberOfElements - 1; i++) {
			paObject[i] = paObject[i + 1];
		}

		paObject[_numberOfElements] = NULL;

		_numberOfElements--; // Decrements the number of elements by one 

		return deleteLocation;
	}
}

// creates and returns a new SortedArray 
template <class DT>
SortedArray<DT>* SortedArray<DT>::split(int i) {
	SortedArray<DT>* temp = new SortedArray<DT>(_arraySize);

	int k = 0;
	for (int j = i; j < (*this)._numberOfElements; ++j) {
		//(*temp).insert((*this).paObject[j]);
		(*temp)[k] = paObject[j]; // moves elements into temp array
								  //delete [] paObject[k];
								  //remove(paObject[j]);
								  //(*this).remove((*this).paObject[j]);
		k++;
	}

	return temp;
}

//returns _arraySize
template<class DT>
int SortedArray<DT>::size() {
	return _arraySize;
}

// Destroys SortedArray
template <class DT>
SortedArray<DT>::~SortedArray() {
	if (paObject != NULL) {
		delete[] paObject;
	}
	paObject = NULL;
	_arraySize = 0;

}

// Linked Sorted Array class that stores SortedArrays within its nodes
template <class DT>
class LinkedSortedArray {
protected:
	list<SortedArray<DT>> nameIT;
	int ArraySizeFactor; // The maximum size of the array in SortedArray
public:
	LinkedSortedArray(DT& s);
	int find(const DT& lookFor);
	int insert(const DT& newOne);
	int remove(const DT& X);
	void printindex(DT& i);
	void printOutput();
	void printRemove(DT& i);
};

//Prints LinkedSortedArray index alongside SortedArray index
template <class DT>
void LinkedSortedArray<DT>::printindex(DT& i) {
	int index = 0;
	for (auto it = nameIT.begin(); it != nameIT.end(); it++) { // Iterates through list
		if (i <= (*it).getMax() && i >= (*it).getMin()) {
			cout << index << " ";
			cout << (*it).find(i);
			cout << endl;

		}

		index++;
	}
	index--;

}

//Prints the elements stored inside LinkedSortedArray
template <class DT>
void LinkedSortedArray<DT>::printOutput() {
	for (auto it = nameIT.begin(); it != nameIT.end(); it++) { // Iterates through list
		for (int i = 0; i < (*it).size(); i++) {
			cout << (*it).paObject[i] << " ";
		}
	}
	cout << endl;

}

//Prints the LinkedSortedArray index alonside SortedArray index
template <class DT>
void LinkedSortedArray<DT>::printRemove(DT& i) {
	int index = 0;
	for (auto it = nameIT.begin(); it != nameIT.end(); it++) {
		if (((*it).getMax() >= i) && ((*it).getMin() <= i)) {
			if ((*it).find(i) == -1) {
				cout << "-1 -1\n";
			}
			else {
				cout << index << " " << (*it).size() - 1 << endl;
			}
		}
		index++;
	}
}

//LinkedSortedArray constructor
template <class DT>
LinkedSortedArray<DT>::LinkedSortedArray(DT& s) {
	ArraySizeFactor = s;
	SortedArray<DT>* t = new SortedArray<DT>(ArraySizeFactor); // 

	nameIT.push_front(*t); // Places the new Array at the front of the Linked List
}

//Finds if the element is stored within any SortedArray
template <class DT>
int LinkedSortedArray<DT>::find(const DT& lookFor) {
	int index = 0;
	for (auto it = nameIT.begin(); it != nameIT.end(); ++it) { // Iterates through LinkedSortedArray
		if (((*it).getMin() <= lookFor) && ((*it).getMax() >= lookFor)) {
			return (*it).find(lookFor);
		}
		index++;

	}
	return -1;
}

//Inserts elements into the SortedArrays stored in LinkedSortedArray
template <class DT>
int LinkedSortedArray<DT>::insert(const DT& newOne) {
	//Iterate
	//case 1: newOne already inside node, return find value
	//case 2 and 3: call insert, if -1, apply split on SA object (ArraySizeFactor/2)
	//push_back the new SA object

	for (auto it = nameIT.begin(); it != nameIT.end(); ++it) {
		if (find(newOne) == -1) { // If newOne does not exist, insert newOne
			if ((*it).insert(newOne) == -1) {
				nameIT.push_back(*(*it).split(ArraySizeFactor / 2)); //Splits SortedArray
				(*it).insert(newOne);
				break;
			}
		}
	}
	return newOne;
}

//Removes elements from the SortedArrays
template <class DT>
int LinkedSortedArray<DT>::remove(const DT& X) {
	for (auto it = nameIT.begin(); it != nameIT.end(); ++it) {
	}
	return X;

}



//main runs and displays operations
int main()
{
	int k; // size of array collected from user
	cin >> k;

	LinkedSortedArray<int>* A = new LinkedSortedArray<int>(k); // create new LinkedSortedArray

	char submission; // characters collected from user
	int** submissionNum; // values collected from user
	int i;
	int j = 0;

	submissionNum = new int*[2000];
	for (int i = 0; i < 2000; i++) {
		submissionNum[i] = new int[100];
	}

	while (cin >> submission) { // Repeat as long as user enters new submission values
		switch (submission) { // O, I, R, or F

		case 'O': // Display 
		{
			(*A).printOutput();
			break;
		}
		case 'I': // Insert a number
		{
			cin >> i;
			submissionNum[j][0] = i;
			(*A).insert(submissionNum[j][0]);
			(*A).printindex(submissionNum[j][0]);
			j++;

			break;
		}
		case 'R': // Remove a number
		{
			cin >> i;
			submissionNum[j][0] = i;
			(*A).printRemove(submissionNum[j][0]); //if this isnt here than i cant find the value
			(*A).remove(submissionNum[j][0]);
			j++;

			break;
		}
		case 'F': // Find a number
		{
			cin >> i;
			submissionNum[j][0] = i;
			(*A).find(submissionNum[j][0]);
			(*A).printindex(submissionNum[j][0]);
			j++;

			break;
		}
		default: cout << "Wrong value"; // This should never be reached
		}
	}

	return 0;
}