#include <iostream>
#include "board.h"
#include <string>
using namespace std;

void playGame(Board newGame)
{
    int firstRow, firstColumn, secondRow, secondColumn, decision;
    string direction;
    do
    {
        cout<<"Do you want to swap with positions or directions? 1/2"<<endl;

        cin>>decision;

        if(decision == 1)
        {
            cout<<"Please enter 2 positions 0 based"<<endl;
            cin>>firstRow>>firstColumn>>secondRow>>secondColumn;

            if(newGame.swapAdjacentCells(firstRow,firstColumn,secondRow,secondColumn))
                cout<<"Swapped!"<<endl;
            else
                cout<<"Illegal Move!"<<endl;
        }
        else if(decision == 2)
        {
            cout<<"Please enter the position of cells zero based and direction"<<endl;

            cin>>firstRow>>firstColumn>>direction;            

            if(newGame.swapAdjacentCellsWithDirection(firstRow,firstColumn,direction))
                cout<<"Swapped!"<<endl;
            else
                cout<<"Illegal Move!"<<endl;
        }

        newGame.printBoard();

        cout<<endl<<endl;

        cout<<"Current Score: "<<newGame.score<<endl;

        newGame.numberOfMovesLeft--;

    } while (newGame.numberOfMovesLeft > 0 && newGame.checkMoves());
}

int main()
{
    string choice;
    int size,movesCount;

    do {

        cout<<"Welcome to diamonds hunt! please give the size of the board"<<endl;

        cin>>size;

        cout<<"How many moves do you want to have for this game?"<<endl;

        cin>>movesCount;

        Board newGame(size, movesCount);

        newGame.printBoard();

        cout<<endl<<endl;

        playGame(newGame);

        cout<<"do you wanna play again?"<<endl;

        cin>>choice;

    } while( choice == "yes");

	return 0;
}
