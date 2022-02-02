//Zeynep Tandogan 25200
#include <iostream>
#include "zeyneptandogan_Tandogan_Zeynep_hw6_Board.h"
using namespace std;

class Player{
public:
	Player(Board & myboard, char id, int dir);//parametric constructor
	void move(int);
	void claimOwnership();
	bool wins() const;
	int getRow();
	int getCol();
private:
	char player_id;
	Board &board;
	int direction;
	int row;
	int col;
};