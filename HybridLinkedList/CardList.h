//Zeynep Tandogan
#include <string>
using namespace std;


struct creditCardNode  { 
	string creditCardNo; 
	creditCardNode * next;  
	
	creditCardNode::creditCardNode()
	{
		next=NULL;
	}
	creditCardNode::creditCardNode(const string& creditcardid, creditCardNode* linknext)
		: creditCardNo(creditcardid), next(linknext)
	{}
};

struct expirationNode { 
	int month, year;  
	creditCardNode * cHead;  
	expirationNode * next;  
	expirationNode * prev; 

	expirationNode::expirationNode()
	{
		cHead=NULL;
		next=NULL;
		prev=NULL;
	}
	expirationNode::expirationNode(const int& monthval,const int&yearval, expirationNode* linknext,expirationNode*linkprev, creditCardNode* node_credit)
		:month(monthval),year(yearval),next(linknext),prev(linkprev),cHead(node_credit)
	{}

};

class CardList  {

public: 
	CardList(); //default constructor that creates an empty list 
	void insertCard (string creditCardNo, int month, int year);    //inserts a new card to the structure in sorted fashion 
	void displayListChronological ();  //displays entire structure in chronological order 
	void displayListReverseChronological ();  //displays entire structure in reverse chronological order 
	void cardSearch (string creditCardNo);  //displays all of the occurrences of the given card number 
	void bulkDelete (int month, int year);  //deletes all nodes up to and including given expiration date 
	void deleteAll (); //deletes the entire structure 
	void changes(int month,int year,string creditCardNo, CardList &the_list);//search for distinct dates for creating nodes in doubly linked list
	void ordered_doublylist(int month,int year,string creditcardid);//create ordered expiration date doubly linked list

private:  
	expirationNode * head;
	expirationNode * tail; 
 
};