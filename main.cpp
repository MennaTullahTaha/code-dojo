#include <iostream>
#include "board.h"
#include <string>
using namespace std;

void playGame(Board newGame)
{
    int firstRow, firstColumn, secondRow, secondColumn, decision;
    string direction, keepPlaying;
    do
    {
        cout<<"Do you want to swap with positions or directions? 1/2"<<endl;

        cin>>decision;

        if(decision ==1)
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

        cout<<"Do you want to keep playing?"<<endl;

        cin>>keepPlaying;

    } while (keepPlaying == "yes");
}

int main()
{
    string choice;
    int size;

    do {

        cout<<"Welcome to diamonds hunt! please give the size of the board"<<endl;

        cin>>size;

        Board newGame(size);

        newGame.printBoard();

        cout<<endl<<endl;

        playGame(newGame);

        cout<<"do you wanna continue?"<<endl;

        cin>>choice;

    } while( choice == "yes");

	return 0;
}
