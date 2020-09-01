#include <iostream>
#include <cstdlib>
using namespace std;


template <typename T>
class Node{
template <class U> friend class Thread_BST;
private:
	Node<T>* leftChild;
	Node<T>* rightChild;
	Node<T>* parent;
	T data;
	bool hasLeftThread;
	bool hasRightThread; //thread
	
	
public:
	Node();
	Node(T);
};

template <typename T> 
Node<T>::Node(){
	leftChild = NULL;
	rightChild = NULL;
	parent = NULL;
	hasLeftThread = true;
	hasRightThread = true;
}

template <typename T>
Node<T>::Node(T input){
	data = input;
	Node();
}









template <typename T> 
class Thread_BST{
private:
	Node<T>* root;
	bool treeIsEmpty();
	void insert_connectNodes(Node<T>*,T);
	void generateInsertionPosition(T);
	void createFirstNodeAndConnect(T);
	void recursive_traversal(Node<T>*);
public:
	void traversal_inorder();
	Node<T>& find(T);
	void insert(T);
	void deleteData(T);
	Thread_BST();
	void deleteNode(T);
		
};

template <typename T>
Thread_BST<T>::Thread_BST(){
	root = new Node<T>;
	root->leftChild = root;
	root->rightChild=root;
	root->hasLeftThread = true;
	root->hasRightThread = true;
	root->parent = root;
}

template <typename T>
void Thread_BST<T>::insert(T data){
	if(treeIsEmpty()){ //first node
//		cout<<"First called.\n";
		createFirstNodeAndConnect(data);
	}
	else{
		generateInsertionPosition(data);
	}
}

template <typename T> 
void Thread_BST<T>::generateInsertionPosition(T data){
	Node<T>* iterator=root->leftChild;
	while(iterator!=NULL){
//		cout<<"Iterator="<<iterator->data<<"  "<<iterator->hasRightThread<<endl;
		if(data<iterator->data){
			if(iterator->hasLeftThread){
				insert_connectNodes(iterator,data);
//				cout<<"small end called\n";
				break;
			}
			else{
//				cout<<"Head left.\n";
				iterator = iterator->leftChild;
			}
		}
		else{
			if(iterator->hasRightThread){
				insert_connectNodes(iterator,data);
//				cout<<"large end called\n";
				break;
			}
			else{
//				cout<<"Head Right.\n";
				iterator=iterator->rightChild;				
			}
		}
	}
}

template <typename T>
void Thread_BST<T>::insert_connectNodes(Node<T>* iterator,T data){
	Node<T>* input = new Node<T>;
	input->data = data;
	if(iterator->data < input->data){ //rightThread
		input->rightChild=iterator->rightChild;
		input->hasRightThread = true;
		iterator->hasRightThread = false;
		iterator->rightChild = input;
	}
	else{
		input->leftChild=iterator->leftChild;
		input->hasLeftThread = true;
		iterator->hasLeftThread = false;
		iterator->leftChild = input;
	}
//	cout<<iterator->hasRightThread<<" "<<iterator->hasLeftThread<<endl;
	
}

template <typename T>
void Thread_BST<T>::createFirstNodeAndConnect(T data){
	Node<T>* input = new Node<T>;
	input->data = data;
	root->leftChild = input;
	root->hasLeftThread = false;
	input->leftChild = root;
	input->rightChild=root;
	input->hasLeftThread = true;
	input->hasRightThread = true;
	input->parent =root;
}


template <typename T>
bool Thread_BST<T>::treeIsEmpty(){
	return (root->leftChild==root);
}


template <typename T>
void Thread_BST<T>::traversal_inorder(){
	if(!treeIsEmpty()){
		Node<T>* iterator = root->leftChild;
		recursive_traversal(iterator);
	}
}

template <typename T>
void Thread_BST<T>::recursive_traversal(Node<T>* iterator){
	if(!iterator->hasLeftThread){
		recursive_traversal(iterator->leftChild);
	}
	cout<<iterator->data;
	if(!iterator->hasRightThread){
		recursive_traversal(iterator->rightChild);
	}
}
/*
template <typename T>
void deleteNode(T target){
	if(!treeIsEmpty()){
		Node<T>* iterator = root->leftChild;
		recursive_deleteNode(iterator,root,target);
	}
}


template <typename T>
void recursive_deleteNode(Node<T>* iterator,Node<T>* parent,T target){
	if(iterator->data < target && !iterator->hasRightThread){
		recursive_deleteNode(iterator->rightChild,iterator,target);
	}
	else if(iterator->data >target && !iterator->hasLeftThread){
		recursive_deleteNode(iterator->leftChild,iterator,target);
	}
	else if(iterator->data==target){
		cout<<iterator->data<<" found , Deleting...";
		delete_connectNodes(iterator,parent);
	}
	else{
		cout<<target<<" not found.";
	}
}


Node<T>* findSuccessor(Node<T>* current){
	
	while(current->)
}





void delete_connectNodes(Node<T>* toDelete,Node<T>* parent){
	if(parent->leftChild==toDelete){ 
		parent->leftChild=toDelete->rightChild;
	}////////////////////////
	else{
		
	}
}

*/

int main(void){
	Thread_BST<int> alpha;
	alpha.insert(3);
	alpha.insert(5);
	alpha.insert(4);
	alpha.insert(7);
	alpha.insert(2);
	alpha.insert(6);
	alpha.insert(9);
	
	alpha.traversal_inorder();
	return 0;
}




