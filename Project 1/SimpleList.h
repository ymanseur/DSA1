#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using namespace std;

template <class T>
class SimpleList {

	struct Node{
		T data;
		Node* next;
		Node(T t, Node* n=NULL): data(t), next(n){}
	}

	*head, *tail;
	string name;	//name of the list
	
protected:

	void push_front(const T& data){
		if(!head){
			head = new Node(data, NULL);
			tail = head;
		}else{
			Node* temp = head;
			head = new Node(data, temp);
		}
	}
	
	void push_last(const T& data){
		if(!head){
			head = new Node(data, NULL);
			tail = head;
		}else{
			Node* temp = tail;
			tail = new Node(data, NULL);
			temp->next = tail;
		}
	}
	
	T pop_front(){
		Node* temp = head;
		head = head->next;
		T popped = temp->data;
		delete temp;
		return popped;
	}
	
public:
	
	//Returns name of list
	const string& getName() const {return name;}
	
	//Returns true or false if list is empty
	bool isEmpty(){return head==NULL;}
	
	//Abstract push function (will be redefined when template is used)
	virtual void push(const T&) = 0;	
	
	//Abstract pop function (will be redefined when template is used)
	virtual T pop() = 0;	
	
	//Constructor
	SimpleList(string n) : name(n), head(NULL), tail(NULL) {}	
	
	//Default Deconstructor
	virtual ~SimpleList(){	
		Node* ii = head;
		while(ii){
			Node* next = ii->next;
			delete ii;
			ii = next;
		}
	}	
};

//Implement stack class using template
template <class T>
class Stack : public SimpleList<T>{
	public:
		void push(const T& data){SimpleList<T>::push_front(data);}
		T pop(){return this->pop_front();}
		Stack(string name) : SimpleList<T>(name){}
};

//Implement queue class using template
template <class T>
class Queue : public SimpleList<T>{
	public:
		void push(const T& data){SimpleList<T>::push_last(data);}
		T pop(){return this->pop_front();}
		Queue(string name) : SimpleList<T>(name){}
};

#endif
