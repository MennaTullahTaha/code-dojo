#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Board
{
private:
    vector< vector<int> > gameBoard;
    int size;
    bool isShapeLVertically(int, int, int, int);
    bool isShapeTVertically(int, int, int, int);
    bool isShapeLHorziontally(int, int, int, int);
    bool isShapeTHorziontally(int, int, int, int);
    bool checkShapeHorziontally();
    bool checkShapeVeritically();
    void checkForSameGemsRows();
    void refillGems();
    void removeGemsFromRow(int, int, int);
    void populateGemsFromRowsAbove(int, int);
    void checkForSameGemsColumn();
    void removeGemsFromColumn(int,int,int);

public:
    int numberOfMovesLeft, score;
    Board(int, int);
    ~Board();
    void printBoard();
    bool checkMoves();
    vector<vector<int> > getBoard();
    bool isSwapValid(int, int, int, int);
    bool swapAdjacentCellsWithDirection(int, int, string);
    bool swapAdjacentCells(int, int, int, int);
    bool checkDirection(int, int, string);
    bool checkShape();
    void initializeBoard(int);
};
