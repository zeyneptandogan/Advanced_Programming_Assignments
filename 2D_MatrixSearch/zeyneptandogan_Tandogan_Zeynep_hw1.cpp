//Zeynep Tandogan

//This program searches for X's in the matrix in the file and evaluate whether the X's form a closed path or not. Before that, validty of the matrix.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>     // for setw
#include <vector>

using namespace std;

struct coordinates{//I use struct to store values
	int row;
	int col;
};

bool coordinateexistbefore(vector<coordinates> values, int upd_row,int upd_col){//checking whether the coordinate is seen before or not 
	for (int z=0;z<values.size();z++){
		if (values[z].row==upd_row && values[z].col==upd_col){
				return true;//it is seen before
		}
	}
	return false;//it is not seen before
}

bool isvalidnum(int startrow,int startcol,vector<vector<char>> formedmatrix){
	int limitrow=formedmatrix.size();
	int limitcol=formedmatrix[0].size();
	if(startrow<0 ||startrow>=limitrow|| startcol<0 ||startcol>=limitcol){
		return false;//entrances for startrow and startcol outside of the matrix
	}
	else 
		return true;//valid numbers for startrow and startcol

}

void writethecoordinates(vector<coordinates> values){
	for (int i=0;i<values.size();i++){
		cout<<values[i].row<< "\t" << values[i].col<<endl;
	}
}

void findingx(int rownum,int colnum,vector<vector<char>> formedmatrix){//following x function
	int startrow,startcol;
	bool continueasking=true;
	string error1, error2;//errors for having string entrances for startrow and startcol
	while(continueasking){
		cout<< "Please enter starting coordinates, first row X then column Y: " ;
		if (!(cin>>startrow>>startcol)){
			cout<<"Invalid Coordinates"<<endl;
			cin.clear();
			cin>>error1>>error2;//clearing error flags.
			continueasking=true;
			
		}
		else{
			if(startrow==-1 && startcol==-1){//end order as inputs
				cout<< "Terminating..."<<endl;
				continueasking=false;
			}
			else if (isvalidnum(startrow,startcol,formedmatrix)==false){//it is checked whether inputs are valid or not
				cout<<"Invalid Coordinates"<< endl;;
				continueasking=true;
			}
			else{
				int upd_row ,upd_col;
				vector<coordinates> values;
				
				if (formedmatrix[startrow][startcol]=='x'){
					upd_row=startrow;
					upd_col=startcol;
					coordinates s;//I use struct
					s.row=startrow;
					s.col=startcol;
					values.push_back(s);
					bool loopcont=true;
					int count=0;
					bool trytheother=false;
					bool finished=true;

					while(loopcont){
						 trytheother=true;
						 if((upd_col+1)<formedmatrix[0].size()){//in order to have the boundaries
							if ((formedmatrix[upd_row][upd_col+1]=='x'&&trytheother==true)/*&&(!(col1count==1||col2count==1))*/){
								upd_col=upd_col+1;
								if (coordinateexistbefore(values,upd_row,upd_col)==false){
									s.row=upd_row;
									s.col=upd_col;
									values.push_back(s);
									trytheother=false;//in order not to enter other if statements
								}	
								else{//if it is seen before,trytheother is true;it means other if statements will be tested as well.
									if(upd_col==startcol && upd_row==startrow&& values.size()!=2){//when value.size()==2 there is a possibility only two x's side by side.
										loopcont=false;//in order to finish the loop.
										cout<<"Found an enclosed area. The coordinates of the followed path: "<<endl;
										finished=false;
									}
									else{
										upd_col--;
										count++;
									}
								
								}

							}
						 }
						 if(upd_row+1<formedmatrix.size()){//in order to have the boundaries
							 if(formedmatrix[upd_row+1][upd_col]=='x'&&trytheother){
								upd_row=upd_row+1;
								if (coordinateexistbefore(values,upd_row,upd_col)==false){
									//colcount=0;
									s.row=upd_row;
									s.col=upd_col;
									values.push_back(s);
									trytheother=false;//in order not to enter other if statements
								}
								else{//if it is seen before,trytheother is true;it means other if statements will be tested as well.
									if(upd_row==startrow && upd_col==startcol&& values.size()!=2){
										loopcont=false;//in order to finish the loop.
										cout<<"Found an enclosed area. The coordinates of the followed path: "<<endl;
										finished=false;
									}
									else{
										upd_row--;//update row for the case the coordinate is seen before
										count++;
										
									}
								}
							 }
						 }
						 if(upd_col-1>=0){//in order to have the boundaries
							 if (formedmatrix[upd_row][upd_col-1]=='x'&&trytheother/*&&(!(col1count==1||col2count==1))*/){
								upd_col=upd_col-1;
								if (coordinateexistbefore(values,upd_row,upd_col)==false){
								
									s.row=upd_row;
									s.col=upd_col;
									values.push_back(s);
									trytheother=false;
								}
								else{
									if(upd_row==startrow && upd_col==startcol&& values.size()!=2){
										loopcont=false;
										cout<<"Found an enclosed area. The coordinates of the followed path: "<<endl;
										finished=false;
									}
									else{
										upd_col++;//update col for the case the coordinate is seen before
										count++;
									}
								
								}
							}
						 }
						 if(upd_row-1>=0){//in order to have the boundaries
							 if (formedmatrix[upd_row-1][upd_col]=='x'&& trytheother==true/*&&(!(row1count==1||row2count==1))*/){
								upd_row=upd_row-1;
								if (coordinateexistbefore(values,upd_row,upd_col)==false){
								
									s.row=upd_row;
									s.col=upd_col;
									values.push_back(s);
									trytheother=false;
								}
								else{
									if(upd_row==startrow && upd_col==startcol&& values.size()!=2){
										loopcont=false;
										cout<<"Found an enclosed area. The coordinates of the followed path: "<<endl;
										finished=false;
									}
									else{
										upd_row++;//update row for the case the coordinate is seen before
										count++;
									}

								}
						
							}
						 }
						if (trytheother==true)//it means it can not find any coordinate that has X and we can finish the loop
							loopcont=false;
					
					}
					 if (finished){//finished become false when we find closed area, if it is true it means we cannot find closed path
						 cout<< "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " <<endl;
					 } 
		
					writethecoordinates(values);//stored values for coordinates we find that they have x.

				}
			
			
				else if(formedmatrix[startrow][startcol]!='x'){//for the case if we dont have any x in the first side
					cout<<"This cell is not occupied!"<<endl;
					continueasking=true;//again ask new coordinates
				}
			}

	}
}
}


int main(){
	ifstream matrixfile;
	string matrixname;
	char ch;
	cout<<"Please enter file name:";
	cin>>matrixname;
	vector<vector<char>> formedmatrix;//empty matrix is formed
	string line;
	int invalid=0;

	matrixfile.open(matrixname.c_str());//open the file.

	while(matrixfile.fail()){//if it can not be opened.
		cout<<"Cannot find a file named " << matrixname<<endl;
		cout<<"Please enter file name:";//take the filename again
		cin>>matrixname;
		matrixfile.open(matrixname.c_str());
	}
	int count=0;
	if (!matrixfile.fail()){//if it is opened
		while(!matrixfile.eof()){//if the end of file is not reach, continue to read the file.
			getline(matrixfile,line);
			count++;// count of the line number 
			
			stringstream ss(line);
			char ch;
			vector<char> tempmat;//form temporary matrix for push_back

			while(ss>>ch){
				tempmat.push_back(ch);
			}
			formedmatrix.push_back(tempmat);// matrix in the file is carried to formedmatrix which was empty.
		}
		//cout<< count; count shows the row number
		int rownum= formedmatrix.size();//count;
		//int colnum= formedmatrix[0].size();

		bool rowcolequal=true;//bool is formed to test row-column variable amount is equal or not.
		for (int i=1; i< rownum;i++){
			if (formedmatrix[i-1].size()!=formedmatrix[i].size()){//compare the sizes of the columns after each other.
				rowcolequal=false;
				if (rowcolequal==false){
					cout<< matrixname << " is invalid matrix, does not contain same amount of char each row! "<<endl;//error when row-column not equal
					cin.get();
					cin.ignore();
					return 0;//finish here the program
				}
			}
		}
		rowcolequal=true;
		
	   if(rowcolequal==true){
		    
			int colnum=formedmatrix[0].size();//since col-row number are equal we can take one of the columns to take as colnum reference.
			//cout<< "Input matrix:"<< endl;
			for (int i=0;i< rownum; i++){
				for (int j=0;j< colnum;j++){
					if (formedmatrix[i][j]!='o'&&formedmatrix[i][j]!='x'){
						invalid=1;//it means there is an invalid char.
						
					}
					//cout<< formedmatrix[i][j] /*<<"\t"*/;
				}
			}
			if (invalid!=1){//if there is not invalid char,print the matrix.
				cout<< "Input matrix:"<< endl;

				for (int i=0;i< rownum; i++){
					for (int j=0;j< colnum;j++){
						cout<< setw(4)<<formedmatrix[i][j];
					}
					cout<<endl;
				}

			}
			else {//if invalid=1, it means there is an invalid char or chars.
				cout << matrixname<<" includes invalid char(s)"<<endl;
				cin.get();
				cin.ignore();
				return 0;//finish the program in this case here.
			}
			findingx(rownum,colnum,formedmatrix);

		}
	}
cin.get();
cin.ignore();
 return 0;
}