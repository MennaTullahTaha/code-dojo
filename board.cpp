#include "board.h"
#include <unordered_map>
#include <random>

Board::Board(int given_size, int moves)
{
    size = given_size;
    numberOfMovesLeft = moves;
    score = 0;
    //Initiualize the board with the random values between 1 and 5
    initializeBoard(given_size);
}

Board::~Board()
{
}

void Board::printBoard()
{
    vector<vector<int>> board = getBoard();
    for(int i = 0; i < size; i++)
    {
        cout<<"Row "<<i<<"  ";
        for(int j = 0; j < size; j++)
            if(j!= size-1)
                cout<<board[i][j]<<"    ";
            else
                cout<<board[i][j]<<endl;
        cout<<endl;
    }
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

void Board::checkForSameGemsRows()
{
    int currentGem, counter, endColumn = -1;
    for(int i = 0; i < size; i++)
    {       
        for(int j = 0; j < size; j++)
        {
            counter = 1;
            for(int k = j+1; k < size; k++)
            {
                if(gameBoard[i][j] == gameBoard[i][k])
                {
                    counter++;
                    endColumn = k;
                }    
                else
                {
                    endColumn = k-1;
                    break;
                }
            }
            if (counter >=3)
            {
                removeGemsFromRow(i,j,endColumn);
                score+=(counter * 5);
            }
        }
    }
}

void Board::removeGemsFromRow(int row, int startColumn, int endColumn)
{
    for(int i = startColumn; i <= endColumn; i++)
        gameBoard[row][i] = -1;
}

void Board::refillGems()
{
    checkForSameGemsRows();

    checkForSameGemsColumn();

    for(int i = size-1; i >= 0; i--)
    {
        for(int k = 0; k < size; k++)
            if(gameBoard[i][k] == -1)
                populateGemsFromRowsAbove(i,k);
    }
   
}

void Board::checkForSameGemsColumn()
{
    int currentGem, counter, endRow;
    for(int i = 0; i < size; i++)
    {       
        for(int j = 0; j < size; j++)
        {
            counter = 1;
            for(int k = j+1; k < size; k++)
            {
                if(gameBoard[j][i] == gameBoard[k][i])
                {
                    counter++;
                    endRow = k;
                }    
                else
                {
                    endRow = k-1;
                    break;
                }
            }
            if (counter >=3)
            {
                removeGemsFromColumn(j,i,endRow);
                score += (counter*5);
            }
        }
    }
}

void Board::removeGemsFromColumn(int startRow, int column, int endRow)
{
    for(int i = startRow; i <= endRow; i++)
        gameBoard[i][column] = -1;
}

void Board::populateGemsFromRowsAbove(int row, int column)
{
    for(int i = 0; i < size-1 ; i++)
    {
        if(gameBoard[i+1][column] ==-1 && gameBoard[i][column]!= -1)
        {
            gameBoard[i+1][column]  = gameBoard[i][column];
            gameBoard[i][column] = rand() % 5 + 1;
        }
    }

    for(int i = 0; i < size; i++)
        if(gameBoard[0][i] == -1)
            gameBoard[0][i] = rand() % 5 + 1;
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
    {
        swap(gameBoard[firstRowPosition][firstColumnPosition], gameBoard[secondRowPosition][secondColumnPosition]);
        if(checkShape())
        {
            cout<<"Special bomb found!! you get a bonus of 50 points!"<<endl;
            score += 50;
        }
        refillGems();
    }

    return check;
}

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

bool Board::checkShape()
{
    return checkShapeHorziontally() || checkShapeVeritically();
}

bool Board::checkShapeHorziontally()
{
    int counter , endColumn;

    for(int i = 0; i < size ; i++)
    {
        for(int j =0 ; j < size; j++)
        {
            counter = 1;
            for(int k = j+1; k < size; k++)
            {
                if(gameBoard[i][j] == gameBoard[i][k])
                {
                    counter++;
                    endColumn = k;
                }    
                else
                {
                    endColumn = k-1;
                    break;
                }
            }
                
            if(counter >= 3)
                if(isShapeLVertically(i,j,endColumn,gameBoard[i][j]) || isShapeTVertically(i,j,endColumn,gameBoard[i][j]))
                    return true;
        }
    }
    return false;
}

bool Board::checkShapeVeritically()
{
    int counter, endRow;

    for(int i = 0; i < size ; i++)
    {
        for(int j =0 ; j < size; j++)
        {
            counter = 1;
            for(int k = j+1; k < size; k++)
            {
                if(gameBoard[k][i] == gameBoard[j][i])
                {
                    counter++;
                    endRow = k;
                }    
                else
                {
                    endRow = k-1;
                    break;
                }
            }
                if(counter >= 3)
                    if(isShapeLHorziontally(i, j, endRow, gameBoard[endRow][i]) || isShapeTHorziontally(i,j,endRow,gameBoard[j][i]))
                        return true;         
        }
    }
    return false;
}

bool Board::isShapeLVertically(int rowId, int start, int end,  int gemType)
{
    int rightCounter = 0, leftCounter = 0;
    for(int i = rowId+1; i < size; i++)
    {
        if(gameBoard[i][start] == gemType)
            rightCounter++;
        else if (gameBoard[i][end] == gemType)
            leftCounter++;
        else
        {
            if (rightCounter >= 2 || leftCounter >= 2)
                return true;
            else
                break;
        }
    }

    rightCounter = 0, leftCounter = 0;
    for(int i = rowId-1; i >= 0 ; i--)
    {
        if(gameBoard[i][start] == gemType)
            rightCounter++;
        else if (gameBoard[i][end] == gemType)
            leftCounter++;
        else
        {
            if (rightCounter >= 2 || leftCounter >= 2)
                return true;
            else
                break;
        }
    }
    return false;
}

bool Board::isShapeTVertically(int rowId, int start,int end, int gemType)
{
    if((end - start + 1)%2 == 0)
        return false;
    int column = (end - start + 1)/2 + start , counter = 0;
    for(int i = rowId+1; i < size; i++)
    {
        if(gameBoard[i][column] == gemType)
            counter++;
        else
        {   
            if (counter >= 2)
                return true;
            else
                break;
        }
    }
    counter = 0;
    for(int i = rowId-1; i >= 0; i--)
    {
        if(gameBoard[i][column] == gemType)
            counter++;
        else
        {
            if (counter >= 2)
                return true;
            else
                break;
        }
    }
    return false;
}

bool Board::isShapeTHorziontally(int columnId, int startRow,int endRow, int gemType)
{
    if((endRow - startRow + 1)%2 == 0)
        return false;
    int row = (endRow - startRow + 1)/2 + startRow, counter = 0;
    for(int i = columnId-1; i >= 0; i--)
    {
        if(gameBoard[row][i] == gemType)
            counter++;
        else
        {
            if(counter>=2)
                return true;
            else
                break;
        }
    }
    counter = 0;
    for(int i = columnId+1; i < size; i++)
    {
        if(gameBoard[row][i] == gemType)
            counter++;
        else
        {
            if(counter>=2)
                return true;
            else
                break;
        }
    }
    return false;
}

bool Board::isShapeLHorziontally(int columnId, int startRow,int endRow, int gemType)
{
    int rightCounter = 0, leftCounter = 0;
    for(int i = columnId+1; i < size; i++)
    {
        if(gameBoard[startRow][i] == gemType)
            rightCounter++;
        else if (gameBoard[endRow][i] == gemType)
            leftCounter++;
        else
        {
            if (rightCounter >= 2 || leftCounter >= 2)
                return true;
            else
                break;
        }
    }
    
    rightCounter = 0, leftCounter = 0;

    for(int i = columnId-1; i >=0 ; i--)
    {
        if(gameBoard[startRow][i] == gemType)
            rightCounter++;
        else if (gameBoard[endRow][i] == gemType)
            leftCounter++;
        else
        {
            if (rightCounter >= 2 || leftCounter >= 2)
                return true;
            else
                break;
        }
    }
    return false;
}

bool Board::checkMoves()
{
    unordered_map<int,int> countGemTypePerRow;
    for(int i = 0; i < gameBoard.size(); i++)
    {   
        countGemTypePerRow.clear();
        for(int j = 0; j < gameBoard.size(); j++)
        {
            if(countGemTypePerRow[gameBoard[i][j]])
                countGemTypePerRow[gameBoard[i][j]]++;
            else
                countGemTypePerRow[gameBoard[i][j]] = 1;
        }
        for (auto& it: countGemTypePerRow)
        {
            if(it.second >=2)
                return true;
        }
    }
    return false;
}