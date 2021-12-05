#pragma once
#include <vector>
#include <string>


enum BoardType{
    Matrix,
    Marked
};

class Board
{
    private:
        std::vector<std::vector<int>> matrix;
        std::string name;
        std::vector<std::vector<int>> marked;
        int sumRow(int rowIndex, BoardType type) const;
        int sumColumn(int colIndex, BoardType type) const;
        int getValue(int rowIndex, int colIndex) const;
    public:
        std::pair<int, int> winScores;
        bool alreadyWon;
        Board(
            std::vector<std::vector<int>> _matrix, 
            std::string _name
        );
        ~Board(){};
        // getters
        bool checkRowMarked(int rowIndex) const;
        bool checkColMarked(int colIndex) const;
        std::pair<int, int> searchNumber(int number) const;
        int sumUnmarked() const;
        void printBoard(BoardType type) const;
        std::string getName() const;
        
        // setters
        void markValue(int rowIndex, int colIndex);
        void beginGame();
        void setWinScores(int numberDrawn, int umSum);
        

};