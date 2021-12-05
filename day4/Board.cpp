
#include <vector>
#include <iostream>
#include <string>
#include "Board.h"
#include "../utils.h"

using namespace std;

Board::Board(
    std::vector<std::vector<int>> _matrix, 
    std::string _name
) : 
    matrix(_matrix),
    name(_name),
    marked(),
    alreadyWon(false),
    winScores()
    {   
}

void Board::beginGame(){
    // (re)sets the board.marked to zeroes
    std::vector<std::vector<int>> newMarked;
    for (int i = 0;i < matrix.size(); i++){
        vector<int> newRow;
        for(int j = 0; j < matrix[i].size(); j++){
            newRow.push_back(0);
        }
        newMarked.push_back(newRow);
    }
    marked = newMarked;
}

pair<int, int> Board::searchNumber(int number) const {
    // searches for number on our board - returns row and col index
    // if pair of negative ints are returned, number is not present
    for (int i = 0;i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            int boardNumber = matrix[i][j];
            if (boardNumber == number){
                return pair<int, int> (i, j);
            }
        }
    }
    return pair<int, int> (-1,-1); 
}

int Board::sumRow(int rowIndex, BoardType type) const {
    vector<vector<int>> board;
    board = type==Marked ? marked : matrix;
    vector<int> row = board[rowIndex];
    return common::sumVector(row);
}

int Board::sumColumn(int colIndex, BoardType type) const {
    vector<vector<int>> board;
    board = type==Marked ? marked : matrix;
    vector<int> column;
    for (int i = 0; i < board.size(); i++){
        vector<int> row = board[i];
        column.push_back(row[colIndex]);
    }
    return common::sumVector(column);
}

int Board::sumUnmarked() const {
    int total = 0;
    for (int i = 0;i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            total += ((1-marked[i][j]) * matrix[i][j]);
        }
    }
    return total;
}
int Board::getValue(int rowIndex, int colIndex) const {
    vector<int> row = matrix[rowIndex];
    return row[colIndex];
}

string Board::getName() const {
    return name;
}

void Board::markValue(int rowIndex, int colIndex) {
    marked[rowIndex][colIndex] = 1;
}

bool Board::checkRowMarked(int rowIndex) const {
    vector<int> row = matrix[rowIndex];
    return sumRow(rowIndex, Marked) == row.size();
}
bool Board::checkColMarked(int colIndex) const {
    return sumColumn(colIndex, Marked) == matrix.size();
}

void Board::printBoard(BoardType type = Matrix) const {
    vector<vector<int>> board;
    board = type==Marked? marked : matrix;
    string bName = type==Marked? "Marked" : "Matrix";
    cout << endl << name << ": " << bName << endl;
    for (int i = 0;i < board.size(); i++){
        cout << "|";
        for(int j = 0; j < board[i].size(); j++){
            string extraSpace = board[i][j] < 10 ? " " : "";
            cout << "\t" << extraSpace << board[i][j];
        }
        cout  << "|\n";
    }
}

void Board::setWinScores(int numberDrawn, int umSum){
    winScores = pair<int, int>(numberDrawn, umSum);
    alreadyWon = true;
}
