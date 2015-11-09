/*

Name: 			Yacine Manseur
Date: 			04/10/2014
Class: 			DSA I
Description:	Read in commands from a given file and perform the certain 
				commands dealing with singly linked lists of stacks and queues.
				At the end, a file is written describing the commands processed
				and what was accomplished.
				
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <sstream>
#include "SimpleList.h"

using std::string;
using namespace std;

/*	This function inputs a list and a name to search for within the given list. It 
	creates an iterator and linearly searches through the whole list. If the pointer 
	at a certain index has the same name as the name we are searching for, it returns 
	the list that has that name. If the name is not found within the list, NULL is returned.	*/
template <typename T>
SimpleList<T>* search(list<SimpleList<T> *>& listSL, const string& name){

	typename list<SimpleList<T> *>::iterator ii = listSL.begin();
	
	while (ii != listSL.end()){
		if (name == (*ii)->getName())
			return *ii;
		ii++;
	}
	return NULL;
}

/*	This function chooses what command to perform: create, push or pop. This decision
	is based on what the string command is. Since we can assume the input is correct,
	there is no need to include an error check. Other parameters are passed into this 
	function because this function calls other functions based on what command is 
	asked to be performed.															*/
template <typename T>
void chooseCommand(list<SimpleList<T> *>& listSL, const string& command, 
					const string& name, const string& element, ofstream& myfile){

	if(command == "create"){
		createList(listSL, name, element, myfile);
	}else if (command == "push"){
		pushList(listSL, name, element, myfile);
	}else {
		popList(listSL, name, myfile);
	}
}

/*	This function creates a list. The type of list (int double or string) is given 
	through the template of typename T. In this case, the variable name is the name
	of the list, and the variable listType is either "stack" or "queue." The first
	thing done in this function is to check if there is already a stack or queue
	created that has the same name. If the list already exists, an error is thrown.
	If the list does not exist, the corresponding type of list is created.		*/
template <typename T>
void createList(list<SimpleList<T> *>& mainList, const string& name, 
				const string& listType, ofstream& myfile){
				
	SimpleList<T>* temp = search(mainList, name);
	if(temp == NULL){
		if(listType == "stack"){
			SimpleList<T> *pSLi = new Stack<T>(name);
			mainList.push_front(pSLi);
		}else{
			SimpleList<T> *pSLi = new Queue<T>(name);
			mainList.push_front(pSLi);
		}
	}else{
		myfile << "ERROR: This name already exists! " << endl;
	}
}

/*	This function pushes a variable of type T into a specific list
	of type T. This is done by using string stream, and then extracting
	the data into pushData. The type of pushData is determined by which
	type of list calls this function. The pointer then pushes the data
	into the list that was called at the beginning of the function.
	An error is thrown if the list doesn't exist.					*/
template <typename T>
void pushList(list<SimpleList<T> *>& listSL, const string& name, 
				string value, ofstream& myfile){

	SimpleList<T>* temp = search(listSL, name);
	T pushData;
	if(temp == NULL)
		myfile << "ERROR: This name does not exist!" << endl;
	else{
		T pushdata;
		istringstream buffer(value);
		buffer >> pushdata;
		temp->push(pushdata);
	}
}

/*	This function invokes the pop() function defined in the given list.
	If the list does not exist, or the list is empty, and error is thrown.
	A pointer temp is created that points to the specified list, and the
	pointer invokes the pop() function of the list.					*/
template <typename T>
void popList(list<SimpleList<T> *>& listSL,  string name, ofstream& myfile){

	SimpleList<T>* temp = search(listSL, name);
	
	if(temp == NULL)
		myfile << "ERROR: This name does not exist!" << endl;
	else{
		if(temp->isEmpty()) {
			myfile << "ERROR: This list is empty!" << endl;
		}else{
			myfile << "Value popped: " << temp->pop() << endl;
		}
	}
}

int main() {
	string inputname;	//	name of file inputted
	string outputname;	//	name of file outputted
	string c1;	//	first word
	string c2;	//	second word
	string c3;	//	third word
	int first;	//	index of first space
	int second;	//	index of second space (if there is one)
	ofstream myfile;	//	the output file
	
	list<SimpleList<int> *> listSLi;	//	all integer stacks and queues
	list<SimpleList<double> *> listSLd;	//	all double stacks and queues
	list<SimpleList<string> *> listSLs;	//	all string stacks and queues
	
	//Prompt user for input and output files
	cout << "Enter name of input file: ";
	cin >> inputname;
	cout << "Enter name of output file: ";
	cin >> outputname;
	
	//Initialize read and write files
	ifstream input(inputname.c_str());
	myfile.open(outputname.c_str());
	
	//Loops through every line in the input file.
	for(string line; getline(input, line);){
	
		myfile << "PROCESSING COMMAND: ";
		first = line.find(" ", 0);	//	Index of first space in line.
		c1 = line.substr(0, first);	//	First word in sentence.
		second = line.find(" ", first + 1);	//	Index of second space. If there is no second space, it is -1
		if(second == -1){
			c2 = line.substr(first + 1, line.length()-first-2);
			myfile << c1 << " " << c2 << endl;
		}else{
			c2 = line.substr(first + 1, (second-first - 1));
			c3 = line.substr(second + 1, line.length() - second-2);
			myfile << c1 << " " << c2 << " " << c3 << endl;
		}
		
		char dataType = c2[0];	//will either be i, d, or s
		//check if we are dealing with integer, double, or string
		switch(dataType){
			case 'i':
				chooseCommand(listSLi, c1, c2, c3, myfile);
				break;
			case 'd':
				chooseCommand(listSLd, c1, c2, c3, myfile);
				break;
			case 's':
				chooseCommand(listSLs, c1, c2, c3, myfile);
				break;
		}
	}
	
	input.close();
	myfile.close();
	return 0;
};
