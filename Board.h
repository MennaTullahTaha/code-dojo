#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Board
{
private:
    vector< vector<int> > game_board;
    bool rows_state[3];
public:
    Board();
    ~Board();
    void printBoard();
    vector<vector<int> > getBoard();
    bool isSwapValid(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition);
    vector<vector<int> > swapAdjacentCells(int firstRowPosition, int firstColumnPosition, int secondRowPosition, int secondColumnPosition);
    bool isRowValid(int rowIndex);
    void deleteRow(int rowIndex);
};

