#include <iostream>
#include "Board.h"
#include <string>
using namespace std;
int main()
{
    cout<<"Please enter the size of the board"<<endl; 

    int size, first_row, first_column, second_row, second_column;
    string direction;

    cin>>size;

    Board new_game(size);

    new_game.printBoard();

    cout<<"---------------------"<<endl;

    cout<<"Please enter the position of cells zero based"<<endl;

    cin>>first_row>>first_column>>second_row>>second_column;

    if(new_game.swapAdjacentCells(first_row,first_column,second_row,second_column))
        cout<<"Swapped!"<<endl;
    else
        cout<<"Illegal Move!"<<endl;

    new_game.printBoard();

    cout<<"-------------------------"<<endl;

    cout<<"Please enter the position of cells zero based and direction"<<endl;

    cin>>first_row>>first_column;
    //TODO: check if direction is entered correctly by the user and in lower case
    cin>>direction;

    if(new_game.swapAdjacentCellsWithDirection(first_row,first_column,direction))
        cout<<"Swapped!"<<endl;
    else
        cout<<"Illegal Move!"<<endl;

    new_game.printBoard();

    cout<<"-----------------------------"<<endl;

	return 0;
}
