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
        void swap_sib(Node*);       //swap tree sibling
        //expression
        //sorting

        // for functions
        Node* root;
    private:
        Node* _copy(Node*);
        bool _equal(Node*,Node*);
        int _count(Node*);
        int _height(Node*,int);

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

int Binary_Tree::_count(Node* current){
    if(current==NULL) return 0;
    else{
        int node_left = _count(current->lChild);
        int node_right = _count(current->rChild);
        return 1+node_left+node_right;
    }

}

int Binary_Tree::height(void){
    if(isEmpty()) return 0;
    else{
        return _height(this->root,1);
    }
}

int Binary_Tree::_height(Node* current,int height){
    int rHeight=height;
    int lHeight=height;
    if(current->rChild!=NULL){
        rHeight =  _height(current->rChild,height+1);
    }
    else if(current->lChild!=NULL){
        lHeight = _height(current->lChild,height+1);
    }
    return max(rHeight,lHeight);
}

void Binary_Tree::swap_sib(Node* current){
    if(current!=NULL){
        swap_sib(current->lChild);
        swap_sib(current->rChild);
        Node* temp = current->lChild;
        current->lChild = current->rChild;
        current->rChild = temp;
    }
}

int main(void){
    Binary_Tree alpha;
    alpha.root = new Node;
    alpha.root->data = 32;
    alpha.root->rChild = new Node;
    alpha.root->rChild->lChild = new Node;
    alpha.root->rChild->rChild = new Node;
    alpha.root->rChild->lChild->data = 120;
    alpha.root->rChild->rChild->data = 321;
    alpha.root->lChild = new Node;
    Binary_Tree beta = alpha.copy();
    cout<<"Copy--beta.root: "<<beta.root->data<<endl;
    cout<<"is Equal: "<<alpha.equal(beta)<<endl;
    cout<<"Node count: "<<alpha.count()<<endl;
    cout<<"Height: "<<alpha.height()<<endl;
    cout<<"Before Change: "<<alpha.root->rChild->lChild->data<<endl;
    alpha.swap_sib(alpha.root->rChild);
    cout<<"Changed: "<<alpha.root->rChild->lChild->data<<endl;
}

/*TODO
swap sibling
expression
sorting
*/