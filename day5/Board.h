#pragma once
#include <vector>
#include <string>


class Board
{
    private:
        std::vector<std::vector<int>> matrix;
        std::string name;
        int sumRow(int rowIndex) const;
        int sumColumn(int colIndex) const;
        int getValue(int rowIndex, int colIndex) const;
    public:
        Board(
            std::string _name,
            int maxRows,
            int maxCols
        );
        ~Board(){};
        // getters
        int findNoGtEt(int threshold) const;
        std::pair<int, int> searchNumber(int number) const;
        void printBoard() const;
        std::string getName() const;
        
        // setters
        void incrementValue(int rowIndex, int colIndex);
        

};