//Zeynep Tandogan 25200

#include<iostream>
#include <string>
using namespace std;
char permutation_function(char ch){

	unsigned char a= ch & (1<<7);//1000000 to get the 7th bit value
	a= (a>>2); //shift operation right

	unsigned char b= ch & (1<<6);//01000000 to get the 6th bit value
	b=(b<<1); //shift operation left

	unsigned char c=ch & (1<<5);//00100000 to get the 5th bit value
	c=(c>>1);

	unsigned char d=ch & (1<<4);//00010000 to get the 4th bit value
	d=(d<<2);

	unsigned char e=ch & (1<<3);//00001000 to get the 3rd bit value
	e=(e>>2);

	unsigned char f=ch & (1<<2);//00000100 to get the 2th bit value
	f=(f<<1);

	unsigned char g=ch & (1<<1);//00000010 to get the 1th bit value
	g=(g>>1);

	unsigned char h=ch & (1);//00000001 to get the 0th bit value
	h=(h<<2);

	unsigned char permutated_result= (a|b)|(c|d)|(e|f)|(g|h) ;
	return permutated_result;
}

int main()
{
	cout<<"*** Welcome to the Simple Data Encryption Application ***"<<endl;
	string key;
	cout<<"Please enter the encryption key:";
	getline(cin,key);
	int length_key=key.length();
	string plaintext;
	cout<<"Please enter the plaintext to be encrypted: ";
	while(getline(cin,plaintext)){//while getting plaintext, the loop will continue
		unsigned char ch,result_p,result_final;
		unsigned char currentkey_Ch;

		int length_plaintext=plaintext.length();
		for (int i=0;i<length_plaintext;i++){
			ch=plaintext.at(i);//by using .at i reach the char
			currentkey_Ch=key.at(i%length_key);// to get the key char that corresponds to the char from plaintext by using modulus i provide repetition of key
			result_p=permutation_function(ch);
			result_final=currentkey_Ch ^ result_p;//use XOR to achieve the result.
			if(i==0)//for putting ciphertext at the beginning
				cout << "Ciphertext: "<< hex << (int) result_final;
			else if(i!=length_plaintext-1)//if it is not the last char of the plaintext
				cout << hex << (int) result_final;
			
			else if(i==length_plaintext-1)//if it is the last char of the plaintext
				cout << hex << (int) result_final<<endl;
		}
		cout<<endl;
		cout<<"Please enter the plaintext to be encrypted: ";//while loop continues, continue to ask.

	}


	return 0;
}