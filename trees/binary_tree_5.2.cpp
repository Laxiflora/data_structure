#include <iostream>
#include <cstdlib>
using namespace std;
class Binary_Tree;
class Node{
    friend class Binary_Tree;
    public:
        Node* rChild;
        Node* lChild;
        int data;

};

class Binary_Tree{
    public:
        Binary_Tree(void);
        bool isEmpty(void);
        Binary_Tree copy(void);    //copy tree
        bool equal(Binary_Tree);   //is the tree equal
        int count(void);           //count nodes number
        int height(void);          //count tree height
        void swap_sib(void);       //swap tree sibling
        //expression
        //sorting

        // for functions
        Node* root;
    private:
        Node* _copy(Node*);
        bool _equal(Node*,Node*);
        int _count(Node*);
};

Binary_Tree::Binary_Tree(void){
    this->root = NULL;
    //Binary tree could be empty-> no root node
}

bool Binary_Tree::isEmpty(void){
    return this->root == NULL;
}


Binary_Tree Binary_Tree::copy(){
    Binary_Tree temp;
    if(this->root!=NULL){
        temp.root = this->_copy(this->root);
        return temp;
    }
    return temp;
}

Node* Binary_Tree::_copy(Node* orig){
    if(orig == NULL) return NULL;
    else{
        Node* newNode = new Node;
        newNode->data = orig->data;
        newNode->lChild = _copy(orig->lChild);
        newNode->rChild = _copy(orig->rChild);
        return newNode;
    }
}

bool Binary_Tree::equal(Binary_Tree beta){
    if(this->root==NULL && beta.root==NULL) return true;
    else{
        return _equal(this->root,beta.root);
    }
}

bool Binary_Tree::_equal(Node* alpha,Node* beta){
    bool isequal = false;
    if(alpha == NULL && beta == NULL) isequal = true;
    else if(alpha->data==beta->data){
        if(_equal(alpha->lChild,beta->lChild)){
            isequal = _equal(alpha->rChild,beta->rChild);
        }
    }
    return isequal;
}

int Binary_Tree::count(void){
    if(this->isEmpty()) return 0;
    else{
        return _count(this->root);
    }
}

int _count(Node* current){
    if(current==NULL) return 0;
    else{
        int node_left = _count(current->lChild);
        int node_right = _count(current->rChild);
        return 1+node_left+node_right;
    }

}


int main(void){
    Binary_Tree alpha;
    alpha.root = new Node;
    alpha.root->data = 87;
    Binary_Tree beta = alpha.copy();
    cout<<beta.root->data<<endl;
    cout<<alpha.equal(beta)<<endl;
}