//Zeynep Tandogan
#include "fill_empty.h"
#include <iostream>

using namespace std;

fill_empty::fill_empty(){//constructor
	top=NULL;//initialise top
}

fill_empty::~fill_empty(){//destructor
	coordinate_node*p=top;
	while(p!=NULL){//delete one by one 
		top=p->next;
		delete p;
		p=top;
	}
}

bool fill_empty::isEmpty() const{
	if(top==NULL)//when the stack is empty it means top shows null
		return true;
	else
		return false;
}

void fill_empty::push(int val_row,int val_col){
	/* Begin: code taken from DynIntStack.cpp and updated*/
	coordinate_node*p=new coordinate_node;
	p->row=val_row;
	p->col=val_col;

	if(isEmpty()){//Add the first one to the stack
		top=p;
		p->next=NULL;
	}
	else{
		p->next=top;//adding the other new coordinate values to the stack
		top=p;
	}
	/* End: code taken from DynIntStack.cpp*/
}

void fill_empty::pop(int&val_row,int& val_col){
	/* Begin: code taken from DynIntStack.cpp and updated*/

	coordinate_node *p;
	if(isEmpty()){//if there is nothing to pop
		top=NULL;
		return ;
	}
	else{
		val_row=top->row; //deleting the element that is the last added to the stack (first in last out)
		val_col=top->col;
		p=top->next;
		delete top;
		top=p;
	}
	/* End: code taken from DynIntStack.cpp*/
}

