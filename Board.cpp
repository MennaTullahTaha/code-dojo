#include "Board.h"
#include <random>

Board::Board(int given_size)
{
    //Initiualize the board with the given values from exam
    size = given_size;
    initializeBoard(given_size);
    initializeRowsState();
}

Board::~Board()
{
}

void Board::printBoard()
{
    vector<vector<int>> board = getBoard();
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(j!= size-1)
                cout<<board[i][j]<<" ";
            else
                cout<<board[i][j]<<endl;
}

vector<vector<int> > Board::getBoard()
{
    return gameBoard;
}

void Board::initializeBoard(int size)
{
    for(int i = 0; i < size; i++)
        gameBoard.push_back(vector<int>(size));
    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            gameBoard[i][j] = rand() % 5 + 1;
}

void Board::initializeRowsState()
{
    for(int i = 0; i < size; i++)
        rowsStates.push_back(1);
}

bool Board::isSwapValid(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition)
{
    if(firstRowPosition >= 0 && firstRowPosition < size)
    {
        if(firstColumnPosition>=0 && firstColumnPosition < size)
        {
            if(secondRowPosition>=0 && secondRowPosition<size)
            {
                if(secondColumnPosition>=0 && secondColumnPosition<size)
                {
                    if(abs(secondRowPosition-firstRowPosition) <= 1 && abs(secondColumnPosition - firstColumnPosition) <= 1)
                        return true;
                }
            }
        }
    }
    return false;
}

bool Board::swapAdjacentCells(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition)
{
    bool check = isSwapValid(firstRowPosition, firstColumnPosition, secondRowPosition, secondColumnPosition);

    if(check)
        swap(gameBoard[firstRowPosition][firstColumnPosition], gameBoard[secondRowPosition][secondColumnPosition]);

    return check;
}

bool Board::isRowValid(int rowIndex)
{
    return rowsStates[rowIndex];
}

void Board::deleteRow(int rowIndex)
{
    rowsStates[rowIndex] = 0;
}