//Zeynep Tandogan 25200
#include "zeyneptandogan_Tandogan_Zeynep_hw6_Board.h"
#include <iostream>

using namespace std;

Board::Board(){//default constructor
	for (int a=0;a<2;a++){
		for (int b=0;b<6;b++){
			theBoard[a][b]='-';//filling the empty matrix with char '-' 
		}
	}
}

void Board::displayBoard() const{
	for (int j=0;j<2;j++){
		for (int i=0;i<6;i++){
			cout<< theBoard[j][i]<<" ";//printing the board
		}
		cout<<endl;
	}
}

char Board::getOwner(int row_val,int col_val){
	//learning the owner of the place
	if (theBoard[row_val][col_val]=='-')
		return '-';
	else if(theBoard[row_val][col_val]=='A')
		return 'A';
	else if(theBoard[row_val][col_val]=='B')
		return 'B';
}

void Board::setOwner(int row_val ,int col_val ,char id){
	if (theBoard[row_val][col_val]=='-')
		theBoard[row_val][col_val]=id;//putting the char that arrive this location
}

bool Board::isFull()const{
	for (int i=0;i<2;i++){
		for (int j=0;j<6;j++){
			if(theBoard[i][j]=='-')//if there is an empty place it means it does not finish return false
				return false;
		}
	}
	return true;//it is full
}

int Board::countOwnedCells(char id){
	int count=0;
	for (int i=0;i<2;i++){
		for (int j=0;j<6;j++){
			if(theBoard[i][j]==id)//the number of places that belong to the char is counted with count, at the end return count
				count++;
		}
	}
	return count;
}

