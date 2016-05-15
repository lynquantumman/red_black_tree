/*@desc the 2-3-4 tree and the red-black tree
@writer Quantumman
@improvement if you can do that with only one class, don't make a derived class from that
iteration is a pointer, and the thing in the vector could also be a pointer, 
at that time, -> is liable to be wrong.
if member variety is a pointer type, the complier will not initialise it to NUll
you'd better use constructor to initialise it.
@caution Symbol **********
@need_to_be_done The deletion of the rb_tree 
*/
#include<vector>
using std::vector;
#include<algorithm>
#include<fstream>
#include<iostream>
using namespace std;
enum color{RED=00, BLACK=01};//enum uses the comma to seperate
enum direction{LEFT=0, RIGHT=1,UNDEFINED=3}; 
//===============================
//template <typename T>
//vector<T>::iterator median(vector<T>::iterator begin, vector<T>::iterator begin){//This func can be adapted.
//	sort(begin,end);//sort func writes the vector, and the result vector ascends.
// 	return (end-begin)/2
//}
//==============================


//compare newNumber with the value in the Node to which the pointer points
//if the result direction is NULL, the set that  that direction including the number and the direction it self.




class rb_node{
public:
	double number;
 	rb_node*  direct[2];
 	color parentColor;
};




rb_node* compareSetNode(rb_node* ptr, double newNumber, direction& dir){
	
	dir=newNumber<(ptr->number)?LEFT:RIGHT;
		if(nullptr==ptr->direct[dir])
			return ptr->direct[dir];
		else{//when ptr->direct is NULL
			ptr->direct[dir]=new rb_node;//*******************************************************
			ptr->direct[dir]->direct[LEFT]=nullptr;
			ptr->direct[dir]->direct[RIGHT]=nullptr;
			ptr->direct[dir]->number=newNumber;
			ptr->direct[dir]->parentColor=RED;
			return nullptr;
		}	
	
}

int main(){

	ifstream loadSet("set.txt");//this set includes several numbers with double or int type
	double first;
	loadSet>>first;
	auto toRoot=new rb_node;//*************************************************************
	toRoot->number=first;
	toRoot->parentColor=BLACK;
	toRoot->direct[LEFT]=nullptr;
	toRoot->direct[RIGHT]=nullptr;
	
	rb_node* toNode=nullptr;//This node can be either Root type or rb_root type
	
	double newNumber;
	
	while(loadSet>>newNumber){//the search from a single node
		toNode=toRoot;
		direction dir=UNDEFINED;//to store the newly-insert is in which side
		vector<rb_node*> path;
		vector<direction> dir_path;
		//cout<<"row 71"<<endl;
		cout<<"newNumber is "<<newNumber<<endl;
		do{
		//the existing of path is helpful to further operation.
		path.push_back(toNode);//the path from the root to the newly-insert node(not including the newly-insert node)
		toNode=compareSetNode(toNode, newNumber,dir);
		dir_path.push_back(dir);//the next node can be found by toNode with the dir
		}while(nullptr!=toNode);
		//code above has finished the work about the joining of a newNumber;
		//code below will work with the adjustment of this rb_tree
		cout<<"row 89"<<endl;
		rb_node* toFather=path.back();//the back element
		cout<<"91 and the path.size() is "<<path.size()<<endl;
		if(path.size()>=2){//at least, there is a grandfather node
			cout<<"93"<<endl;
			decltype(path.end()) toToGrandFather=path.end()-2;
			auto toGrandFather=*toToGrandFather;
			cout<<"96"<<endl;
			if(LEFT==dir){//if the newly-insert is on left side
				if(nullptr==toFather->direct[RIGHT]){
				//****************************
				//*****************************
				//************************************
					cout<<"row 93 could work"<<endl;
					if(toGrandFather->direct[LEFT]&&toGrandFather->direct[RIGHT]){
						toGrandFather->direct[LEFT]->parentColor=BLACK;
						toGrandFather->direct[RIGHT]->parentColor=BLACK;
					}
					cout<<"98 could work"<<endl;
					if(toGrandFather->direct[LEFT]&&(toGrandFather->direct[RIGHT]==nullptr)){
						//left-left AVL rotation
						//AVL rotating firstï¼Œthen link with upper pointer
						toFather->direct[RIGHT]=toGrandFather;//the type of toGrandFather is *Root, the type of direct[RIGHT]is *rb_tree 
						toGrandFather->direct[LEFT]=nullptr;
						if(path.size()>=3){
							auto toGrandPlus=path.end()-3;
							auto iter=dir_path.end()-3;
							(*toGrandPlus)->direct[*iter]=toFather;
							//toGrandPlus->
						}
						cout<<"108 could work."<<endl;
					}
					if(toGrandFather->direct[RIGHT]&&(toGrandFather->direct[LEFT]==nullptr)){
						//right-left AVL rotation
						auto temp=toGrandFather->direct[RIGHT];
						toGrandFather->direct[RIGHT]=toFather->direct[LEFT];
						toFather->direct[LEFT]=nullptr;
						toGrandFather->direct[RIGHT]->direct[RIGHT]=temp;

					}
					
				}
				if(toFather->direct[RIGHT]->parentColor==BLACK){//when the right side is not null, the right side must be red
					cout<<"Somethings went wrong."<<endl;
				}
			}
			if(RIGHT==dir){
				//if the newly-insert is on right side
				cout<<"137"<<endl;
				if(nullptr==toFather->direct[LEFT]){
					if(toGrandFather->direct[LEFT]&&toGrandFather->direct[RIGHT]){
						toGrandFather->direct[LEFT]->parentColor=BLACK;
						toGrandFather->direct[RIGHT]->parentColor=BLACK;
					}
					cout<<"143"<<endl;
					if(toGrandFather->direct[LEFT]&&(toGrandFather->direct[RIGHT]==nullptr)){
						//left-right AVL rotation
						auto temp=toGrandFather->direct[LEFT];
						toGrandFather->direct[LEFT]=toFather->direct[RIGHT];
						toFather->direct[RIGHT]=NULL;
						toGrandFather->direct[LEFT]->direct[LEFT]=temp;
					}
					cout<<"141"<<endl;
					if(toGrandFather->direct[RIGHT]&&(toGrandFather->direct[LEFT]==nullptr)){
					//right-right AVL rotation
						toFather->direct[LEFT]=toGrandFather;
						toGrandFather->direct[RIGHT]=nullptr;
						if(path.size()>=3){
							auto toGrandPlus=path.end()-3;
							auto iter=dir_path.end()-3;
							(*toGrandPlus)->direct[*iter]=toFather;
						}
					}
				}
				if(toFather->direct[LEFT]->parentColor==BLACK)//when the right side is not null, the right side must be red
					cout<<"Somethings went wrong."<<endl;//*************************************
			}
		}
		cout<<"158"<<endl;
	}
loadSet.close();
//system("pause");
}
