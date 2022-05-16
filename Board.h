#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Board
{
private:
    vector< vector<int> > gameBoard;
    vector<bool> rowsStates;
    int size;
public:
    Board(int given_size);
    ~Board();
    void printBoard();
    vector<vector<int> > getBoard();
    bool isSwapValid(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition);
    bool swapAdjacentCells(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition);
    bool isRowValid(int rowIndex);
    void deleteRow(int rowIndex);
    void initializeBoard(int size);
    void initializeRowsState();
};

