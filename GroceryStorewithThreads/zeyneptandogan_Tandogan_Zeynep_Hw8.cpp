//Zeynep Tandogan 25200
#include <iostream>
#include <time.h>
#include <random>
#include <thread>
#include <mutex>
#include <ctime>  
#include <chrono>
#include <iomanip>
#include "zeyneptandogan_Tandogan_Zeynep_queue.h"
using namespace std;

mutex general_mutex,currentcountmutex,cout_mutex;//mutexes for shared parts of threads
int total_customer_count;//in order to be able to use them easier i choose to make them global
int cashier2_threshold;
HW8DynIntQueue queue;
int currentcount=0;//in order not to have any problem in cashier function in terms of counting current number of customers that taking transaction

int random_range(const int & min, const int & max) {  //for random time 
	static mt19937 generator(time(0));   
	uniform_int_distribution<int> distribution(min, max);    
	return distribution(generator); 
}

void customer(int min_arrival,int max_arrival){
	for(int i=1;i<=total_customer_count;i++){//for every customer
		general_mutex.lock();//we have to lock this part by general mutex,i formed this mutex for dequeuing and enqueuing parts
		queue.enqueue(i);
		int currentsize=queue.getCurrentSize();//it should be stored because it might change while threads are working.
		general_mutex.unlock();

		cout_mutex.lock();//this mutex is for cout statement in order not to have complicated and wrong order in the result
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt); 
		cout <<"New customer with ID "<< i<<"has arrived (queue size is "<< currentsize<<"): "<< put_time(ptm,"%X") <<endl;
		cout_mutex.unlock();
		//sleep_time between the customer arrivals
		int time_in_seconds=random_range(min_arrival, max_arrival);
		this_thread::sleep_for(chrono::seconds(time_in_seconds));
	}

}
void cashier(int cashier_no,int min_checkout_time,int max_checkout_time){
	int time_in_seconds=random_range(min_checkout_time, max_checkout_time);//first sleep for the cashier before work
	this_thread::sleep_for(chrono::seconds(time_in_seconds));
	bool continue_cashier=true;//this is for the second cashier issue
	int num;
	//int count=0;

	currentcountmutex.lock();
	while(currentcount<total_customer_count){
		// we have to put conditions for second cashier since it should not work if the customer number in queue less than threshold
		if(cashier_no==2){
			general_mutex.lock();//again we have to use general mutex since we get queue's current size in these lines 
			int current_size=queue.getCurrentSize();
			if(current_size<cashier2_threshold)//checking the condition if it does not satisfy continue to operation 
				continue_cashier=false;
			else
				continue_cashier=true;
			general_mutex.unlock();
		}
		if(continue_cashier){
			general_mutex.lock();//first we have to lock general mutex to avoid any complication
			if(queue.getCurrentSize()!=0){//if the queue is not empty
				queue.dequeue(num);	
				int currentsize=queue.getCurrentSize();
				currentcount++;
				currentcountmutex.unlock();
				general_mutex.unlock();//we can unlock it since we do everything we should do in it "dequeuing"
				cout_mutex.lock();//for cout statement
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt);
				cout<< "Cashier " <<cashier_no<<" started transaction with customer "<<num<<" (queue size is "<<currentsize<<"):"<< put_time(ptm,"%X") <<endl;
				cout_mutex.unlock();

				//sleep for transaction
				int time_in_seconds_2=random_range(min_checkout_time, max_checkout_time);
				this_thread::sleep_for(chrono::seconds(time_in_seconds_2));			
				cout_mutex.lock();//we have to lock the mutex for this cout statement 
				time_t tt2 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm2 = new struct tm; 
				localtime_s(ptm2, &tt2);
				cout<<"Cashier "<<cashier_no<<" finished transaction with customer "<<num<<" "<<put_time(ptm2,"%X") <<endl; 
				cout_mutex.unlock();
				currentcountmutex.lock();
			}
			else
				general_mutex.unlock();//since i lock it before if i have to unlock it for the condition that if it does not enter if statement
		}

		currentcountmutex.unlock();//this is the preparation for while loop,since it will come back to the beginning it should be locked again 
		currentcountmutex.lock();
	}
	currentcountmutex.unlock();//i lock it before entering the while loop,it should be unlocked 
}
int main(){

	//taking inputs from the user 
	cout<< "Please enter the total number of customers: ";
	cin>>total_customer_count;	

	cout<<"Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin>>cashier2_threshold;
	int min_arrival,max_arrival,min_checkout_time,max_checkout_time;
	cout<<"Please enter the inter-arrival time range between two customers: "<<endl;
	cout<<"Min: " ;
	cin>>min_arrival;
	cout<<"Max: ";
	cin>>max_arrival;

	cout<<"Please enter the checkout time range of cashiers: "<<endl;
	cout<<"Min: " ;
	cin>>min_checkout_time;
	cout<<"Max: ";
	cin>>max_checkout_time;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout<<"Simulation starts "<<put_time(ptm,"%X")<<endl;//getting the current time 

	//creating three threads one for customer other two for cashier
	thread thr0(customer,min_arrival,max_arrival);
	thread thr1(cashier,1,min_checkout_time,max_checkout_time);//1 and 2 expresses their id's
	thread thr2(cashier,2,min_checkout_time,max_checkout_time);

	//they should be joined 
	thr0.join();
	thr1.join();
	thr2.join();
	time_t tt2 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm2 = new struct tm; 
	localtime_s(ptm2, &tt2); 
	cout<<"End of the simulation ends: "<<put_time(ptm2,"%X")<<endl;//for the end of the program
	
	return 0;
}