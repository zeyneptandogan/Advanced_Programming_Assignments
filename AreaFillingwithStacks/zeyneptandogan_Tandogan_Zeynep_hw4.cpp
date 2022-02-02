//Zeynep Tandogan- 25200

//this program is designed to find empty neighboring coordinates that an empty coordinate entered by user and fill with the entered char at the end show the resulting matrix 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include "fill_empty.h"
using namespace std;

void delete_matrix(char **matrix,int int_row){//deleting the matrix 
	/* Begin: code taken from matrix.cpp and updated*/
	
	for(int i=0; i<int_row; i++){
		delete [] matrix[i];//delete the matrix 
	}
	delete [] matrix;//delete the location

	/* End: code taken from matrix.cpp*/
}

bool isvalid_val(string num){
	int int_num;
	int_num=atoi(num);//convert string num to integer
	if(int_num>=3){//the value of row and column must be higher or equal to three.if that satisfies, return true;otherwise false.
		return true;
	}
	else
		return false;
}
bool isvalid_coor(string num,string numcontrol ){
	int int_num=atoi(num);
	int int_numcontrol=atoi(numcontrol);
	if (num <"0" ||num>"9")//if it is not a number
		return false;
	else if(int_num>=int_numcontrol)//if the entered one is bigger than the existed number in matrix.
		return false;
	return true;
}

void searching_for_Empty(char **matrix,int startrow,int startcol,char fill_char, fill_empty &stack,int int_row,int int_col){
	//take stack as reference in order not to have an issue with shallow copy, if it destructs the original one will be gone at the same time
	//this function is to find empty place and fill it with the entered char for filling, and designing the stack.
	int upd_row=startrow;
	int upd_col=startcol;
	bool tryagain=true;//i created a bool to control that while loop if tryagain false which shows that stack is empty from that position.
	while(tryagain){
		
		if (upd_row+1<int_row && matrix[upd_row+1][upd_col]==' '){//looking below
			upd_row+=1;
			stack.push(upd_row,upd_col);
			matrix[upd_row][upd_col]=fill_char;
		}
		else if(upd_col+1<int_col && matrix[upd_row][upd_col+1]==' '){//looking right
			upd_col+=1;
			stack.push(upd_row,upd_col);
			matrix[upd_row][upd_col]=fill_char;
		}
		else if (upd_row-1>=0 && matrix[upd_row-1][upd_col]==' '){//looking above
			upd_row-=1;
			stack.push(upd_row,upd_col);
			matrix[upd_row][upd_col]=fill_char;
		}
		else if(upd_col-1>=0 && matrix[upd_row][upd_col-1]==' '){//looking left
			upd_col-=1;
			stack.push(upd_row,upd_col);
			matrix[upd_row][upd_col]=fill_char;
		}
		else{
			if(!stack.isEmpty()){
			//after every pop,if the first element isnt arrived (stack is empty),check every element's below,above,left and right parts not to miss any empty part
				stack.pop(upd_row,upd_col);
				tryagain=true;
			}
			else
				tryagain=false;//stack is empty now

			if(tryagain==false){
				
				for (int i=0;i<int_row;i++){//these for loops for printing the resulted matrix
					for (int z=0;z<int_col;z++){
						cout<<matrix[i][z];
					}
					cout<<endl;
				}
			}
		}
	}
}

int main(){
	string filename;
	ifstream input_file;
	string num_row,num_col;
	cout<<"Enter the number of rows: " ;
	cin>>num_row;
	while(!isvalid_val(num_row)){//if the validity of row isnot okay make the user enter again a value
		cout<< num_row<< " is not valid!"<< endl;
		cout<<"Enter the number of rows: " ;
		cin>>num_row;
	}
	cout<< "Enter the number of columns: ";
	cin>>num_col;

	while(!isvalid_val(num_col)){//if the validity of column isnot okay make the user enter again a value
		cout<< num_col<< " is not valid!"<< endl;
		cout<<"Enter the number of columns: " ;
		cin>>num_col;
	}
	cout<<"Please enter file name: ";
	cin>>filename;
	input_file.open(filename.c_str());
	while(input_file.fail()){//if the file does not exist take a new filename until a valid filename
		cout<<"Cannot open a file named " << filename<<endl;
		cout<<"Please enter file name: ";
		cin>>filename;
		input_file.open(filename.c_str());
	}

	//forming the matrix

	int int_row=atoi(num_row);
	int int_col=atoi(num_col);
	string line,line1;
	char ** matrix;//pointer to pointer
	int count=0;
			
	matrix=new char* [int_row];//every row will point another pointer to have columns thats why it is a pointer.
	for (int p=0;p<int_row;p++){
		matrix[p]=new char [int_col];//matrix is formed.
	}
	string letter="";
	while(getline(input_file,line)){//read line by line 
		for (int j=0;j<int_col;j++ ){
			matrix[count][j]=line[j];//store it in the pointer to pointer char matrix
		}
		count++;//increment the count which represent the row value
	}
	bool continueask=true;
	while(continueask){
		string start_row,start_col;
		cout<<"Enter the starting point: ";
		cin>>start_row>>start_col;
		if(!(isvalid_coor(start_row,num_row)&&isvalid_coor(start_col,num_col))){//if that values are not valid for the matrix ask again for starting point
			cout<<"Invalid coordinate!"<<endl;
		}
		else{
			continueask=false;
			int startrow=atoi(start_row);
			int startcol=atoi(start_col);
			if(matrix[startrow][startcol]=='X'){
				cout<<"Starting point is already occupied.\nTerminating...";
				delete_matrix(matrix,int_row);
				cin.get();
				cin.ignore();
				return 0;
			}
			else {
				bool isnot_valid=true;
				while(isnot_valid){
					char fill_char;
					cout<<"Enter the filling char: " ;
					cin>>fill_char;
					if (fill_char=='X' || fill_char=='x'){//the filling char cannot be x or X
						cout<<"Filling char is not valid!"<<endl;
					}
					else{
						isnot_valid=false;
						fill_empty stack;//form the stack, push the first value and fill that location with that char
						stack.push(startrow,startcol);
						matrix[startrow][startcol]=fill_char;
						searching_for_Empty(matrix,startrow,startcol,fill_char,stack,int_row,int_col);//call the function for finding empty neighboring places
						delete_matrix(matrix,int_row);
					}
				}
			}
		}
	}

	
	cin.get();
	cin.ignore();
	return 0;
}
