#include "Board.h"

Board::Board()
{
    //Initiualize the board with the given values from exam
    initializeBoard();
    initializeRowsState();
}

Board::~Board()
{
}

void Board::printBoard()
{
    vector<vector<int>> board = getBoard();
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(j!= 2)
                cout<<board[i][j]<<" ";
            else
                cout<<board[i][j]<<endl;
}

vector<vector<int> > Board::getBoard()
{
    return gameBoard;
}

void Board::initializeBoard()
{
    for(int i = 0; i < 3; i++)
    {
        gameBoard.push_back(vector<int>(3));
        gameBoard[0][i] = i+1;
    }
    
    gameBoard[1][0] = 4;
    gameBoard[1][1] = 4;
    gameBoard[1][2] = 5;
    
    gameBoard[2][0] = 5;
    gameBoard[2][1] = 3;
    gameBoard[2][2] = 4;
}

void Board::initializeRowsState()
{
    for(int i = 0; i < 3; i++)
        rowsStates[i] = 1;
}