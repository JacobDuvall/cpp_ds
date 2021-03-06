//Calculate and analyze various sorting algorithm times (insertion sort, selection sort, heap sort, and quick sort)

#include <iostream>
using namespace std;
#include <windows.h>
#include <time.h>
#include <ctime>
#include <list>

int* A; //int pointer A
int* B; //int pointer B
int X[] = { 1000, 1500, 2000, 2500, 3000, 3300, 3500, 4000, 4500, 5000 }; //array X containing 10 elements varying in sizes from 1000 to 5000

//insertion sort algorithm
void insertionSort(int arr[], int size) { //takes int array and int size of array
	int i;
	int j;
	int key; //insert element

	for (i = 1; i < size; i++) {
		key = arr[i]; //key is set to arr[i]
		j = i - 1; // j is one less than i
		
		while ((j >= 0) && (arr[j] > key)) { //loop while j is greater or 0 and arr[j] greater than key
			arr[j + 1] = arr[j]; //sets the element one greater than arr[j] to arr[j]
			j--; //decrement j
		}
		arr[j + 1] = key; //arr[j + 1] is set to key
	}
}

//swap values of arrays
void swap(int x[], int y[]) { //takes 2 arrays 
	int temp = *x; //needs a temporary array in order to swap correctly
	*x = *y; //x is y
	*y = temp; //y is original x
}

//selection sort algorithm
void selectionSort(int arr[], int size) { //takes int array and int size of array
	int i;
	int j;
	int min; //minimum element

	for (int i = 0; i < size - 1; i++) { //loop through arr size
		min = i; //set min to i value
		for (j = i + 1; j < size; j++) { //loop through size starting at i + j
			if (arr[j] < arr[min]) { // if array at j is less than array at min
				min = j; //set min to j
			}
		}
		swap(arr[min], arr[i]); //swap array at min and array at i
	}
}

//heap function called on by heapSort
void heap(int arr[], int size, int i) { //takes array, size, and i valeu from heapSort
	
	int root = i; //largest is the root
	int left = 2 * i + 1; //left child algorithm
	int right = 2 * i + 2; //right child algorithm

	if (left < size && arr[left] > arr[root]) { //check if left child is greater than root
		root = left; //set root to left child
	}
	if (right < size && arr[right] > arr[root]) { //check if right child is greater than root
		root = right; //set root to right child
	}
	if (root != i) { //if root not root
		swap(&arr[i], &arr[root]); //swap root and element
		heap(arr, size, root); //recursively make sub-tree into heap
	}
}

//heap sort algorithm
void heapSort(int arr[], int size) { //takes int array and int size from array
	for (int i = size / 2 - 1; i >= 0; i--) { //loops through array from its midpoint size down
		heap(arr, size, i); //call to heap function
	}
	for (int i = size - 1; i >= 0; i--) { //loops through array from its size down
		swap(arr[0], arr[i]); //swap array at 0 with array at i
		heap(arr, i, 0); //call to heap function
	}
}

//quick sort algorithm
void quickSort(int arr[], int n, int left, int right) { //takes array, array size, left value, and right value
	if (left < right) { //if left less than right
		int pivot = arr[left]; //set pivot to array at left value element

		int i = left; // i is left
		int j = right + 1; //j is right + 1
		do {
			do {
				i++; //increment i
			} while ((i < n) && (arr[i] < pivot)); //do while i greater than size of array and array at i is less than pivot value
			do {
				j--; 
			} while (arr[j] > pivot); //do while array at j is greater than pivot value
			if (i < j) { //if i is less than j
				swap(arr[i], arr[j]); //swap array at i value and array at j value
			}
		} while (i < j); //do while i is less than j
		swap(arr[left], arr[j]); //swap array at left value and array at j value
		quickSort(arr, n, left, j - 1); //recursive call to quickSort
		quickSort(arr, n, j + 1, right); //recursive call to quickSort
	}
}

//checks algorithm speeds for arrays of various sizes from 1000 to 5000
int main()
{
	LARGE_INTEGER start; //start tick value
	LARGE_INTEGER stop; //stop tick value

	//create a seed
	A = new int[30]; //array A of size 30
	B = new int[30]; //array B of size 30

	int seed = static_cast<int>(time(0)); //seed is equal to time(0) which will be different each time the program is run
	srand(seed); //makes it so the rand function is random each time the program is run

	for (int i = 0; i < 30; i++) { 
		A[i] = rand(); //fill up the array A with 30 random numbers
	}

	for (int i = 0; i < 30; i++) {
		B[i] = A[i]; //fill B with A's values
	}

	cout << "Before insertion sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 unsorted elements of B
	}
	cout << endl;

	insertionSort(B, 30); //call insertion sort on B

	cout << "After insertion sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 sorted elements of B
	}
	cout << endl << endl;

	for (int i = 0; i < 30; i++) {
		B[i] = A[i]; //fill B with A's values
	}

	cout << "Before selection sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 unsorted elements of B
	}
	cout << endl;

	selectionSort(B, 30); //call selection sort on B

	cout << "After selection sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 sorted elements of B
	}
	cout << endl << endl;

	for (int i = 0; i < 30; i++) {
		B[i] = A[i]; //fill B with A's values
	}

	cout << "Before heap sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 unsorted elements of B
	}
	cout << endl;

	heapSort(B, 30); //call heapsort on B

	cout << "After heap sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 sorted elements of B
	}
	cout << endl << endl;

	for (int i = 0; i < 30; i++) {
		B[i] = A[i]; //fill B with A's values
	}

	cout << "Before quick sort: ";
	for (int i = 0; i < 10; i++) { 
		cout << B[i] << " "; //print first 10 unsorted elements of B
	}
	cout << endl;

	quickSort(B, 30, 0, 29); //call quicksort on B

	cout << "After quick sort: ";
	for (int i = 0; i < 10; i++) {
		cout << B[i] << " "; //print first 10 sorted elements of B
	}
	cout << endl << endl;

	delete[] A; //delete array A

	int average[400]; //array to store tick values
	list<int> averagelist; //averagelist list of type int

	for (int k = 0; k < 10; k++) { //loop 10 times to hit all 10 values of array X from 1000 to 5000

		A = new int[X[k]]; //initialize array A to size [X[k]]
		B = new int[X[k]]; //initialize array B to size [X[k]]

		for (int set = 0; set < 10; set++) { //generate 10 different sets in order to get an average based off 10 different values

			for (int i = 0; i < X[k]; i++) { //loop the size of X[k]
				A[i] = rand(); //fill up array A with X[k] random numbers
			}

			for (int i = 0; i < X[k]; i++) { // i from 0 to array size
				B[i] = A[i]; //make B values equal to A values
			}
			QueryPerformanceCounter(&start); //start clock
			insertionSort(B, X[k]); //insertionSort
			QueryPerformanceCounter(&stop); //stop clock
			averagelist.push_back(stop.QuadPart - start.QuadPart); //add insertion sort tick time to end of averagelist

			for (int i = 0; i < X[k]; i++) { // i from 0 to array size
				B[i] = A[i]; //make B values equal to A values
			}
			QueryPerformanceCounter(&start); //start clock
			selectionSort(B, X[k]); //selectionSort
			QueryPerformanceCounter(&stop); //stop clock
			averagelist.push_back(stop.QuadPart - start.QuadPart); //add selection sort tick time to end of averagelist

			for (int i = 0; i < X[k]; i++) { // i from 0 to array size
				B[i] = A[i]; //make B values equal to A values
			}
			QueryPerformanceCounter(&start); //start clock
			heapSort(B, X[k]); //heapSort
			QueryPerformanceCounter(&stop); //stop clock
			averagelist.push_back(stop.QuadPart - start.QuadPart); //add heap sort tick time to end of averagelist

			for (int i = 0; i < X[k]; i++) { // i from 0 to array size
				B[i] = A[i]; //make B values equal to A values
			}
			QueryPerformanceCounter(&start); //start clock
			quickSort(B, X[k], 0, X[k] - 1); //quickSort
			QueryPerformanceCounter(&stop); //stop clock
			averagelist.push_back(stop.QuadPart - start.QuadPart); //add quick sort tick time to end of averagelist
		}
	}

	int i = 0; 
	for (list<int>::iterator it = averagelist.begin(); it != averagelist.end(); it++) { //iterate through list of 400 tick elements
		average[i] = *it; //populate average array with 400 tick elements
		i++;
	}

	/*
		Every 4th element is related by way of common sorting algorithm tick time
		Every 40 elements is a new array size
		i.e. elements 0, 4, 8, 12, 16, 20, 24, 28, 32, 36 are all insertion sort tick times from array size 1000
			when these 10 elements are added together and divided by 10, the average is found
		This process is done 40 times to find the average of 4 different sorts for 10 different array sizes 
	*/
	//1000
	cout << endl;
	//Average of ten insertion sorts for an array of size 1000
	int insertiontotal = average[0] + average[4] + average[8] + average[12] + average[16] +
		average[20] + average[24] + average[28] + average[32] + average[36];
	cout << "insertion sort (1000) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 1000
	int selectiontotal = average[1] + average[5] + average[9] + average[13] + average[17] +
		average[21] + average[25] + average[29] + average[33] + average[37];
	cout << "selection sort (1000) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 1000
	int heaptotal = average[2] + average[6] + average[10] + average[14] + average[18] +
		average[22] + average[26] + average[30] + average[34] + average[38];
	cout << "heap sort (1000) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 1000
	int quicktotal = average[3] + average[7] + average[11] + average[15] + average[19] +
		average[23] + average[27] + average[31] + average[35] + average[39];
	cout << "quick sort (1000) average: " << quicktotal / 10 << endl;

	//1500
	cout << endl;
	//Average of ten insertion sorts for an array of size 1500
	insertiontotal = average[40] + average[44] + average[48] + average[52] + average[56] +
		average[60] + average[64] + average[68] + average[72] + average[76];
	cout << "insertion sort (1500) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 1500
	selectiontotal = average[41] + average[45] + average[49] + average[53] + average[57] +
		average[61] + average[65] + average[69] + average[73] + average[77];
	cout << "selection sort (1500) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 1500
	heaptotal = average[42] + average[46] + average[50] + average[54] + average[58] +
		average[62] + average[66] + average[70] + average[74] + average[78];
	cout << "heap sort (1500) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 1500
	quicktotal = average[43] + average[47] + average[51] + average[55] + average[59] +
		average[63] + average[67] + average[71] + average[75] + average[79];
	cout << "quick sort (1500) average: " << quicktotal / 10 << endl;

	//2000
	cout << endl;
	//Average of ten insertion sorts for an array of size 2000
	insertiontotal = average[80] + average[84] + average[88] + average[92] + average[96] +
		average[100] + average[104] + average[108] + average[112] + average[116];
	cout << "insertion sort (2000) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 2000
	selectiontotal = average[81] + average[85] + average[89] + average[93] + average[97] +
		average[101] + average[105] + average[109] + average[113] + average[117];
	cout << "selection sort (2000) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 2000
	heaptotal = average[82] + average[86] + average[90] + average[94] + average[98] +
		average[102] + average[106] + average[110] + average[114] + average[118];
	cout << "heap sort (2000) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 2000
	quicktotal = average[83] + average[87] + average[91] + average[95] + average[99] +
		average[103] + average[107] + average[111] + average[115] + average[119];
	cout << "quick sort (2000) average: " << quicktotal / 10 << endl;

	//2500
	cout << endl;
	//Average of ten insertion sorts for an array of size 2500
	insertiontotal = average[120] + average[124] + average[128] + average[132] + average[136] +
		average[140] + average[144] + average[148] + average[152] + average[156];
	cout << "insertion sort (2500) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 2500
	selectiontotal = average[121] + average[125] + average[129] + average[133] + average[137] +
		average[141] + average[145] + average[149] + average[153] + average[157];
	cout << "selection sort (2500) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 2500
	heaptotal = average[122] + average[126] + average[130] + average[134] + average[138] +
		average[142] + average[146] + average[150] + average[154] + average[158];
	cout << "heap sort (2500) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 2500
	quicktotal = average[123] + average[127] + average[131] + average[135] + average[139] +
		average[143] + average[147] + average[151] + average[155] + average[159];
	cout << "quick sort (2500) average: " << quicktotal / 10 << endl;


	//3000
	cout << endl;
	//Average of ten insertion sorts for an array of size 3000
	insertiontotal = average[160] + average[164] + average[168] + average[172] + average[176] +
		average[180] + average[184] + average[188] + average[192] + average[196];
	cout << "insertion sort (3000) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 3000
	selectiontotal = average[161] + average[165] + average[169] + average[173] + average[177] +
		average[181] + average[185] + average[189] + average[193] + average[197];
	cout << "selection sort (3000) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 3000
	heaptotal = average[162] + average[166] + average[170] + average[174] + average[178] +
		average[182] + average[186] + average[190] + average[194] + average[198];
	cout << "heap sort (3000) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 3000
	quicktotal = average[163] + average[167] + average[171] + average[175] + average[179] +
		average[183] + average[187] + average[191] + average[195] + average[199];
	cout << "quick sort (3000) average: " << quicktotal / 10 << endl;

	//3300
	cout << endl;
	//Average of ten insertion sorts for an array of size 3300
	insertiontotal = average[200] + average[204] + average[208] + average[212] + average[216] +
		average[220] + average[224] + average[228] + average[232] + average[236];
	cout << "insertion sort (3300) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 3300
	selectiontotal = average[201] + average[205] + average[209] + average[213] + average[217] +
		average[221] + average[225] + average[229] + average[233] + average[237];
	cout << "selection sort (3300) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 3300
	heaptotal = average[202] + average[206] + average[210] + average[214] + average[218] +
		average[222] + average[226] + average[230] + average[234] + average[238];
	cout << "heap sort (3300) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 3300
	quicktotal = average[203] + average[207] + average[211] + average[215] + average[219] +
		average[223] + average[227] + average[231] + average[235] + average[239];
	cout << "quick sort (3300) average: " << quicktotal / 10 << endl;

	//3500
	cout << endl;
	//Average of ten insertion sorts for an array of size 3500
	insertiontotal = average[240] + average[244] + average[248] + average[252] + average[256] +
		average[260] + average[264] + average[268] + average[272] + average[276];
	cout << "insertion sort (3500) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 3500
	selectiontotal = average[241] + average[245] + average[249] + average[253] + average[257] +
		average[261] + average[265] + average[269] + average[273] + average[277];
	cout << "selection sort (3500) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 3500
	heaptotal = average[242] + average[246] + average[250] + average[254] + average[258] +
		average[262] + average[266] + average[270] + average[274] + average[278];
	cout << "heap sort (3500) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 3500
	quicktotal = average[243] + average[247] + average[251] + average[255] + average[259] +
		average[263] + average[267] + average[271] + average[275] + average[279];
	cout << "quick sort (3500) average: " << quicktotal / 10 << endl;

	//4000
	cout << endl;
	//Average of ten insertion sorts for an array of size 4000
	insertiontotal = average[280] + average[284] + average[288] + average[292] + average[296] +
		average[300] + average[304] + average[308] + average[312] + average[316];
	cout << "insertion sort (4000) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 4000
	selectiontotal = average[281] + average[285] + average[289] + average[293] + average[297] +
		average[301] + average[305] + average[309] + average[313] + average[317];
	cout << "selection sort (4000) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 4000
	heaptotal = average[282] + average[286] + average[290] + average[294] + average[298] +
		average[302] + average[306] + average[310] + average[314] + average[318];
	cout << "heap sort (4000) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 4000
	quicktotal = average[283] + average[287] + average[291] + average[295] + average[299] +
		average[303] + average[307] + average[311] + average[315] + average[319];
	cout << "quick sort (4000) average: " << quicktotal / 10 << endl;

	//4500
	cout << endl;
	//Average of ten insertion sorts for an array of size 4500
	insertiontotal = average[320] + average[324] + average[328] + average[332] + average[336] +
		average[340] + average[344] + average[348] + average[352] + average[356];
	cout << "insertion sort (4500) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 4500
	selectiontotal = average[321] + average[325] + average[329] + average[333] + average[337] +
		average[341] + average[345] + average[349] + average[353] + average[357];
	cout << "selection sort (4500) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 4500
	heaptotal = average[322] + average[326] + average[330] + average[334] + average[338] +
		average[342] + average[346] + average[350] + average[354] + average[358];
	cout << "heap sort (4500) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 4500
	quicktotal = average[323] + average[327] + average[331] + average[335] + average[339] +
		average[343] + average[347] + average[351] + average[355] + average[359];
	cout << "quick sort (4500) average: " << quicktotal / 10 << endl;

	//5000
	cout << endl;
	//Average of ten insertion sorts for an array of size 5000
	insertiontotal = average[360] + average[364] + average[368] + average[372] + average[376] +
		average[380] + average[384] + average[388] + average[392] + average[396];
	cout << "insertion sort (5000) average: " << insertiontotal / 10 << endl;

	//Average of ten selection sorts for an array of size 5000
	selectiontotal = average[361] + average[365] + average[369] + average[373] + average[377] +
		average[381] + average[385] + average[389] + average[393] + average[397];
	cout << "selection sort (5000) average: " << selectiontotal / 10 << endl;

	//Average of ten heap sorts for an array of size 5000
	heaptotal = average[362] + average[366] + average[370] + average[374] + average[378] +
		average[382] + average[386] + average[390] + average[394] + average[398];
	cout << "heap sort (5000) average: " << heaptotal / 10 << endl;

	//Average of ten quick sorts for an array of size 5000
	quicktotal = average[363] + average[367] + average[371] + average[375] + average[379] +
		average[383] + average[387] + average[391] + average[395] + average[399];
	cout << "quick sort (5000) average: " << quicktotal / 10 << endl;

	return 0;

}

