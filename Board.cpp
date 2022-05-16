#include "Board.h"
#include <unordered_map>
#include <random>

Board::Board(int given_size)
{
    size = given_size;
    //Initiualize the board with the random values between 1 and 5
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

//make all rows available for swapping
void Board::initializeRowsState()
{
    for(int i = 0; i < size; i++)
        rowsStates.push_back(1);
}

//check if the swap movement could be done
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

//swap adjacent cells with positions
bool Board::swapAdjacentCells(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition)
{
    bool check = isSwapValid(firstRowPosition, firstColumnPosition, secondRowPosition, secondColumnPosition);

    if(check)
        swap(gameBoard[firstRowPosition][firstColumnPosition], gameBoard[secondRowPosition][secondColumnPosition]);

    return check;
}

//swap cells with direction provided
bool Board::swapAdjacentCellsWithDirection(int firstRowPosition, int firstColumnPosition, string direction)
{
    bool result = false;
    if(firstRowPosition>=0 && firstRowPosition< size)
    {
        if(firstColumnPosition>=0 && firstColumnPosition<size)
        {
           result = checkDirection(firstRowPosition,firstColumnPosition, direction);
           if (result)
           {
                if(direction == "up")
                    result = swapAdjacentCells(firstRowPosition,firstColumnPosition, firstRowPosition-1, firstColumnPosition);
                else if (direction == "down")
                    result = swapAdjacentCells(firstRowPosition,firstColumnPosition, firstRowPosition+1, firstColumnPosition);
                else if (direction == "left")
                    result = swapAdjacentCells(firstRowPosition,firstColumnPosition, firstRowPosition, firstColumnPosition-1);
                else if (direction == "right")
                    result = swapAdjacentCells(firstRowPosition,firstColumnPosition, firstRowPosition, firstColumnPosition+1);
           }  
        }
    }
    return result;
}

//check if direction is valid
bool Board::checkDirection(int firstRowPosition, int firstColumnPosition, string direction)
{
    bool result = true;

    if(direction == "up" && firstRowPosition == 0)
        result = false;
    else if(direction == "down" && firstRowPosition == size-1)
        result = false;
    else if(direction == "left" && firstColumnPosition == 0)
        result = false;
    else if(direction == "right" && firstColumnPosition == size-1)
        result = false;

    return result;
}

//check if there are enough numbers to form a shape
bool Board::checkShape()
{
    unordered_map<int,int> check;
    int max = -1, id = 0;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if (check[gameBoard[i][j]])
                check[gameBoard[i][j]]++;
            else
                check[gameBoard[i][j]] = 1;
        }
    }
    for(auto& it:check)
    {
        if (max < it.second)
        {
            max = it.second;
            id = it.first;
        }
    }
    if (max >= size/2)
        return true;
    else
        return false;
}

//TODO: check if shapeL is there
bool Board::isShapeL()
{
    // should call check shape and see what's the dominant number of occurances then check if they form L shape
    return false;
}

//TODO: check if shapeT is there
bool Board::isShapeT()
{
    // should call check shape and see what's the dominant number of occurances then check if they form T shape
    return false;
}

//Check if row is valid to perform swap on for later stages at the game
bool Board::isRowValid(int rowIndex)
{
    return rowsStates[rowIndex];
}

//Check disable row for further development of the game 
void Board::deleteRow(int rowIndex)
{
    rowsStates[rowIndex] = 0;
}