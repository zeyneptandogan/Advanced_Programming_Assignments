//Zeynep Tandogan
#include <iostream>
using namespace std;

class IntegerSet{
public:
	IntegerSet();//empty-default constructor
	IntegerSet(int);//it will take num_element -constructor with parameter
	~IntegerSet();//destructor
	IntegerSet(const IntegerSet &);//deep copy
	IntegerSet operator+(int)const; //summation
	IntegerSet & operator=(const IntegerSet &);
	const IntegerSet& operator+=(const IntegerSet&);
	IntegerSet  operator *(const IntegerSet&)const;
	IntegerSet operator+(const IntegerSet&)const;//union

	int* reach_Array()const;//these two functions are to reach private data members for free functions
	int findnum_element()const;

private:
	int num_element;
	int *set_array;
};

//free functions
ostream &  operator << (ostream & os, const IntegerSet & ct);
bool operator<=(const IntegerSet&,const IntegerSet&) ;
bool operator<=(const int,const IntegerSet&);
bool operator !=(const IntegerSet&,const IntegerSet&);