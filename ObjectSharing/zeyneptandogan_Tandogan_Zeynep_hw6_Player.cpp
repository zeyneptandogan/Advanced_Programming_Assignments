//Zeynep Tandogan 25200
#include <iostream>
#include "zeyneptandogan_Tandogan_Zeynep_hw6_Board.h"
#include "zeyneptandogan_Tandogan_Zeynep_hw6_Player.h"
using namespace std;

Player::Player(Board &myboard, char id, int dir)//parametric constructor
	:board(myboard),player_id(id),direction(dir)
{ 
	row=0;//initialization for row and col
	col=0;
};

void Player::move(int value){
	int left=0;
	if (direction==1){//if char A is playing
		if(row==0){
			left=5-col;//with left ý denoted the number of places at that row
			if(value>left){//if value is higher than left it should turn the corner and arrive row 1.
				row=1;
				col=6-(value-left);//since it takes column values in reverse order,the column value that it takes will equal to this.
			}
			else 
				col=col+value;	//if it should stay at the same row just increase col since it is clockwise
			
		}
		else if(row==1){//this part is designed with the same logic with the above part. 
			left=col;
			if(value>left){
				row=0;
				col=(value-left)-1;//it turns the corner and start taking values from 0 to 5 for col.
			}
			else
				col=col-value;//if it should stay at the same row just decrease col since it is clockwise
			
		}

	}
	else if(direction==0){//if char b is playing
	//the same things with direction==1 but direction 1'move for row 1 in this row 0, row 0 in this row 1. Because it moves counter clockwise
		if(row==0){
			left=col;
			if(value>left){
				row=1;
				col=value-left-1;//it turns the corner and start taking values from 0 to 5 for col.
			}
			else 
				col=col-value;//if it should stay at the same row just decrease col since it is counterclockwise
			
		}
		else if(row==1){
			left=6-col-1;
			if(value>left){
				row=0;
				col=6-(value-left);//it turns the corner and start taking values from 5 to 0 for col.
			}
			else
				col=col+value;//if it should stay at the same row just increase col since it is counterclockwise
			
		}

	}
}

void Player::claimOwnership(){
	if (board.getOwner(row,col)=='-'){
		board.setOwner(row,col,player_id);
	}
}

bool Player::wins() const{
	if(board.countOwnedCells(player_id)==7){//the one that takes 7 places get the play.
		return true;
	}
	return false;
}
int Player::getRow(){//learning row value
	return row;
}

int Player::getCol(){//learning col value
	return col;
}

