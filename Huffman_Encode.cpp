/*
A basic approach to huffman_encode , which only accepts "0-9" currently


*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#ifndef INITIAL_SIZE
    #define INITIAL_SIZE 10
#endif

using namespace std;
/*
//The basic class type.
class Node{
protected:
    Node* leftChild;
    Node* rightChild;
};
*/
//The Node class I use.
class Node_Huffman{
    friend class Huffman_Encoder;
protected:
    int frequent;
    int name;               //needs to improve
    Node_Huffman* leftChild;
    Node_Huffman* rightChild;
public:
    Node_Huffman();
    Node_Huffman(int);
};

Node_Huffman::Node_Huffman(){
    frequent=0;
    name = -1;
    leftChild=NULL;
    rightChild=NULL;
}

Node_Huffman::Node_Huffman(int name){
    frequent=0;
    this->name = name;
    leftChild=NULL;
    rightChild=NULL;
}

//The example node.
class Node_Customed:Node_Huffman{
private:
    string something;
    int weight;
};
//

class Huffman_Encoder{
private:
    vector<Node_Huffman*> nodeGroup;
    Node_Huffman* root;
    bool StringInputToNode(string);
    void FrequencySort();
    void BuildTree();
    string Output(string,string*);
    void Recursive_Output(string*,string,Node_Huffman*);
public:
    Huffman_Encode();
    void Test();
    string EncodeWithString(string);

};

//Constructor
    Huffman_Encoder::Huffman_Encode(){
    	//nodeGroup.reserve(10);
    }

/*
	Main Controller
*/
string Huffman_Encoder::EncodeWithString(string input){
	vector<Node_Huffman> NodeGroup;
    bool input_error = false;
    input_error=StringInputToNode(input);
    if(!input_error){
    	string HuffmanCode[10];
    	FrequencySort();
    	BuildTree();
    	return Output(input,HuffmanCode);
    }
    else{
		cout<<"Encode Shut Down.\n";
		return input;
	}
}



/*Process the input to nodes in vector with frequency
	input:string
	outcome:nodeGroup
*/
bool Huffman_Encoder::StringInputToNode(string input){
    bool input_error = false;
    //-------------manually build the node-----
    for(int i=0;i<10;i++){
    	Node_Huffman* temp = new Node_Huffman(i);
		nodeGroup.push_back(temp);
    }

    //-----------------------------------------
    for(int i=0;i<input.length()&&!input_error;i++){
        switch(input[i]){
            case '0':
                nodeGroup[0]->frequent++;
                break;
            case '1':
                nodeGroup[1]->frequent++;
           		break;
		    case '2':
                nodeGroup[2]->frequent++;
            	break;
			case '3':
                nodeGroup[3]->frequent++;
            	break;
			case '4':
                nodeGroup[4]->frequent++;
                break;
            case '5':
                nodeGroup[5]->frequent++;
                break;
            case '6':
                nodeGroup[6]->frequent++;
                break;
            case '7':
                nodeGroup[7]->frequent++;
                break;
            case '8':
                nodeGroup[8]->frequent++;
                break;
            case '9':
                nodeGroup[9]->frequent++;
                break;
            default:
                cout<<"Error! input must between 0~9\n";
                input_error=true;
                break;
        }

    }
    //delete frequent = 0 nodes
    for(int i=0;i<nodeGroup.size();i++){
    	if(nodeGroup[i]->frequent==0){
    		nodeGroup.erase(nodeGroup.begin()+i);
    		i--;
		}
	}
	//
    return input_error;

}

/*Sort the frequency
	input:nodeGroup
	outcome:nodeGroup(frequency sorted)
*/
void Huffman_Encoder::FrequencySort(){           //implemented with bubble sort
	for(int i=0;i<nodeGroup.size();i++){
		for(int j=0;j<nodeGroup.size();j++){
			if(nodeGroup[i]->frequent < nodeGroup[j]->frequent){
				Node_Huffman* temp = nodeGroup[i];
				nodeGroup[i] = nodeGroup[j];
				nodeGroup[j] = temp;
			}
		}
	}
}

/* Build the binary tree
	input:nodeGroup
	output:nodeGroup with tree node(not sorted), root
*/
void Huffman_Encoder::BuildTree(){
	for(int i=0;i<nodeGroup.size()-1;i+=2){
		Node_Huffman* temp = new Node_Huffman();
		temp->frequent = nodeGroup[i]->frequent + nodeGroup[i+1]->frequent;
		temp->leftChild = nodeGroup[i];
		temp->rightChild = nodeGroup[i+1];
		for(int j=i+2;j<=nodeGroup.size();j++){
			if(j+1>=nodeGroup.size()){nodeGroup.push_back(temp); break;}
			if(temp->frequent < nodeGroup[j]->frequent){
				nodeGroup.insert(nodeGroup.begin()+j+1 , temp);
				break;
			}
		}
	}
	this->root = nodeGroup.back();
	for(int i=0;i<nodeGroup.size();i++){
	}
}


/*
Traversal the tree in postorder

*/
string Huffman_Encoder::Output(string input,string* HuffmanCode){
    string path="";
    Node_Huffman* current = root;
    cout<<HuffmanCode[9];
	Recursive_Output(HuffmanCode,path,current);
	string encodedString;
	for(int i=0;i<input.length();i++){
		int temp = input[i]-'0';                         //CAUTION:not a good method
		encodedString += HuffmanCode[temp]+"_";
	}
	return encodedString;
}

/*Recursive function

*/
void Huffman_Encoder::Recursive_Output(string* HuffmanCode,string path,Node_Huffman* current){
	if(current!=NULL){
		//	cout<<"D="<<current->name<<endl;
			Recursive_Output(HuffmanCode,path+"0",current->leftChild);
			Recursive_Output(HuffmanCode,path+"1",current->rightChild);
			if(current->name!=-1){
				cout<<current->name<<" = "<<path<<endl;
				HuffmanCode[current->name] = path;
			}
	}
}


void Huffman_Encoder::Test(){
    for(int i=0;i<nodeGroup.size();i++){
        cout<<nodeGroup[i]->frequent<<" "<<nodeGroup[i]->name<<endl;
    }
    while(root->leftChild!=NULL){
    	cout<<root->leftChild->name<<endl;
    	root = root->leftChild;
	}

}


int main(void){
    Huffman_Encoder alpha;
    string input;
    cin>>input;
    string output = alpha.EncodeWithString(input);
  	cout<<output;
    return 0;
}


