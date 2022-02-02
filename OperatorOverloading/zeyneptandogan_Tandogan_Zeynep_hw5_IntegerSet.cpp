//Zeynep Tandogan
#include "zeyneptandogan_Tandogan_Zeynep_hw5_IntegerSet.h"
#include <iostream>

using namespace std;

IntegerSet::IntegerSet(){//default constructor
	num_element=0;
	set_array=NULL;
}

IntegerSet::IntegerSet(int element){//constructor with parameter
	if(element>=0){
		num_element=element;
		set_array=new int[num_element];
		for (int i=0;i<num_element;i++){//this part is for the set that have increasing values
			set_array[i]=i;
		}
	}
	else{//for the case we have negative input constructor
		num_element=0;
		set_array=NULL;
	}
}
IntegerSet::~IntegerSet(){//destructor
	num_element=0;
	delete[] set_array;//deleting 
}

IntegerSet::IntegerSet(const IntegerSet &copy){//Copy constructor

	num_element=copy.num_element;//creating ýntegerset corresponds to the copy
	set_array=new int[num_element];

	for (int i=0;i<num_element;){
		set_array[i]=copy.set_array[i];
		i++;
	}
}
IntegerSet IntegerSet::operator+(int element)const{
	
	bool found_before=false;
	for(int i=0;i<num_element;i++){
		if(set_array[i]==element){
			found_before=true;//it is added before
		}
	}
	if(found_before){//not add the added one again
		return *this;
	}
	else if(!found_before){//if it is not added before
		IntegerSet a(num_element+1);//create an ýntegerset with size num_element+1,since we are adding one more element to the set
		for (int i=0;i<num_element;i++){
			a.set_array[i]=set_array[i];
		}
		a.set_array[num_element]=element;//the newly added element to the set
		return a;
	}
}

IntegerSet& IntegerSet::operator=(const IntegerSet &rhs){
	/* Begin: code taken from matrixvector.cpp and updated */ 
	if(this!=&rhs){//if left hand side is not equal to right hand side,we can delete
		num_element=0;
		delete[] set_array;

		num_element=rhs.num_element;
		set_array=new int[num_element];

		
		for(int i = 0; i < num_element; i++)
		{
			set_array[i] = rhs.set_array[i]; // assigning the values
		}

	}
	return *this;
	/* End: code taken from MathVector.cpp */
}

const IntegerSet&IntegerSet::operator+=(const IntegerSet&rhs){
	*this=*this+rhs;//i use + operator here
	return *this;
}

IntegerSet IntegerSet::operator*(const IntegerSet&rhs)const{
	int same=0;
	for (int i=0;i<num_element;i++){
		for (int j=0;j<rhs.num_element;j++){
			if (rhs.set_array[j]==set_array[i])
				same++;//in order not to allocate more memory than it is needed ,i count the same elements in the sets
		}
	}
	IntegerSet a(same);//create integerset with size 'same'
	int count=0;
	for (int i=0;i<num_element;i++){
		for (int j=0;j<rhs.num_element;j++){
			if (rhs.set_array[j]==set_array[i]){//if they are equal, add the element to the new integerset's array
				a.set_array[count]=set_array[i];
				count++;//in order to spesify the index of a.set_array
			}
		}
	}
	return a;
}

IntegerSet IntegerSet::operator+(const IntegerSet&rhs)const {
	int same=0;
	if(num_element!=0){//if the set is not empty
		for (int i=0;i<num_element;i++){
			for (int j=0;j<rhs.num_element;j++){
				if (rhs.set_array[j]==set_array[i])
					same++;//in order to know the number of elements in sets that are the same
			}
		}
		int len_set=num_element+rhs.num_element-same;//finding the size of new IntegerSet
		IntegerSet a(len_set);
		int count=0;
		for (int i=0;i<num_element;i++){//filling the new IntegerSet
			a.set_array[i]=set_array[i];
		}

		int index=0;
		for(int z=0;z<rhs.num_element;z++){
			for(int j=0;j<num_element;j++){
		
				if(rhs.set_array[z]!=set_array[j]){
					count++;
				}

				if(count==num_element){//it means that the element is not equal to any element in the other set.
					a.set_array[num_element+index]=rhs.set_array[z];//add the elenent
					index++;
				}
			}
			count=0;//in order to restart the search
		}
		return a;
	}
	else if(num_element==0 ||rhs.num_element==0){//if one of entered sets equals to empty set
		if(num_element==0){
			IntegerSet a(rhs.num_element);
			for (int i=0;i<rhs.num_element;i++){
				a.set_array[i]=rhs.set_array[i];//just have the one with elements in this case rhs
			}
			return a;
		}
		else{ 
			IntegerSet a(num_element);
			for (int i=0;i<num_element;i++){
				a.set_array[i]=set_array[i];//just have the one with elements in this case lhs
			}
			return a;
		}
	}
}
int* IntegerSet::reach_Array()const{//i create this to reach array which is a private data member

	return this->set_array;
}
int IntegerSet::findnum_element()const{//i create this to reach num_element in the set, which is a private data member
	return this->num_element;
}

//free functions
ostream &  operator << (ostream & os,const IntegerSet & rhs){
	int*rhs_Set=rhs.reach_Array();//i create an array that equals to the array in private part
	int rhs_element=rhs.findnum_element();//i reach the num_element via findnum_element function
	if(rhs_element==0){
		os<<"{}";//if the set is empty
	}
	else{
		bool exist=false;
		for (int i=0;i<rhs_element-1;i++){
			exist=true;//it means there are other elements
			if(i==0)
				os<<"{"<<rhs_Set[i]<<",";
			else
				os<<rhs_Set[i]<<",";
		}
		if(exist==true)//for the last element
			os<<rhs_Set[rhs_element-1]<<"}";
		else
			os<<"{"<<rhs_Set[rhs_element-1]<<"}";//if we have only one element in the set
		
	}
	return os;
}

bool operator<=(const IntegerSet&rhs,const IntegerSet&lhs){
	int count=0;
	int* lhs_Set=lhs.reach_Array();
	int* rhs_Set=rhs.reach_Array();
	for (int i=0;i<lhs.findnum_element();i++){
		for (int j=0;j<rhs.findnum_element();j++){
			if (lhs_Set[i]==rhs_Set[j]){
				count++;
			}
		}
	}
	if(count==rhs.findnum_element()){//if lhs contains all elements of rhs
		return true;
	}
	return false;

}
bool operator<=(const int element,const IntegerSet&lhs){
	int*lhs_set=lhs.reach_Array();
	for(int i=0;i<lhs.findnum_element();i++){
		if (lhs_set[i]==element){//only search for that element whether it is included or not
				return true;
		}
	}
	return false;
}
bool operator !=(const IntegerSet&lhs,const IntegerSet&rhs){
	int*rhs_set=rhs.reach_Array();
	int*lhs_set=lhs.reach_Array();
	int same_count=0;
	if (rhs.findnum_element()==lhs.findnum_element()){//if they include same number of elements
		for (int i=0;i<rhs.findnum_element();i++){
			for(int j=0;j<lhs.findnum_element();j++){
				if (rhs_set[i]==lhs_set[j])
					same_count++;//count the sameness
			}
		}
		if (same_count==rhs.findnum_element())//if same number of elements is equal to the number of element in one of the sets(since their element num are equal there wont be a problem)
			return false;//it means they are equal.
		else
			return true;
	}
	else
		return true;
}