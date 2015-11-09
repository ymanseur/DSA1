// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2014

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

int i1, i2, ii, bucket;
float intData;
list<Data *>::iterator ipD, ip1, ip2;
list<Data *> sorted;
list<Data *> countB[100000];
Data *output[1100000];
char countC[1100000]; //smallest type of memory

bool compare(const Data* d1, const Data* d2){
//if d1 is smaller than d2, returns true
//else returns false
	i1 = 20;
	i2 = 20;
	while((d1->data)[i1] != '.'){i1--;}
	while((d2->data)[i2] != '.'){i2--;}
		
	if(i1==i2)
		return ((d1->data).compare((d2->data)) < 0);
	else
		return (i1 < i2);
}

//For faster comparisons when decimal point doesn't matter
inline bool compare2(const Data* d1, const Data* d2){
	return ((d1->data).compare((d2->data)) < 0);
}

void bucketSort(list<Data *> &l, int numBuckets, int shift){
	for(ipD = l.begin(); ipD != l.end(); ipD++){
		i1 = 20;
		while(((*ipD)->data)[i1] != '.')
			i1--;
		i2 = i1-shift;
		if(i2 <= 0){
			countB[0].push_back(*ipD);
		} else {
			bucket = atoi((*ipD)->data.substr(0,i2).c_str());
			countB[bucket].push_back(*ipD);
		}
	}
	
	countB[0].sort(compare);
	sorted.splice(sorted.end(), countB[0]);
	for(ii = 0; ii <= numBuckets; ii++){
		countB[ii].sort(compare);
		sorted.splice(sorted.end(), countB[ii]);
	}
	l.swap(sorted);
}


void insertionSort(list<Data *> &l){
	for(ipD = l.begin(); ipD != l.end(); ipD++){
		ip1 = ipD;//ip1 points to the current data member
		ip2 = ip1;
		ip2--;//ip2 points to the data member right before ip1
		while(ip1 != l.begin() && compare2(*ip1, *ip2)){
			iter_swap(ip1,ip2);	//swaps what the two iterators are pointing at
			ip1--;
			ip2--;
		}
	}
}

void countingSort(list<Data *> &l){
	for(ipD = l.begin(); ipD != l.end(); ipD++){
		intData = 1000 * atof((*ipD)->data.c_str());	//since indexes must be integers
		output[(int)intData] = *ipD;	//the index is the actual number being stored multiplied by 1000 to make it an integer
		countC[(int)intData]++; //keeps track of duplicates
	}
	//biggest possible number is 999,999
	for(ii = 0;  ii <=999999; ii++){	
		// this pushes all the values into a sorted list sorted low to high
		while(countC[ii]--){	//loop exits when argument = 0 i.e. no more elements of index ii
			sorted.push_back(output[ii]);
		}
	}
	l.swap(sorted);	//overwrites l with the sorted version of itself
}

void sortDataList(list<Data *> &l) {
	// Fill in this function
  
	
	//Find out which case we are dealing with  
	if((*l.begin())->data.length() < 8){
		//T3
		countingSort(l);
		//Counting Sort
	}else if ((*l.begin())->data.substr(0,15) == ((*++l.begin())->data.substr(0,15))){
		//T4
		insertionSort(l);
		//Insertion Sort
	}else if (l.size() < 500000) {
		//T1
		bucketSort(l, 1000, 17);
		//l.sort(compare);
		//Bucket?
	}else{
		//T2
		bucketSort(l, 10000, 16);
		//l.sort(compare);
		//Bucket?
		}
  }

