// BETUL CAM
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
struct node{
    int size;
	int quant;
	node *next;
};
struct stock{
	node *head;
	void create();
	void add_stock(int);
	void sell(int);
	void current_stock();
	void clear();
};
//CREATE  FUNCTION
void stock::create(){  //neccessarry to create linked list. root is null now
	head = NULL;
}
//CLEAR FUNCTION
void stock::clear(){
	node *iter;
	while(head){
		iter=head;
		head = head->next;
		delete iter;
	}
}
//ADD_STOCK FUNCTION
void stock::add_stock(int size){
	node *iter = head;
	node *nn;
	nn = new node;
	nn ->next = NULL;
	if(head == NULL){
		head = nn;
		nn->size=size;
		nn->quant=1;
		return;
	}
	else if(size < iter->size){
		nn->next = iter; // head = iter = nn->next
		head =  nn;
		nn->quant = 1;
		nn->size = size;
		return;
	}
	else if(size == iter->size){
		iter->quant++;
		return;
	}
	while(iter->next != NULL){
		if(iter->next->size == size){
			iter->next->quant++;
			break;
		}
		else if(size<iter->next->size){
			nn->next = iter->next;
			iter->next = nn;
			nn->quant = 1;
			nn->size = size;
			break;
		}
		iter = iter->next;
	}
	if(iter->next == NULL){
		iter->next = nn;
		nn->size = size;
		nn->quant = 1;
	}
}
//CURRENT_STOCK
void stock::current_stock( ){ //write current stock
	node *iter =head;
	while(iter != NULL){
		cout<<iter->size<<":"<<iter->quant<<endl;
		iter = iter->next;
	}
}
//SELL FUNCTION
void stock::sell(int size){
	node *iter = head;
	if(iter == NULL){ //if list is empty
		cout<<"NO_STOCK"<<endl;
		return;
	}
	else if(iter->size == size && iter->quant == 1){
		head = iter->next; //first node deleted, root changed(head)
		delete iter;
		return;
	}
	else if(iter->size == size){
		iter->quant--;
	}
	node *iter2= iter->next;
	while(iter2->next != NULL && iter2->size != size){
		iter2 = iter2->next;
		iter= iter->next; 
	}
	if(iter2->size != size){
		cout<<"NO_STOCK"<<	endl;
		return;
	}
	if(iter2->quant == 1 ){
	iter->next = iter2->next;
delete iter2;
return;}	
	else if(iter2->quant > 1){
		iter2->quant = iter2->quant -1;
		return;
	}
}


//MAIN FUNCTION
int main(int argc, char **argv){
	stock mystock;
	mystock.create();
	
	ifstream input(argv[1]);
	if(!input.is_open()){
		cerr<<"failed to open file"<<endl;
	}
	int a=0;
	while(input>>a){
		if(a>0){
			mystock.add_stock(a);
		}
		else if(a==0){
			mystock.current_stock();
		}
		else if(a<0){
			mystock.sell(-a);
		}
	}
	mystock.clear();
	input.close();
	return 0;
}
