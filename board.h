#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Board
{
private:
    vector< vector<int> > gameBoard;
    vector<bool> rowsStates;
    int size;
    bool isShapeLVertically(int, int, int, int);
    bool isShapeTVertically(int, int, int, int);
    bool isShapeLHorziontally(int, int, int, int);
    bool isShapeTHorziontally(int, int, int, int);
    bool checkShapeHorziontally();
    bool checkShapeVeritically();
public:
    Board(int);
    ~Board();
    void printBoard();
    vector<vector<int> > getBoard();
    bool isSwapValid(int, int, int, int);
    bool swapAdjacentCellsWithDirection(int, int, string);
    bool swapAdjacentCells(int, int, int, int);
    bool checkDirection(int, int, string);
    bool checkShape();
    bool isRowValid(int);
    void deleteRow(int);
    void initializeBoard(int);
    void initializeRowsState();
};
