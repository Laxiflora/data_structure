#include <iostream>
#include <cstdlib>
using namespace std;


struct Student{
	public: //for convince
	int ID;
	int Grade;
	public:
		Student(int in_ID,int in_Grade){
			ID = in_ID;
			Grade = in_Grade;
		}
		Student(){
			ID = 0;
			Grade = 0;
		}
	friend ostream& operator<<(ostream& os,const Student in){
		cout<<"Grade = "<<in.Grade<<" ID = "<<in.ID;
		return os;
	}
};
 


///////////////////////////////
template <typename T>
class Node{
template<class U> friend class Linked_List;
private:	
	T data;
	Node* leftNode;
	Node* rightNode;
public:
	Node();
	Node(T);
};

template <typename T>
Node<T>::Node(){
	leftNode = NULL;
	rightNode = NULL;
}

template <typename T>
Node<T>::Node(T input){
	leftNode = NULL;
	rightNode = NULL;
	data = input;
}

template <typename T>
class Linked_List{
	private:
		Node<T>* headptr;
		Node<T>* tailptr;
		Node<T>* iterator;
		int totalSize;
		void ConnectNode(Node<T>*,Node<T>*,Node<T>*);
		void ConnectNode(Node<T>*,Node<T>*);
		void Iterate(int);
		void Traversal(int);
		bool IsTail();
	public:
		void Insert(Node<T>*,int);
		void Insert(T,int);
		void Delete(int);
		int Size();
		Linked_List();
		T& At(int);
};

/*
Connect the nodes
*/
template <typename T>
void Linked_List<T>::ConnectNode(Node<T>* left,Node<T>* mid,Node<T>* right){
	left->rightNode = mid;
	mid->leftNode = left;
	mid->rightNode = right;
	right->leftNode = mid;
}

/*
Connect the nodes(called by delete/insert)
*/
template <typename T>
void Linked_List<T>::ConnectNode(Node<T>* left,Node<T>* right){
	left->rightNode = right;
	right->leftNode = left;
}



template <typename T>
Linked_List<T>::Linked_List(){
	headptr = new Node<T>;
	tailptr = new Node<T>;
	ConnectNode(headptr,tailptr);
	totalSize = 0;
	iterator = NULL;
}


/*
Iterate to the property position
*/
template <typename T>
void Linked_List<T>::Traversal(int position){
	iterator = headptr->rightNode;
	if(position>totalSize) position = totalSize;   //set to the last element
	for(int i=0;i<position;i++){
		iterator = iterator->rightNode;
	}
	
}
/*
insert new Node (parameters=T)
*/
template <typename T>
void Linked_List<T>::Insert(T newData,int position){
	Node<T>* newNode = new Node<T>;
	newNode->data = newData;
	Insert(newNode,position); 
}
/*
insert new Node (parameters=Node*)
*/
template <typename T>
void Linked_List<T>::Insert(Node<T>* newNode,int position){
	Traversal(position);
	ConnectNode(iterator->leftNode,newNode,iterator);
	totalSize++;
}

/*
return list size
*/
template <typename T>
int Linked_List<T>::Size(){
	return this->totalSize;
}

/*
retreve the element
*/
template <typename T>
T& Linked_List<T>::At(int position){
	if(totalSize==0) cout<<"Empty List\n";
	else{
		Traversal(position);
		if(IsTail()) iterator = tailptr->leftNode;       
		return this->iterator->data;
	}
}


template <typename T>
void Linked_List<T>::Delete(int position){
	Traversal(position);          
	if(totalSize==0) cout<<"Empty List\n";          //has no node
	else{
		if(IsTail()) iterator = iterator->leftNode; //has node but last one
		ConnectNode(iterator->leftNode,iterator->rightNode);          //has node
	}
	this->totalSize--;
}

/*
Can be used to do something more
*/
template <typename T>
bool Linked_List<T>::IsTail(){
	return (iterator==tailptr);
}

int main(void){
	Linked_List<Student> test;
	Student insert_test(20,2);
	Student insert_test2(30,3);
	Student insert_test3(40,4);
	test.Insert(insert_test,4);
	cout<<test.At(4)<<endl;
	test.Insert(insert_test2,5);
	test.Delete(0);
	test.Insert(insert_test2,5);
	cout<<test.At(1)<<endl;
}

/*
設計心得:
Template真的是一個要命的東西,簡單的事情多了他就會困難很多...對於insert/delect超過索引的指令有做防呆,但也因此很難用一個函數定義完所有可能性,變的需要在原呼叫函數去做調整
看到很多的所謂"好code"都會進行type_def,比如說Iterator變成Iterator類別之類,但其實作為看code的人我看起來還蠻誤導的,至少現在還沒辦法改過來
在真的可以自由自在用程式來表達演算法之前,資料結構跟程式熟練度真的是一大阻礙呢(以後乖乖用STL或是Python) 
另外要套用這個Linklist,自訂的類別需要實作至少無參數的constructor 
*/
