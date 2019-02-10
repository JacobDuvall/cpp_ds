// Project1.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

char* printThis(const char* name) {
	return (char*)name;
}

class DataFrame {
protected:

	int** table;
	int noRows, noCols;
	char** colNames;
	char** rowNames;

public:

	//Constructors
	DataFrame() {
		noRows = 0;
		noCols = 0;
		table = NULL;
	}

	DataFrame(int rows, int cols) {
		noRows = rows;
		noCols = cols;

		//Create table
		table = new int*[noRows]; // Creates number of rows for table
		rowNames = new char*[noRows]; //Creates number of rows for rowNames
		colNames = new char*[noCols]; //Creates number of rows for colNames


		for (int i = 0; i < noRows; i++) {
			table[i] = new int[noCols]; // Creates number of columns for table
			rowNames[i] = NULL;

			for (int j = 0; j < noCols; j++) {
				table[i][j] = 0; //sets the table values to 0
			}
		}

		for (int i = 0; i < noCols; i++) {
			colNames[i] = NULL;
		}
	}

	//Output display 
	void display() {

		//display column names
		for (int i = 0; i < noCols; i++) {
			if (colNames[i])cout << colNames[i];
			if (i < noCols - 1) {
				cout << ",";
			}
		}
		cout << "\n";

		//display row names
		for (int i = 0; i < noRows; i++) {
			if (rowNames[i])cout << rowNames[i];
			if (i < noRows - 1) {
				cout << ",";
			}
		}
		cout << "\n";

		//display table values
		for (int i = 0; i < noRows; i++) {
			for (int j = 0; j < noCols; j++) {
				cout << table[i][j] << " ";
			}
			cout << endl;
		}
	}

	//Setters
	void setRowName(int row, const char* name) {
		const char *namex = name;
		while (*namex) namex++;
		int len = namex - name + 1;
		char *retName = new char[len];
		for (int i = 0; i < len; i++) retName[i] = name[i];
		rowNames[row] = retName;
	}

	void setColName(int col, const char* name) {
		const char *namex = name;
		while (*namex) namex++;
		int len = namex - name + 1;
		char *retName = new char[len];
		for (int i = 0; i < len; i++) retName[i] = name[i];
		colNames[col] = retName;
	}

	int* operator[] (int i) { //get row i 
		return table[i];
	}

	//Getters
	char** getRowNames() {
		return rowNames;
	}

	char** getColNames() {
		return colNames;
	}

	int getNumberRows() {
		return noRows;
	}

	int getNumberCols() {
		return noCols;
	}

	//Creates a DataFrame for changing columns
	DataFrame* getColumns(int* columns, int cLen) {

		DataFrame* tempCols = new DataFrame(noRows, cLen);

		for (int i = 0; i < noRows; i++) {
			(*tempCols).setRowName(i, rowNames[i]);
			for (int j = 0; j < cLen; j++) {
				(*tempCols)[i][j] = table[i][columns[j]];
			}
		}
		for (int j = 0; j < cLen; j++) {
			(*tempCols).setColName(j, colNames[columns[j]]);
		}
		return tempCols;
	}

	//Creates a DataFrame for changing rows
	DataFrame* getRows(int* rows, int rLen) {

		DataFrame* tempRows = new DataFrame(rLen, noCols);

		for (int i = 0; i < rLen; i++) {
			(*tempRows).setRowName(i, rowNames[rows[i]]);
		}
		for (int i = 0; i < getNumberCols(); i++) {
			(*tempRows).setColName(i, colNames[i]);
		}
		for (int i = 0; i < rLen; i++) {
			for (int j = 0; j < getNumberCols(); j++) {
				(*tempRows)[i][j] = table[rows[i]][j];
			}
		}
		return tempRows;
	}

	//Creates a DataFrame for changing columns
	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen) {

		DataFrame* tempColsRows = new DataFrame(rLen, cLen);

		for (int i = 0; i < rLen; i++) {
			(*tempColsRows).setRowName(i, rowNames[rows[i]]);
		}
		for (int i = 0; i < cLen; i++) {
			(*tempColsRows).setColName(i, colNames[cols[i]]);
		}

		for (int i = 0; i < rLen; i++) {
			for (int j = 0; j < cLen; j++) {
				(*tempColsRows)[i][j] = table[rows[i]][cols[j]];
			}
		}

		return tempColsRows;
	}

	//Destructor
	~DataFrame() {

		//Deletes table
		if (table != NULL) {
			for (int i = 0; i < noRows; i++) {
				delete[] table[i];
			}
			delete[] table;
		}

		if (rowNames != NULL) {
			for (int i = 0; i < noRows; i++) {

				delete[] rowNames[i];
			}
			delete[] rowNames;
		}
		if (colNames != NULL) {
			for (int i = 0; i < noCols; i++) {
				delete[] colNames[i];
			}
			delete[] colNames;
		}
	}
};

int main()
{
	int c, r;
	int selectC[3];
	int selectR[10];

	//This may be a problem? But if I comment out the const char* code I still have the same issue.
	char** names;
	names = new char*[4];
	for (int i = 0; i < 4; i++) {
		names[i] = new char[100];
	}
	names[0] = printThis("Jack");
	names[1] = printThis("Peter");
	names[2] = printThis("Scores");
	names[3] = printThis("Values");

	//Read the dataframe from input
	//First line: two numbers seperated by space;
	//			  first number is the number of rows (r) and 
	//			  second number is the number of columns (c)

	// Second line: strings seperated by a comma (c of them); representing column name 

	//Third line: strings seperated by a comma (r of them); representing row names
	//Fourth line and more: c number of integers in each of the r rows (seperated by)
	//		a space between integers in the same row.

	//using the display method, print (in the same format as the input):
	// - the column names of the dataframe
	// - the row names of the dataframe
	// - the contents of the table in the dataframe

	cin >> r >> c;
	DataFrame* firstDF = new DataFrame(r, c);

	//Collect column names
	char** columns;
	columns = new char*[c]; //Set c number of columns
	char z;
	int j = 0;
	for (int i = 0; i < c; i++) {
		columns[i] = new char[100];
	}
	cin.get(z);
	for (int i = 0; i < c; i++) {
		cin.get(z);
		j = 0;
		do {
			columns[i][j++] = z;
			cin.get(z);
		} while ((z != ',') && (z != '\n'));
		columns[i][j] = '\0';
	}
	for (int i = 0; i < c; i++) {
		firstDF->setColName(i, columns[i]);
	}

	//Collect row names
	char** rows;
	rows = new char*[r]; //Set r number of rows
	for (int i = 0; i < r; i++) {
		rows[i] = new char[100];
	}
	for (int i = 0; i < r; i++) {
		cin.get(z);
		j = 0;
		do {
			rows[i][j++] = z;
			cin.get(z);
		} while ((z != ',') && (z != '\n'));
		rows[i][j] = '\0';
	}
	for (int i = 0; i < r; i++) {
		firstDF->setRowName(i, rows[i]);
	}

	//Collect table values
	int w;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> w;
			(*firstDF)[i][j] = w;
		}
	}

	(*firstDF).display();

	// Execute the following code

	//Read the column numbers that you want to extract
	for (int i = 0; i < 3; i++) {
		cin >> selectC[i];
	}

	DataFrame* tempColumns = (*firstDF).getColumns(selectC, 3);

	(*tempColumns).display();

	// Change the row names of select rows

	(*tempColumns).setRowName(2, "Jack");
	(*tempColumns).setRowName(3, "Peter");

	(*tempColumns).display();

	for (int i = 0; i < 10; i++) {
		cin >> selectR[i];
	}

	DataFrame* tempRows = (*firstDF).getRows(selectR, 10);

	(*tempRows).display();

	// Change the column names of selected columns

	(*tempRows).setColName(2, "Scores");
	(*tempRows).setColName(3, "Values");

	(*tempRows).display();

	//Extract the rows in SelectR and columns in SelectC

	DataFrame* tempColsRows = (*firstDF).getRowsCols(selectR, 10, selectC, 3);

	(*tempColsRows).display();

	//Code breaks here

	delete tempColumns;
	delete tempRows;
	delete tempColsRows;

	//Sample Code for me 

	DataFrame* myTable = new DataFrame(5, 5);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			(*myTable)[i][j] = i * j;
		}
	}

	(*myTable).display();

	return 0;
}