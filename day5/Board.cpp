
#include <vector>
#include <iostream>
#include <string>
#include "Board.h"
#include "../utils.h"

using namespace std;

Board::Board(
    string _name,
    int maxRows,
    int maxCols
) : 
    name(_name),
    matrix(
        // empty vec of zeroes
        vector<vector<int>>(maxRows+1,vector<int>(maxCols+1, 0))
    )
    {   
}

void Board::incrementValue(int rowIndex, int colIndex){
    matrix[rowIndex][colIndex]++;
}

int Board::findNoGtEt(int threshold) const {
    int total = 0;
    for (int i = 0;i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if (matrix[i][j] >= threshold){
                total++;
            }
        }
    }
    return total;
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

int Board::sumRow(int rowIndex) const {
    vector<vector<int>> matrix;
    vector<int> row = matrix[rowIndex];
    return common::sumVector(row);
}

int Board::sumColumn(int colIndex) const {
    vector<vector<int>> matrix;
    vector<int> column;
    for (int i = 0; i < matrix.size(); i++){
        vector<int> row = matrix[i];
        column.push_back(row[colIndex]);
    }
    return common::sumVector(column);
}

int Board::getValue(int rowIndex, int colIndex) const {
    vector<int> row = matrix[rowIndex];
    return row[colIndex];
}

string Board::getName() const {
    return name;
}

void Board::printBoard() const {
    cout << endl << name << ": " << endl;
    for (int i = 0;i < matrix.size(); i++){
        cout << "|";
        for(int j = 0; j < matrix[i].size(); j++){
            if (matrix[i][j] == 0){
                cout << ".";
            } else {
                cout << matrix[i][j];
            }
        }
        cout  << "|\n";
    }
}

