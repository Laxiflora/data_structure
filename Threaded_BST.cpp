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
	bool deleted;
	
	
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
	deleted = false;
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
	Node<T>* FindSuccessor(Node<T>*);
	Node<T>* FindPredecessor(Node<T>*);
	void delete_connectNodes(Node<T>* iterator);
	void recursive_deleteNode(Node<T>*,T);
public:
	void traversal_inorder();
	Node<T>& find(T);
	void insert(T);
	void deleteData(T);
	Thread_BST();
	
		
};

//Node<T>* FindSuccessor(Node<T>* input){
//	while
//}

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
		if(data<iterator->data){              //節點應該往左子樹移動 
			if(iterator->hasLeftThread){             //比葉節點小了 
				insert_connectNodes(iterator,data);
				break;
			}
			else{
				iterator = iterator->leftChild;     
			}
		}
		else{                                //節點應該往右子樹移動  
			if(iterator->hasRightThread){    
				insert_connectNodes(iterator,data);
				break;
			}
			else
				iterator=iterator->rightChild;				
		}
	}
}


template <typename T>
void Thread_BST<T>::insert_connectNodes(Node<T>* iterator,T data){  //在知道要插入的地點的情況下決定要插在該節點的左子樹或右子樹並進行連結 
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
	
}

template <typename T>
void Thread_BST<T>::createFirstNodeAndConnect(T data){          //用於連結第一個節點 
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
	if(!iterator->deleted) cout<<iterator->data;
	if(!iterator->hasRightThread){
		recursive_traversal(iterator->rightChild);
	}
}

template <typename T> 
void Thread_BST<T>::deleteData(T data){
	if(!treeIsEmpty()){
		recursive_deleteNode(this->root->leftChild,data);
	}
}


template <typename T>                                                         //TODO:改良delete 
void Thread_BST<T>::recursive_deleteNode(Node<T>* iterator,T target){        //刪除的實作只是讓他在被traversal時被略過 
	if(iterator->data < target && !iterator->hasRightThread){                
		recursive_deleteNode(iterator->rightChild,target);
	}
	else if(iterator->data >target && !iterator->hasLeftThread){
		recursive_deleteNode(iterator->leftChild,target);
	}
	else if(iterator->data==target){
		cout<<iterator->data<<" found , Deleting...\n";
		delete_connectNodes(iterator);
	}
	else{
		cout<<target<<" not found.\n";
	}
}


template <typename T>                                                  //TODO:改良delete 
void Thread_BST<T>::delete_connectNodes(Node<T>* iterator){           //針對recursive_deleteNode做的實作 
	iterator->deleted = true;
}






int main(void){
	Thread_BST<int> alpha;
	alpha.insert(3);
	alpha.insert(5);
	alpha.insert(4);
	alpha.insert(7);
	alpha.insert(2);
	alpha.insert(6);
	alpha.insert(9);
	alpha.deleteData(6);
	alpha.deleteData(10);
	alpha.traversal_inorder();
	return 0;
}




