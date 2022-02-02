//Zeynep Tandogan 25200
#ifndef ZEYNEPTANDOGAN_TANDOGAN_ZEYNEP_HW6_BOARD_H
#define ZEYNEPTANDOGAN_TANDOGAN_ZEYNEP_HW6_BOARD_H
#include <iostream>
using namespace std;

class Board{
public:
	Board();//default constructor
	void displayBoard() const;
	char getOwner(int,int);
	void setOwner(int,int,char);
	bool isFull()const;
	int countOwnedCells(char);
private:
	char theBoard[2][6];
};
#endif