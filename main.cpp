#include <iostream>
#include "Board.h"
using namespace std;
int main()
{
    Board new_game;
    new_game.printBoard();
    new_game.swapAdjacentCells(2,2,1,2);
    new_game.printBoard();
	return 0;
}
