//Zeynep Tandogan
#include <iostream>
#include "CardList.h"

using namespace std;

CardList::CardList()//default
{
	head=NULL;
	tail=NULL;
}


void CardList::insertCard(string creditCardNo, int month, int year){
	expirationNode *ptr=head;
	while(ptr!=NULL){
		if (ptr->month==month&& ptr->year==year){
			creditCardNode *p=ptr->cHead;
			if(p==NULL){//if there is no credit card that was added.
				creditCardNode*temp=new creditCardNode;
				temp->creditCardNo=creditCardNo;
				p=temp;
				p->next=NULL;
				return;
			}
			else if(p!=NULL && creditCardNo< p->creditCardNo){//add new one in front of p
				creditCardNode*temp=new creditCardNode;
				temp->creditCardNo=creditCardNo;
				temp->next=p;
				ptr->cHead=temp;
				return;
			}
			else{
				while(p->next!=NULL && p->next->creditCardNo<creditCardNo){//search for the right place walking through p 
					p=p->next;
				}
				creditCardNode* temp=new creditCardNode;
				temp->creditCardNo=creditCardNo;
				//p->next=temp;
				temp->next=p->next;
				p->next=temp;
				return;
			}
		}
		else{
			ptr=ptr->next;//walk through ptr to find right expiration node for the new credit card
		}
	}
}

void CardList::displayListChronological (){
	expirationNode *p= head;//moving from the beginning of the linked list to end
	
	if (head!=NULL){
		
		int count=1;
		while(p!=NULL){
			creditCardNode *ptr=p->cHead;
			count=1;
			cout<< "Expiration date:" << p->month <<" " << p->year<<endl;
			while(ptr->next!=NULL){
				cout<<count<< ")"<< ptr->creditCardNo <<endl;
				count++;
				ptr=ptr->next;//move to the next respect to credit card no's
			}
			if(ptr->next==NULL){
				cout<<count<< ")"<< ptr->creditCardNo <<endl;//this is for the last node of creditcards
				cout<< "-------------------"<<endl;
			}
			p=p->next;//move to the next respect to expiration dates
		}
	}
	else if (head==NULL){
		cout<<endl;
		cout<< "List is empty!"<< endl;
	}
}

void CardList::displayListReverseChronological (){
	expirationNode *p= tail;//start from tail to have reverse

	if (tail!=NULL){
		
		int count=1;
		while(p!=NULL){
			creditCardNode *ptr=p->cHead;
			if(ptr!=NULL){
				count=1;
				cout<< "Expiration date:" << p->month <<" " << p->year<<endl;
				while(ptr->next!=NULL){
					cout<<count<< ")"<< ptr->creditCardNo <<endl;
					count++;
					ptr=ptr->next;//move to the next respect to credit card no's

				}
				if(ptr->next==NULL){
					cout<<count<< ")"<< ptr->creditCardNo <<endl;
					cout<< "-------------------"<<endl;
				}
				p=p->prev;//move to the next respect to expiration dates
			}
		}
	}
	else if (tail==NULL){
		cout<<endl;
		cout<< "List is empty!"<< endl;
	}
}

void CardList::cardSearch (string creditCardNo){
	expirationNode*p=head;
	
	int count=0;
	while(p!=NULL){
		creditCardNode *ptr=p->cHead;//moving in credit cards
		while(ptr!=NULL){
			
			if(ptr->creditCardNo!=creditCardNo){
				ptr=ptr->next;
			}
			else if(ptr->creditCardNo==creditCardNo){
				cout<< "There exists a credit card given number " << creditCardNo<< " with expiration date: "<<p->month<< " " << p->year<<endl;
				count=1;
				ptr=ptr->next;
				
			}
		}
		p=p->next;//since we can have the same credit no for different dates this move is happened the outside of the second while loop	
	}
	if(count==0){
		cout<<"There is no credit card with given credit card number: " <<creditCardNo<<endl;
	}
}

void CardList::bulkDelete (int month, int year){
	expirationNode*p=head;
	
	creditCardNode*temp;
	//bool found=false;
	if(head!=NULL){
		if((head->month>month && head->year==year)|| head->year>year)//if entered date is less than all of them
			cout<<"There is no card to be deleted!"<<endl;
		while(p!=NULL &&((p->month<=month && p->year==year)|| p->year<year)){//find the date is less or equal to entered date and see the cards in that dates
			creditCardNode*ptr=p->cHead;
			int count=1;
			//found=true;
			cout<<"Node with expiration date " << p->month << " " << p->year<< " and the following credit cards have been deleted!"<<endl;


			while(ptr!=NULL){//deleting cards one by one in that node
				cout<< count<< ")"<< ptr->creditCardNo<<endl;
				count++;
				temp=ptr->next;
				delete ptr;
				ptr=temp;
				p->cHead=ptr;
			}
			p=head->next;
			if(p!=NULL)
				p->prev=NULL;
			delete head;
			head=p;
			if(head==NULL)
				tail=NULL;
		}
	}
}

void CardList::deleteAll (){
	/* Begin: code taken from ptrfunc.cpp and updated */ 
	expirationNode *p=head;
	while(p!=NULL){//erase all nodes.
		creditCardNode*ptr=p->cHead;
		creditCardNode* temp;
		while(ptr!=NULL){
			temp=ptr->next;
			delete ptr;
			ptr=temp;
			p->cHead=ptr;
		}
		p=head->next;
		delete head;
		head=p;
	}
	head=NULL;//at the end they have to be equal to null
	tail=NULL;
}/* End: code taken from ptrfunc.cpp */

void CardList::changes(int monthval,int yearval,string creditcardid,CardList &the_list){
			
			bool distinct_date=true;
			bool existed_card=false;
			expirationNode* ptr=head;
			
			bool finish=false;
			while(ptr!=NULL && distinct_date){
				creditCardNode*p=ptr->cHead;
				if(monthval==ptr->month && yearval==ptr->year){//found the same date
					if(p==NULL){//if there is no card in that node
						the_list.insertCard(creditcardid,monthval,yearval);
						distinct_date=false;
					}
					while(p!=NULL&&!finish){//move through p to find out whether the card is added before or not
						if(p->creditCardNo==creditcardid){
							existed_card=true;
							finish=true;
							distinct_date=false;
						}
						else{
							p=p->next;//update p
						}
					}
					if(existed_card==false){//if it is not added before insert the card
						the_list.insertCard(creditcardid,monthval,yearval);
						distinct_date=false;
					}
				}
				else
					ptr=ptr->next;//update ptr if the date is not equal to the new one
			}
				
			if(distinct_date){//new date new node for doubly linked list
				the_list.ordered_doublylist(monthval,yearval,creditcardid);
			}
			if(distinct_date&& !existed_card){//these if-else statements are for the conclusion
				cout<< creditcardid<< " " << monthval << " " << yearval<< ": added to a new expiration date node "<<endl;
			}
			else if(!distinct_date&& existed_card){
				cout<< creditcardid<< " " << monthval << " " << yearval<<": this card was already inserted"<<endl;
			}
			else if(!distinct_date){
				cout<< creditcardid<< " " << monthval << " " << yearval<<": inserted to an existing expiration date node" <<endl;
			}


}

void CardList::ordered_doublylist(int month,int year,string creditcardid){
	/* Begin: code taken from ptrfunc.cpp and updated */
	expirationNode *ptr=head;
	if(head==NULL&&tail==NULL){//it means that the linked list is empty
		expirationNode*temp=new expirationNode(month,year,NULL,NULL,NULL);
		creditCardNode*p=new creditCardNode(creditcardid,NULL);
		temp->cHead=p;
		head=temp;
		head->prev=NULL;
		tail=head;
		tail->next=NULL;
	}
	else if(year<head->year ||( year==head->year && month< head->month)){//if it is wanted to be added as first because of its date value
		expirationNode*temp=new expirationNode(month,year,head,NULL,NULL);
		creditCardNode*p=new creditCardNode(creditcardid,NULL);
		temp->cHead=p;
		ptr->prev=temp;
		head=temp;
		head->prev=NULL;
	}
	else{
		while(ptr->next!=NULL &&(ptr->next->year<year || (ptr->next->year==year && ptr->next->month<month))){//search for the right place to insert the date node
			ptr=ptr->next;
		}
		expirationNode*temp=new expirationNode(month,year,ptr->next/*next*/,ptr/*prev*/,NULL);
		creditCardNode*p=new creditCardNode(creditcardid,NULL);
		temp->cHead=p;
		//temp->next=ptr->next;
		if(ptr->next!=NULL){
			ptr->next->prev=temp;
			ptr->next=temp;
	
		}
		else if (ptr->next==NULL){
			ptr->next=temp;
			tail=temp;//update tail if the newly added node is the last node of the linked list
		}

	}

}/* End: code taken from ptrfunc.cpp */
